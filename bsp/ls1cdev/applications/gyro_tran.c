#include <gyro_tran.h>
                                                    /* ���������Ĵ������� */
static rt_err_t read_regs(struct rt_i2c_bus_device *bus, rt_uint8_t len, rt_uint8_t *buf)
{
    struct rt_i2c_msg msgs;

    msgs.addr = AHT10_ADDR;                         /* �ӻ���ַ */
    msgs.flags = RT_I2C_RD;                         /* ����־ */
    msgs.buf = buf;                                 /* ��д���ݻ�����ָ�롡*/
    msgs.len = len;                                 /* ��д�����ֽ��� */

                                                    /* ����I2C�豸�ӿڴ������� */
    if (rt_i2c_transfer(bus, &msgs, 1) == 1)
    {
        return RT_EOK;
    }
    else
    {
        return -RT_ERROR;
    }
}

