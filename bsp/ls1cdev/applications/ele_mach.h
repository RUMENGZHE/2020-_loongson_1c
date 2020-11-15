#ifndef __ELE_MACH_H__
#define __ELE_MACH_H__

#include <rtthread.h>
#include <rtdevice.h>




#define PWM_1       "pwm1"            /* PWM设备名称 */
#define PWM_1_CHANNEL     1           /* PWM通道 */
struct rt_device_pwm *pwm_dev_1;      /* PWM设备句柄 */   
rt_uint32_t period_1, pulse_1;

period_1 = 500000;                    /* 周期为0.5ms，单位为纳秒ns */
pulse_1 = 0;                          /* PWM脉冲宽度值，单位为纳秒ns */
                                      /* 查找设备 */





#define PWM_2       "pwm2"            /* PWM设备名称 */
#define PWM_2_CHANNEL     2           /* PWM通道 */
struct rt_device_pwm *pwm_dev_2;      /* PWM设备句柄 */   
rt_uint32_t period_2, pulse_2;

period_2 = 500000;                    /* 周期为0.5ms，单位为纳秒ns */
pulse_2 = 0;                          /* PWM脉冲宽度值，单位为纳秒ns */
                                      /* 查找设备 */




void ele_machinery(void);



#endif
