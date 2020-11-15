#include <distance.h>


float Hcsr04GetLength(void )
{
		unsigned long t=0;
		rt_uint32_t t = 0;
		int i = 0;
		float lengthTemp = 0;
		float sum = 0;
		while(i!=5)
		{
		TRIG_Send = 1;                 						//发送口高电平输出
		delay_us(20);
		TRIG_Send = 0;
		while(ECHO_Reci == 0);         						//等待接收口高电平输出
			
			timer_init(timer_info_my); 						//打开定时器
			i = i + 1;
			while(ECHO_Reci == 1);
			 timer_stop(timer_info_my);                  	//关闭定时器
			t = timer_get_time_ns(timer_info_my);       	//获取时间,分辨率为1US
			lengthTemp = ((float)t/58.0);//cm
			sum = lengthTemp + sum ;
		
	}
		lengthTemp = sum/5.0;
		return lengthTemp;
}

}



