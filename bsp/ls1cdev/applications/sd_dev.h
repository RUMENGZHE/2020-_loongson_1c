#ifndef __SD_DEV_H__
#define __SD_DEV_H__




#include <rtthread.h>
#include <rtdevice.h>
#include <stdlib.h>

struct rt_spi_device *sdcard;
rt_uint32_t 

rt_err_t result_sd;



result_sd=rt_spi_bus_attach_device(sdcard,sdcard_dev,"SPI0");



#define SD_DEVICE_NAME    "sd0"




#endif
