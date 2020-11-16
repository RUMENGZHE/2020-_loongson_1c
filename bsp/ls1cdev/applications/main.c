

#include <rtthread.h>
#include <gps.h>
#include <wifi_link.h>
#include <wifi_at.h>
#include <wifi_tcp_link.h>
#include <mpu6050.h>
#include <gyro_tran.h>
#include <ls1c_pin.h>
#include <ls1c_uart.h>


pin_set_remap(gpio58,PIN_REMAP_FIFTH);
pin_set_remap(gpio59,PIN_REMAP_FIFTH);
uart_init(LS1C_UART4);

pin_set_remap(gpio60,PIN_REMAP_FIFTH);
pin_set_remap(gpio61,PIN_REMAP_FIFTH);
uart_init(LS1C_UART5);

pin_set_remap(gpio62,PIN_REMAP_FIFTH);
pin_set_remap(gpio63,PIN_REMAP_FIFTH);
uart_init(LS1C_UART6);


pin_set_remap(gpio74,PIN_REMAP_FOURTH);
pin_set_remap(gpio75,PIN_REMAP_FOURTH);


pin_set_remap(gpio96,PIN_REMAP_SECOND);
pin_set_remap(gpio103,PIN_REMAP_FOURTH);

pin_set_remap(gpio74,PIN_REMAP_FIRST);
pin_set_remap(gpio75,PIN_REMAP_FIRST);


static rt_sem_t dynamic_sem_gps = RT_NULL;



static rt_thread_t th_gps = RT_NULL;
static rt_thread_t th_wifi = RT_NULL;
static rt_thread_t th_gyro = RT_NULL;
static rt_thread_t th_mach = RT_NULL;
static rt_thread_t th_recie = RT_NULL;
static rt_thread_t th_sd=RT_NULL;

#define THREAD_PRIORITY         25
#define THREAD_STACK_SIZE       512
#define THREAD_TIMESLICE        5

static char thread_stack_gps[1024];
static char thread_stack_wifi[1024];
static char thread_stack_gyro[1024];
static char thread_stack_mach[1024];
static char thread_stack_recie[1024];
static char thread_stack_sd[1024];



static int re_mach;
static char rec_com;

static void th_gps_entry(void *parameter)
{

serial = rt_device_find(gps);

rt_err_t result;
rt_size_t site_size[4];

static rt_uint32_t nmea[10];

result=rt_device_open(serial_gps,RT_DEVICE_FLAG_INT_TX);

/*使用RT-thread默认串口配置*/

NMEA_GPGSV_Analysis(&gpsx,&buf);
NMEA_BDGSV_Analysis(&gpsx,&buf);
NMEA_GNGGA_Analysis(&gpsx,&buf);
NMEA_GNGSA_Analysis(&gpsx,&buf);
NMEA_GNGSA_Analysis(&gpsx,&buf);
NMEA_GNRMC_Analysis(&gpsx,&buf);
NMEA_GNVTG_Analysis(&gpsx,&buf);

site_size[0]=rt_device_write(serial_gps,&(nmea_msg->latitude), &nmea[0],sizeof(*nmea_msg->latitude));
site_size[1]=rt_device_write(serial_gps,&(nmea_msg->nshemi), &nmea[1],sizeof(*nmea_msg->nshemi));
site_size[2]=rt_device_write(serial_gps,&(nmea_msg->longitude), &nmea[2],sizeof(*nmea_msg->longitude));
site_size[3]=rt_device_write(serial_gps,&(nmea_msg->ewhemi), &nmea[3],sizeof(*nmea_msg->ewhemi));


rt_mb_send(&site,(rt_uint32_t)&nmea);


rt_sem_release(dynamic_sem_gps);


re_mach=recv(serial_gps,rec_com,1,0);




}

