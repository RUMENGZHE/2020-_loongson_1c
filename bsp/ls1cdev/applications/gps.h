#ifndef _gps_H
#define _gps_H

#include <stdio.h> 
#include <stdarg.h>	 
#include <string.h>
#include <math.h>

#define gps       "uart5"    /* 串口设备名称 */
static rt_device_t serial_gps;                /* 串口设备句柄 */
static rt_device_t serial_wifi;
/* 查找串口设备 */



#include <rtthread.h>





//GPS NMEA-0183协议重要参数结构体定义 
//卫星信息
__packed typedef struct  
{										    
 	rt_uint8_t num;		//卫星编号
	rt_uint8_t eledeg;	//卫星仰角
	rt_uint16_t azideg;	//卫星方位角
	rt_uint8_t sn;		//信噪比		   
}nmea_slmsg; 

//北斗 NMEA-0183协议重要参数结构体定义 
//卫星信息
__packed typedef struct  
{	
 	rt_uint8_t beidou_num;		//卫星编号
	rt_uint8_t beidou_eledeg;	//卫星仰角
	rt_uint16_t beidou_azideg;	//卫星方位角
	rt_uint8_t beidou_sn;		//信噪比		   
}beidou_nmea_slmsg; 

//UTC时间信息
__packed typedef struct  
{										    
 	rt_uint16_t year;	//年份
	rt_uint8_t month;	//月份
	rt_uint8_t date;	//日期
	rt_uint8_t hour; 	//小时
	rt_uint8_t min; 	//分钟
	rt_uint8_t sec; 	//秒钟
}nmea_utc_time;   	   

//NMEA 0183 协议解析后数据存放结构体
__packed typedef struct  
{										    
 	rt_uint8_t svnum;					//可见GPS卫星数
	rt_uint8_t beidou_svnum;					//可见GPS卫星数
	nmea_slmsg slmsg[12];		//最多12颗GPS卫星
	beidou_nmea_slmsg beidou_slmsg[12];		//暂且算最多12颗北斗卫星
	nmea_utc_time utc;			//UTC时间
	rt_uint32_t latitude;				//纬度 分扩大100000倍,实际要除以100000
	rt_uint8_t nshemi;					//北纬/南纬,N:北纬;S:南纬				  
	rt_uint32_t longitude;			    //经度 分扩大100000倍,实际要除以100000
	rt_uint8_t ewhemi;					//东经/西经,E:东经;W:西经
	rt_uint8_t gpssta;					//GPS状态:0,未定位;1,非差分定位;2,差分定位;6,正在估算.				  
 	rt_uint8_t posslnum;				//用于定位的GPS卫星数,0~12.
 	rt_uint8_t possl[12];				//用于定位的卫星编号
	rt_uint8_t fixmode;					//定位类型:1,没有定位;2,2D定位;3,3D定位
	rt_uint16_t pdop;					//位置精度因子 0~500,对应实际值0~50.0
	rt_uint16_t hdop;					//水平精度因子 0~500,对应实际值0~50.0
	rt_uint16_t vdop;					//垂直精度因子 0~500,对应实际值0~50.0 

	int altitude;			 	//海拔高度,放大了10倍,实际除以10.单位:0.1m	 
	rt_uint16_t speed;					//地面速率,放大了1000倍,实际除以10.单位:0.001公里/小时	 
}nmea_msg;
 	
//S1216F8-BD 配置波特率结构体
__packed typedef struct
{
	rt_uint16_t sos;            //启动序列，固定为0XA0A1
	rt_uint16_t PL;             //有效数据长度0X0004； 
	rt_uint8_t id;             //ID，固定为0X05
	rt_uint8_t com_port;       //COM口，固定为0X00，即COM1   
	rt_uint8_t Baud_id;       //波特率（0~8,4800,9600,19200,38400,57600,115200,230400,460800,921600）
	rt_uint8_t Attributes;     //配置数据保存位置 ,0保存到SRAM，1保存到SRAM&FLASH，2临时保存
	rt_uint8_t CS;             //校验值
	rt_uint16_t end;            //结束符:0X0D0A  
}S1216F8BD_baudrate;

