#include <MPU6050.h>



				                                                //初始化MPU6050
				                                                //返回值:0,成功
				                                                //    其他,错误代码
rt_uint8_t MPU6050_Init(void)
{ 
	rt_uint8_t res;
	
	MPU6050_Write_Byte(MPU6050_PWR_MGMT1_REG,0X80);   			//复位MPU6050
    rt_thread_mdelay(100)
	MPU6050_Write_Byte(MPU6050_PWR_MGMT1_REG,0X00);				//唤醒MPU6050
	MPU6050_Set_Gyro_Fsr(3);									//陀螺仪传感器,±2000dps
	MPU6050_Set_Accel_Fsr(0);									//加速度传感器,±2g
	MPU6050_Set_Rate(50);										//设置采样率50Hz
	MPU6050_Write_Byte(MPU6050_INT_EN_REG,0X00);				//关闭所有中断
	MPU6050_Write_Byte(MPU6050_USER_CTRL_REG,0X00);				//I2C主模式关闭
	MPU6050_Write_Byte(MPU6050_FIFO_EN_REG,0X00);				//关闭FIFO
	MPU6050_Write_Byte(MPU6050_INTBP_CFG_REG,0X80);				//INT引脚低电平有效
	res=MPU6050_Read_Byte(MPU6050_DEVICE_ID_REG);
	if(res==MPU6050_ADDR)										//器件ID正确
	{
		MPU6050_Write_Byte(MPU6050_PWR_MGMT1_REG,0X01);			//设置CLKSEL,PLL X轴为参考
		MPU6050_Write_Byte(MPU6050_PWR_MGMT2_REG,0X00);			//加速度与陀螺仪都工作
		MPU6050_Set_Rate(50);									//设置采样率为50Hz
 	}else return 1;
	return 0;
}
																//设置MPU6050陀螺仪传感器满量程范围
																//fsr:0,±250dps;1,±500dps;2,±1000dps;3,±2000dps
																//返回值:0,设置成功
																//    其他,设置失败 
rt_uint8_t MPU6050_Set_Gyro_Fsr(rt_uint8_t fsr)
{
	return MPU6050_Write_Byte(MPU6050_GYRO_CFG_REG,fsr<<3);		//设置陀螺仪满量程范围  
}
																//设置MPU6050加速度传感器满量程范围
																//fsr:0,±2g;1,±4g;2,±8g;3,±16g
																//返回值:0,设置成功
																//    其他,设置失败 
rt_uint8_t MPU6050_Set_Accel_Fsr(rt_uint8_t fsr)
{
	return MPU6050_Write_Byte(MPU6050_ACCEL_CFG_REG,fsr<<3);	//设置加速度传感器满量程范围  
}
																//设置MPU6050的数字低通滤波器
																//lpf:数字低通滤波频率(Hz)
																//返回值:0,设置成功
																//    其他,设置失败 
rt_uint8_t MPU6050_Set_LPF(rt_uint16_t lpf)
{
	rt_uint8_t data=0;
	if(lpf>=188)data=1;
	else if(lpf>=98)data=2;
	else if(lpf>=42)data=3;
	else if(lpf>=20)data=4;
	else if(lpf>=10)data=5;
	else data=6; 
	return MPU6050_Write_Byte(MPU6050_CFG_REG,data);			//设置数字低通滤波器  
}
																//设置MPU6050的采样率(假定Fs=1KHz)
																//rate:4~1000(Hz)
																//返回值:0,设置成功
																//    其他,设置失败 
rt_uint8_t MPU6050_Set_Rate(rt_uint16_t rate)
{
	rt_uint8_t data;
	if(rate>1000)rate=1000;
	if(rate<4)rate=4;
	data=1000/rate-1;
	data=MPU6050_Write_Byte(MPU6050_SAMPLE_RATE_REG,data);		//设置数字低通滤波器
 	return MPU6050_Set_LPF(rate/2);								//自动设置LPF为采样率的一半
}

																//得到温度值
																//返回值:温度值(扩大了100倍)
short MPU6050_Get_Temperature(void)
{
    rt_uint8_t buf[2]; 
    short raw;
	float temp;
	MPU6050_Read_Len(MPU6050_ADDR,MPU6050_TEMP_OUTH_REG,2,buf); 
    raw=((rt_uint16_t)buf[0]<<8)|buf[1];  
    temp=36.53+((double)raw)/340;  
    return temp*100;;
}
																//得到陀螺仪值(原始值)
																//gx,gy,gz:陀螺仪x,y,z轴的原始读数(带符号)
																//返回值:0,成功
																//    其他,错误代码
rt_uint8_t MPU6050_Get_Gyroscope(short *gx,short *gy,short *gz)
{
    rt_uint8_t buf[6],res;  
	res=MPU6050_Read_Len(MPU6050_ADDR,MPU6050_GYRO_XOUTH_REG,6,buf);
	if(res==0)
	{
		*gx=((rt_uint16_t)buf[0]<<8)|buf[1];  
		*gy=((rt_uint16_t)buf[2]<<8)|buf[3];  
		*gz=((rt_uint16_t)buf[4]<<8)|buf[5];
	} 	
    return res;;
}
																//得到加速度值(原始值)
																//gx,gy,gz:陀螺仪x,y,z轴的原始读数(带符号)
																//返回值:0,成功
																//    其他,错误代码
rt_uint8_t MPU6050_Get_Accelerometer(short *ax,short *ay,short *az)
{
    rt_uint8_t buf[6],res;  
	res=MPU6050_Read_Len(MPU6050_ADDR,MPU6050_ACCEL_XOUTH_REG,6,buf);
	if(res==0)
	{
		*ax=((rt_uint16_t)buf[0]<<8)|buf[1];  
		*ay=((rt_uint16_t)buf[2]<<8)|buf[3];  
		*az=((rt_uint16_t)buf[4]<<8)|buf[5];
	} 	
    return res;;
}

