
#ifndef __GYRO_TRAN_H
#define __GYRO_TRAN_H

#define AHT10_I2C_BUS_NAME      "i2c1"         /* 传感器连接的I2C总线设备名称 */
#define AHT10_ADDR               0x68          /* 从机地址 */
struct rt_i2c_bus_device *gyroscope;           /* I2C总线设备句柄 */

                                               /* 查找I2C总线设备，获取I2C总线设备句柄 */
gyroscope = (struct rt_i2c_bus_device *)rt_device_find(AHT10_I2C_BUS_NAME);

static rt_err_t read_regs(struct rt_i2c_bus_device *bus, rt_uint8_t len, rt_uint8_t *buf);


#endif