//S1216F8-BD 配置输出信息结构体
__packed typedef struct
{
	rt_uint16_t sos;            //启动序列，固定为0XA0A1
	rt_uint16_t PL;             //有效数据长度0X0009； 
	rt_uint8_t id;             //ID，固定为0X08
	rt_uint8_t GGA;            //1~255（s）,0:disable
	rt_uint8_t GSA;            //1~255（s）,0:disable
	rt_uint8_t GSV;            //1~255（s）,0:disable
	rt_uint8_t GLL;            //1~255（s）,0:disable
	rt_uint8_t RMC;            //1~255（s）,0:disable
	rt_uint8_t VTG;            //1~255（s）,0:disable
	rt_uint8_t ZDA;            //1~255（s）,0:disable
	rt_uint8_t Attributes;     //配置数据保存位置 ,0保存到SRAM，1保存到SRAM&FLASH，2临时保存
	rt_uint8_t CS;             //校验值
	rt_uint16_t end;            //结束符:0X0D0A  
}S1216F8BD_outmsg;

//S1216F8-BD 配置位置更新率结构体
__packed typedef struct
{
	rt_uint16_t sos;            //启动序列，固定为0XA0A1
	rt_uint16_t PL;             //有效数据长度0X0003； 
	rt_uint8_t id;             //ID，固定为0X0E
	rt_uint8_t rate;           //取值范围:1, 2, 4, 5, 8, 10, 20, 25, 40, 50
	rt_uint8_t Attributes;     //配置数据保存位置 ,0保存到SRAM，1保存到SRAM&FLASH，2临时保存
	rt_uint8_t CS;             //校验值
	rt_uint16_t end;            //结束符:0X0D0A  
}S1216F8BD_PosRate;

//S1216F8-BD 配置输出脉冲(PPS)宽度结构体
__packed typedef struct
{
	rt_uint16_t sos;            //启动序列，固定为0XA0A1
	rt_uint16_t PL;             //有效数据长度0X0007； 
	rt_uint8_t id;             //ID，固定为0X65
	rt_uint8_t Sub_ID;         //0X01
	rt_uint32_t width;        //1~100000(us)
	rt_uint8_t Attributes;     //配置数据保存位置 ,0保存到SRAM，1保存到SRAM&FLASH，2临时保存
	rt_uint8_t CS;             //校验值
	rt_uint16_t end;            //结束符:0X0D0A 
}S1216F8BD_pps_width;

//S1216F8-BD ACK结构体
__packed typedef struct
{
	rt_uint16_t sos;            //启动序列，固定为0XA0A1
	rt_uint16_t PL;             //有效数据长度0X0002； 
	rt_uint8_t id;             //ID，固定为0X83
	rt_uint8_t ACK_ID;         //ACK ID may further consist of message ID and message sub-ID which will become 3 bytes of ACK message
	rt_uint8_t CS;             //校验值
	rt_uint16_t end;            //结束符 
}S1216F8BD_ACK;

//S1216F8-BD NACK结构体
__packed typedef struct
{
	rt_uint16_t sos;            //启动序列，固定为0XA0A1
	rt_uint16_t PL;             //有效数据长度0X0002； 
	rt_uint8_t id;             //ID，固定为0X84
	rt_uint8_t NACK_ID;         //ACK ID may further consist of message ID and message sub-ID which will become 3 bytes of ACK message
	rt_uint8_t CS;             //校验值
	rt_uint16_t end;            //结束符 
}S1216F8BD_NACK;


int NMEA_Str2num(rt_uint8_t *buf,rt_uint8_t*dx);
void NMEA_GPGSV_Analysis(nmea_msg *gpsx,rt_uint8_t *buf);
void NMEA_BDGSV_Analysis(nmea_msg *gpsx,rt_uint8_t *buf);
void NMEA_GNGGA_Analysis(nmea_msg *gpsx,rt_uint8_t *buf);
void NMEA_GNGSA_Analysis(nmea_msg *gpsx,rt_uint8_t *buf);
void NMEA_GNGSA_Analysis(nmea_msg *gpsx,rt_uint8_t *buf);
void NMEA_GNRMC_Analysis(nmea_msg *gpsx,rt_uint8_t *buf);
void NMEA_GNVTG_Analysis(nmea_msg *gpsx,rt_uint8_t *buf);

#endif



