#ifndef __ELE_MACH_H__
#define __ELE_MACH_H__

#include <rtthread.h>
#include <rtdevice.h>




#define PWM_1       "pwm1"            /* PWM�豸���� */
#define PWM_1_CHANNEL     1           /* PWMͨ�� */
struct rt_device_pwm *pwm_dev_1;      /* PWM�豸��� */   
rt_uint32_t period_1, pulse_1;

period_1 = 500000;                    /* ����Ϊ0.5ms����λΪ����ns */
pulse_1 = 0;                          /* PWM������ֵ����λΪ����ns */
                                      /* �����豸 */





#define PWM_2       "pwm2"            /* PWM�豸���� */
#define PWM_2_CHANNEL     2           /* PWMͨ�� */
struct rt_device_pwm *pwm_dev_2;      /* PWM�豸��� */   
rt_uint32_t period_2, pulse_2;

period_2 = 500000;                    /* ����Ϊ0.5ms����λΪ����ns */
pulse_2 = 0;                          /* PWM������ֵ����λΪ����ns */
                                      /* �����豸 */




void ele_machinery(void);



#endif
