#include <ele_mach>


void ele_machinery()
{
pwm_dev_1 = (struct rt_device_pwm *)rt_device_find(PWM_1);
																		/* ����PWM���ں������� */
pwm_dev_2 = (struct rt_device_pwm *)rt_device_find(PWM_2);

}



