#include <sd_dev.h>

void fill_buffer(rt_uint8_t *buff, rt_uint32_t buff_length)
{
    rt_uint32_t index;
  																  /* ���������������� */
    for (index = 0; index < buff_length; index++)
    {
        buff[index] = ((rt_uint8_t)rand()) & 0xff;
    }
}
static int sd_device(int argc, char *argv[])
{
    rt_err_t ret;
    rt_device_t sd_device;
    char sd_name[RT_NAME_MAX];
    rt_uint8_t *write_buff, *read_buff;
    struct rt_device_blk_geometry geo;
    rt_uint8_t block_num;
    															/* �ж������в����Ƿ�������豸���� */
    if (argc == 2)
    {
        rt_strncpy(sd_name, argv[1], RT_NAME_MAX);
    }
    else
    {
        rt_strncpy(sd_name, SD_DEVICE_NAME, RT_NAME_MAX);
    }
    															/* �����豸��ȡ�豸��� */
    sd_device = rt_device_find(sd_name);
    if (sd_device == RT_NULL)
    {
        rt_kprintf("find device %s failed!\n", sd_name);
        return RT_ERROR;
    }
   																 /* ���豸 */
    ret = rt_device_open(sd_device, RT_DEVICE_OFLAG_RDWR);
    if (ret != RT_EOK)
    {
        rt_kprintf("open device %s failed!\n", sd_name);
        return ret;
    }
    rt_memset(&geo, 0, sizeof(geo));
    															 /* ��ȡ���豸��Ϣ */
    ret = rt_device_control(sd_device, RT_DEVICE_CTRL_BLK_GETGEOME, &geo);
    if (ret != RT_EOK)
    {
        rt_kprintf("control device %s failed!\n", sd_name);
        return ret;
    }
    rt_kprintf("device information:\n");
    rt_kprintf("sector  size : %d byte\n", geo.bytes_per_sector);
    rt_kprintf("sector count : %d \n", geo.sector_count);
    rt_kprintf("block   size : %d byte\n", geo.block_size);
    															/* ׼����д�������ռ䣬��СΪһ���� */
    read_buff = rt_malloc(geo.block_size);
    if (read_buff == RT_NULL)
    {
        rt_kprintf("no memory for read buffer!\n");
        return RT_ERROR;
    }
    write_buff = rt_malloc(geo.block_size);
    if (write_buff == RT_NULL)
    {
        rt_kprintf("no memory for write buffer!\n");
        rt_free(read_buff);
        return RT_ERROR;
    }
    															/* ���д���ݻ�������Ϊд������׼�� */
    fill_buffer(write_buff, geo.block_size);
    															/* ��д���ݻ��������д��SD���У���СΪһ���飬size�����Կ�Ϊ��λ */
    block_num = rt_device_write(sd_device, 0, write_buff, 1);
    if (1 != block_num)
    {
        rt_kprintf("write device %s failed!\n", sd_name);
    }
    															/* ��SD���ж������ݣ��������ڶ����ݻ������� */
    block_num = rt_device_read(sd_device, 0, read_buff, 1);
    if (1 != block_num)
    {
        rt_kprintf("read %s device failed!\n", sd_name);
    }
    															/* �Ƚ�д���ݻ������Ͷ����ݻ������������Ƿ���ȫһ�� */
    if (rt_memcmp(write_buff, read_buff, geo.block_size) == 0)
    {
        rt_kprintf("Block test OK!\n");
    }
    else
    {
        rt_kprintf("Block test Fail!\n");
    }
    															/* �ͷŻ������ռ� */
    rt_free(read_buff);
    rt_free(write_buff);
    return RT_EOK;
}



