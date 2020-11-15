#include <gyro_tran.h>
                                                    /* 读传感器寄存器数据 */
static rt_err_t read_regs(struct rt_i2c_bus_device *bus, rt_uint8_t len, rt_uint8_t *buf)
{
    struct rt_i2c_msg msgs;

    msgs.addr = AHT10_ADDR;                         /* 从机地址 */
    msgs.flags = RT_I2C_RD;                         /* 读标志 */
    msgs.buf = buf;                                 /* 读写数据缓冲区指针　*/
    msgs.len = len;                                 /* 读写数据字节数 */

                                                    /* 调用I2C设备接口传输数据 */
    if (rt_i2c_transfer(bus, &msgs, 1) == 1)
    {
        return RT_EOK;
    }
    else
    {
        return -RT_ERROR;
    }
}

