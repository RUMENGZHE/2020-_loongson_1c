#include <ele_mach>


void ele_machinery()
{
pwm_dev_1 = (struct rt_device_pwm *)rt_device_find(PWM_1);
																		/* 设置PWM周期和脉冲宽度 */
pwm_dev_2 = (struct rt_device_pwm *)rt_device_find(PWM_2);

}