static void th_wifi_entry(void *parameter)
{
static rt_uint32_t nmea_rec[10];
rt_err_t result;

wifi_link();
wifi_at();
wifi_tcp_link();
result = rt_sem_take(dynamic_sem_gps, RT_WAITING_FOREVER);
			if (result != RT_EOK)
			{		 
				rt_kprintf("t2 take a dynamic semaphore, failed.\n");
				rt_sem_delete(dynamic_sem_gps);
				return;
			}
			else
				{

				
			    if (rt_mb_recv(&mb, (rt_uint32_t *)&nmea_rec[0], RT_WAITING_FOREVER)&rt_mb_recv(&mb, (rt_uint32_t *)&nmea_rec[1], RT_WAITING_FOREVER)
				   	&rt_mb_recv(&mb, (rt_uint32_t *)&nmea_rec[2], RT_WAITING_FOREVER)&rt_mb_recv(&mb, (rt_uint32_t *)&nmea_rec[3], RT_WAITING_FOREVER)== RT_EOK)
					{
					result=send(scoket_des, &nmea_rec, strlen(&nmea_rec),0);

						if (str == mb_str3)
							break;
				
						/* 延时100ms */
						rt_thread_mdelay(100);
					}
				}
				/* 执行邮箱对象脱离 */
				rt_mb_detach(&mb);
				}
			    
 
}

static void th_gyro_entry(void *parameter)
{
	static rt_uint32_t temp;
    static rt_err_t result[9];

	result[0]=MPU6050_Init(void);								//初始化MPU6050
	
	
	
	temp=MPU6050_Get_Temperature(void);
	result[1]=MPU6050_Get_Gyroscope(short *gx,short *gy,short *gz);
	result[2]=MPU6050_Get_Accelerometer(short *ax,short *ay,short *az);
	
	result[3]=read_regs(*gyroscope, 2,*gx);
	result[4]=read_regs(*gyroscope, 2,*gy);
	result[5]=read_regs(*gyroscope, 2,*gz);


	
	if (result[0]|result[1]|result[2]|result[3]|result[4]!= RT_EOK)
	   {
		   rt_kprintf("init failed.\n");
		   return -1;
	   }
else
{
	result[6]=send(scoket_des, gx, strlen(*gx),0);
	result[7]=send(scoket_des, gy, strlen(*gy),0);
	result[8]=send(scoket_des, gz, strlen(*gz),0);
	

	if (result[6]|result[7]|result[8]!= RT_EOK)
	   {
		   rt_kprintf("init failed.\n");
		   return -1;
	   }



}

}



static void th_mach_entry(void *parameter)
{

static rt_err_t result[9];


if(re_com=='D')
{
result[0]=rt_pwm_enable(pwm_dev_1,PWM_1_CHANNEL);
result[1]=rt_pwm_enable(pwm_dev_2,PWM_2_CHANNEL);

if(result[0]&result[1]&result[2]!= RT_EOK)
{

rt_kprintf("start failed.\n");
return -1;






switch(re_com)
{
/*左*/
case 'L':
	result[4]=rt_pwm_set(pwm_dev_1,PWM_1_CHANNEL,period,pulse);
	result[5]=rt_pwm_set(pwm_dev_2,PWM_2_CHANNEL,period,pulse*2);

	
	if(result[4]&result[5]!= RT_EOK)
	{
	
	rt_kprintf("failed.\n");
	return -1;
		}
	break;
case 'R':
	result[4]=rt_pwm_set(pwm_dev_1,PWM_1_CHANNEL,period,pulse*2);
	result[5]=rt_pwm_set(pwm_dev_2,PWM_2_CHANNEL,period,pulse);

	if(result[4]&result[5]!= RT_EOK)
	{
	
	rt_kprintf("failed.\n");
	return -1;
		}
	break;
	case 'S':
		result[4]=rt_pwm_disenable(pwm_dev_1,PWM_1_CHANNEL);
		result[5]=rt_pwm_disenable(pwm_dev_2,PWM_2_CHANNEL);

		if(result[4]&result[5]!= RT_EOK)
		{
		
		rt_kprintf("failed.\n");
		return -1;
			}
		break;


}
}
}
}

