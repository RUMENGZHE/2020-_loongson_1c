
#include <wifi_at.h>

                                               /*��ENV��ʹ��AT���AT Serverʹ��Ĭ������*/




void wifi_at()
{
                                               /*��wifiģ������ΪTCPЭ�飬͸��ģʽ*/
	int at_server_init(void);
	void at_server_printfln("AT+CWMOD=1");
	void at_server_printfln("AT+RST");
	void at_server_printfln("AT+CWJAK='ALIENTEK','15902020353'");
	void at_server_printfln("AT+CIPSTART='TCP','192.168.1.115','8080'");
	void at_server_printfln("AT+CIPMODE=1");
	void at_server_printfln("AT+CIPSEND");


}
