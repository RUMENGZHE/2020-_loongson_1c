
#include <wifi_link.h>

                                                          /*WLAN�豸ʹ��Ĭ������*/

void wifi_link()
{

struct rt_wlan_info wifi_info;

INVALID_INFO(&wifi_info);                                 /* ��ʼ�� info */
SSID_SET(&wifi_info, "nova7");                            /* �����ȵ����� */
wifi_info.security = SECURITY_WPA2_AES_PSK;               /* ָ����ȫ���� */
rt_wlan_connect_adv(&wifi_info, "123mydream");            /* ִ�����Ӷ��� */
while (rt_wlan_is_connected() == RT_FALSE);               /* �ȴ����ӳɹ� */

}
