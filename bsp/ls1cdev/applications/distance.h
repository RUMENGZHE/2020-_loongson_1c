#ifndef __DISTANCE_H__
#define __DISTANCE_H__

#include <ls1c_timer.h>
#include <rtthread.h>
#include <ls1c_delay.h>

#define ECHO_Reci gpio58
#define TRIG_Send gpio59

timer_info_t timer_info_my;

timer_info_my.timer=TIMER_PWM0;
timer_info_my.time_ns=0;
timer_info_my.time_h_ns=0;



float Hcsr04GetLength(void );




#endif
