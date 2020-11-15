
#ifndef __GYRO_TRAN_H
#define __GYRO_TRAN_H

#define AHT10_I2C_BUS_NAME      "i2c1"         /* ���������ӵ�I2C�����豸���� */
#define AHT10_ADDR               0x68          /* �ӻ���ַ */
struct rt_i2c_bus_device *gyroscope;           /* I2C�����豸��� */

                                               /* ����I2C�����豸����ȡI2C�����豸��� */
gyroscope = (struct rt_i2c_bus_device *)rt_device_find(AHT10_I2C_BUS_NAME);

static rt_err_t read_regs(struct rt_i2c_bus_device *bus, rt_uint8_t len, rt_uint8_t *buf);


#endif

