// SPDX-License-Identifier: GPL-2.0
/*
 * Copyright (C) 2025 InvenSense, Inc.
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */
#define pr_fmt(fmt) "inv_mpu: " fmt

#include <linux/delay.h>
#include <linux/device.h>
#include <linux/err.h>
#include <linux/i3c/device.h>
#include <linux/i3c/master.h>
#include <linux/kernel.h>
#include <linux/mod_devicetable.h>
#include <linux/module.h>
#include <linux/of_irq.h>
#include <linux/regmap.h>
#include <linux/slab.h>
#include <linux/version.h>

#include "inv_mpu_iio.h"
#include "inv_mpu_dts.h"

/* Android 14 GKI workaround */
#if KERNEL_VERSION(6, 6, 0) > LINUX_VERSION_CODE
struct device *i3cdev_to_dev(struct i3c_device *i3cdev)
{
	return &i3cdev->dev;
}
#endif

enum inv_mpu_i3c_pid {
#if defined(CONFIG_INV_MPU_IIO_ICM42600)
	INV_MPU_I3C_PID_0 = 0x46a00000000,
#elif defined(CONFIG_INV_MPU_IIO_ICM43600)
	INV_MPU_I3C_PID_0 = 0x46a00000000,
	INV_MPU_I3C_PID_1 = 0x46a00010000,
#endif
	INV_MPU_I3C_PID_NB,
};

enum inv_mpu_i3c_id {
#if defined(CONFIG_INV_MPU_IIO_ICM42600)
	INV_MPU_I3C_ID_0,
#elif defined(CONFIG_INV_MPU_IIO_ICM43600)
	INV_MPU_I3C_ID_0,
	INV_MPU_I3C_ID_1,
#endif
	INV_MPU_I3C_ID_NB,
};
struct inv_mpu_i3c_data {
	enum inv_devices id;
	const char *name;
};
#if defined(CONFIG_INV_MPU_IIO_ICM42600)
static const struct inv_mpu_i3c_data inv_mpu_chips[INV_MPU_I3C_ID_NB] = {
	[INV_MPU_I3C_ID_0] = {
		.id = ICM42688,
		.name = "icm42688",
	},
};
#elif defined(CONFIG_INV_MPU_IIO_ICM43600)
static const struct inv_mpu_i3c_data inv_mpu_chips[INV_MPU_I3C_ID_NB] = {
	[INV_MPU_I3C_ID_0] = {
		.id = ICM43600,
		.name = "icm43600",
	},
	[INV_MPU_I3C_ID_1] = {
		.id = ICM53600,
		.name = "icm53600",
	},
};
#endif

/* device id table is used to identify what device can be
 * supported by this driver
 */
#define INV_MPU_I3C_DEVICE(id, pid)			\
	I3C_DEVICE(I3C_PID_MANUF_ID(pid),		\
		   I3C_PID_PART_ID(pid),		\
		   (void *)&inv_mpu_chips[id])

static const struct i3c_device_id inv_mpu_id[INV_MPU_I3C_ID_NB + 1] = {
#if defined(CONFIG_INV_MPU_IIO_ICM42600)
	INV_MPU_I3C_DEVICE(INV_MPU_I3C_ID_0, INV_MPU_I3C_PID_0),
#elif defined(CONFIG_INV_MPU_IIO_ICM43600)
	INV_MPU_I3C_DEVICE(INV_MPU_I3C_ID_0, INV_MPU_I3C_PID_0),
	INV_MPU_I3C_DEVICE(INV_MPU_I3C_ID_1, INV_MPU_I3C_PID_1),
#endif
	{}
};
MODULE_DEVICE_TABLE(i3c, inv_mpu_id);

static const struct regmap_config inv_mpu_regmap_config = {
	.name = "inv_mpu",
	.reg_bits = 8,
	.val_bits = 8,
};

/*
 *  inv_mpu_probe() - probe function.
 */