static void th_sd_entry(void *parameter)
{

static rt_err_t result;

rt_uint8_t data[18];
rt_uint32_t buff_length=8;
rt_uint32_t sd_data_len=8;


fill_buffer(&data,buff_length);

result=sd_device(sd_data_len,&nmea);

	if(result!= RT_EOK)
			{
			
			rt_kprintf("failed.\n");
			return -1;
				}


}


static struct rt_mailbox site;
/* 用于放邮件的内存池 */
static char site_pool[128];
ALIGN(RT_ALIGN_SIZE)

int mailbox_site(void)
{
    rt_err_t result;


    result = rt_site_init(&site,
                        "my_site",                     
                        &site_pool[0],                
                        sizeof(site_pool) / 4,     
                        RT_IPC_FLAG_FIFO);       
    if (result != RT_EOK)
    {
        rt_kprintf("init mailbox failed.\n");
        return -1;
    }


static void recie_entry(void *parameter)
{
    
    /* 安装信号 */
    rt_signal_install(SIGUSR1, rt_signal_handler);
    rt_signal_unmask(SIGUSR1);
	

    
}

void rt_signal_handler()
{

	result[0]=rt_pwm_disenable(pwm_dev_1,PWM_1_CHANNEL);
		result[1]=rt_pwm_disenable(pwm_dev_2,PWM_2_CHANNEL);

				if(result[0]&result[1]!= RT_EOK)
				{
				
				rt_kprintf("failed.\n");
				return -1;
					}


}

int signal_recie(void)
{

float lenth;
	/* 创建线程1 */
	th_recie = rt_thread_create("recie",
							recie_entry, RT_NULL,
							sizeof(*thread_stack_recie),
							THREAD_PRIORITY, THREAD_TIMESLICE);
	
	if (tid1 != RT_NULL)	   
		rt_thread_startup(tid1);

	if(lenth<=30)
		{
	/* 发送信号 SIGUSR1 给线程1 */
	rt_thread_kill(th_recie, SIGUSR1);
		}
	return 0;
}





int main(int argc, char** argv)
{   

th_gps = rt_thread_create("th_gps",
                            th_gps_entry, RT_NULL,
                            sizeof(*thread_stack_gps),
                            THREAD_PRIORITY, THREAD_TIMESLICE);

    if (th_gps != RT_NULL)
        rt_thread_startup(th_gps);
 th_wifi = rt_thread_create("th_wifi",
							 th_wifi_entry, RT_NULL,
							 sizeof(*thread_stack_wifi),
							 THREAD_PRIORITY, THREAD_TIMESLICE);
 
	 if (th_wifi != RT_NULL)
		 rt_thread_startup(th_wifi);
 th_gyro = rt_thread_create("th_gyro",
							 th_gyro_entry, RT_NULL,
							 sizeof(*thread_stack_gyro),
							 THREAD_PRIORITY, THREAD_TIMESLICE);
 
	 if (th_gps != RT_NULL)
		 rt_thread_startup(th_gyro);
 th_mach = rt_thread_create("th_mach",
							 th_mach_entry, RT_NULL,
							 sizeof(*thread_stack_mach),
							 THREAD_PRIORITY, THREAD_TIMESLICE);
 
	 if (th_mach != RT_NULL)
		 rt_thread_startup(th_mach);
 th_sd = rt_thread_create("th_sd",
							  th_sd_entry, RT_NULL,
							  sizeof(*thread_stack_sd),
							  THREAD_PRIORITY, THREAD_TIMESLICE);
  
	  if (th_mach != RT_NULL)
		  rt_thread_startup(th_mach);

 dynamic_sem_gps = rt_sem_create("gps", 0, RT_IPC_FLAG_FIFO);
    if (dynamic_sem_gps == RT_NULL)
    {
        rt_kprintf("create dynamic semaphore failed.\n");
        return -1;
    }
    else
    {
        rt_kprintf("create done. dynamic semaphore value = 0.\n");
    }

	

    return 0;
}
