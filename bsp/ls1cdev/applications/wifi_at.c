
#include <wifi_at.h>

                                               /*在ENV中使能AT命令，AT Server使用默认配置*/




void wifi_at()
{
                                               /*将wifi模块设置为TCP协议，透传模式*/
	int at_server_init(void);
	void at_server_printfln("AT+CWMOD=1");
	void at_server_printfln("AT+RST");
	void at_server_printfln("AT+CWJAK='ALIENTEK','15902020353'");
	void at_server_printfln("AT+CIPSTART='TCP','192.168.1.115','8080'");
	void at_server_printfln("AT+CIPMODE=1");
	void at_server_printfln("AT+CIPSEND");


}