static int inv_mpu_probe(struct i3c_device *i3cdev)
{
	const struct i3c_device_id *id = i3c_device_match_id(i3cdev, inv_mpu_id);
	struct device *dev = i3cdev_to_dev(i3cdev);
	const struct inv_mpu_i3c_data *chip = id->data;
	struct regmap *regmap;
	int irq = -ENODEV;
	struct inv_mpu_state *st;
	struct iio_dev *indio_dev;
	int result;

	regmap = devm_regmap_init_i3c(i3cdev, &inv_mpu_regmap_config);
	if (IS_ERR(regmap)) {
		result = PTR_ERR(regmap);
		goto out_no_free;
	}

	if (dev->of_node)
		irq = of_irq_get(dev->of_node, 0);
	if (irq < 0) {
		result = irq;
		goto out_no_free;
	}

#if KERNEL_VERSION(5, 9, 0) > LINUX_VERSION_CODE
	indio_dev = iio_device_alloc(sizeof(*st));
#else
	indio_dev = iio_device_alloc(dev, sizeof(*st));
#endif
	if (indio_dev == NULL) {
		pr_err("memory allocation failed\n");
		result = -ENOMEM;
		goto out_no_free;
	}

	iio_device_set_drvdata(indio_dev, indio_dev);
	st = iio_priv(indio_dev);
	mutex_init(&st->lock);
	st->map = regmap;
	st->dev = dev;
	st->irq = irq;
	st->bus_type = BUS_I3C;
	i3cdev_set_drvdata(i3cdev, indio_dev);
	indio_dev->dev.parent = dev;
	indio_dev->name = chip->name;

#ifdef CONFIG_OF
	result = invensense_mpu_parse_dt(st->dev, &st->plat_data);
	if (result)
		goto out_free;
#else
	if (dev_get_platdata(st->dev) == NULL) {
		result = -ENODEV;
		goto out_free;
	}
	st->plat_data = *(struct mpu_platform_data *)dev_get_platdata(st->dev);
#endif
	/* Power on device */
	if (st->plat_data.power_on) {
		result = st->plat_data.power_on(&st->plat_data);
		if (result < 0) {
			dev_err(st->dev, "power_on failed: %d\n", result);
			goto out_free;
		}
		pr_info("%s: power on here.\n", __func__);
	}
	pr_info("%s: power on.\n", __func__);

	msleep(100);

	/* power is turned on inside check chip type */
	result = inv_check_chip_type(indio_dev, chip->id);
	if (result)
		goto out_free;

	result = inv_mpu_configure_ring(indio_dev);
	if (result) {
		pr_err("configure ring buffer fail\n");
		goto out_free;
	}

	result = iio_device_register(indio_dev);
	if (result) {
		pr_err("IIO device register fail\n");
		goto out_unreg_ring;
	}

	result = inv_create_dmp_sysfs(indio_dev);
	if (result) {
		pr_err("create dmp sysfs failed\n");
		goto out_unreg_iio;
	}
	init_waitqueue_head(&st->wait_queue);
	st->resume_state = true;
#ifdef CONFIG_HAS_WAKELOCK
	wake_lock_init(&st->wake_lock, WAKE_LOCK_SUSPEND, "inv_mpu");
#else
	st->wake_lock = wakeup_source_create("inv_mpu");
	wakeup_source_add(st->wake_lock);
	if (st->wake_lock)
		pr_info("wakeup_source is created successfully\n");
	else
		pr_info("failed to create wakeup_source\n");
#endif
	dev_info(st->dev, "%s ma-kernel-%s is ready to go!\n",
				indio_dev->name, INVENSENSE_DRIVER_VERSION);

#ifdef TIMER_BASED_BATCHING
	pr_info("Timer based batching\n");
#endif

	return 0;

out_unreg_iio:
	iio_device_unregister(indio_dev);
out_unreg_ring:
	inv_mpu_unconfigure_ring(indio_dev);
out_free:
	iio_device_free(indio_dev);
out_no_free:
	if (result != -EPROBE_DEFER)
		dev_err(dev, "%s failed %d\n", __func__, result);
	return result;
}

/*
 *  inv_mpu_remove() - remove function.
 */
#if KERNEL_VERSION(5, 12, 0) <= LINUX_VERSION_CODE
static void inv_mpu_remove(struct i3c_device *i3cdev)
#else
static int inv_mpu_remove(struct i3c_device *i3cdev)
#endif
{
	struct iio_dev *indio_dev = i3cdev_get_drvdata(i3cdev);
	struct inv_mpu_state *st = iio_priv(indio_dev);

#ifndef CONFIG_HAS_WAKELOCK
	if (st->wake_lock)
		wakeup_source_destroy(st->wake_lock);
#endif
	if (st->aux_dev)
		i2c_unregister_device(st->aux_dev);
	iio_device_unregister(indio_dev);
	inv_mpu_unconfigure_ring(indio_dev);
	iio_device_free(indio_dev);
	dev_info(st->dev, "inv-mpu-iio module removed");
#if KERNEL_VERSION(5, 12, 0) > LINUX_VERSION_CODE
	return 0;
#endif
}

#ifdef CONFIG_PM_SLEEP
static int inv_mpu_i3c_suspend(struct device *dev)
{
	struct iio_dev *indio_dev = i3cdev_get_drvdata(dev_to_i3cdev(dev));

	return inv_mpu_suspend(indio_dev);
}

static void inv_mpu_i3c_complete(struct device *dev)
{
	struct iio_dev *indio_dev = i3cdev_get_drvdata(dev_to_i3cdev(dev));

	inv_mpu_complete(indio_dev);
}
#endif

static const struct dev_pm_ops inv_mpu_i3c_pmops = {
#ifdef CONFIG_PM_SLEEP
	.suspend = inv_mpu_i3c_suspend,
	.complete = inv_mpu_i3c_complete,
#endif
};

static struct i3c_driver inv_mpu_driver = {
	.probe = inv_mpu_probe,
	.remove = inv_mpu_remove,
	.id_table = inv_mpu_id,
	.driver = {
		.owner = THIS_MODULE,
		.name = "inv-mpu-iio-i3c",
		.pm = &inv_mpu_i3c_pmops,
	},
};
module_i3c_driver(inv_mpu_driver);

MODULE_AUTHOR("Invensense Corporation");
MODULE_DESCRIPTION("Invensense I3C device driver");
MODULE_LICENSE("GPL");
