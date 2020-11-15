
#include <wifi_link.h>

                                                          /*WLAN设备使用默认配置*/

void wifi_link()
{

struct rt_wlan_info wifi_info;

INVALID_INFO(&wifi_info);                                 /* 初始化 info */
SSID_SET(&wifi_info, "nova7");                            /* 设置热点名字 */
wifi_info.security = SECURITY_WPA2_AES_PSK;               /* 指定安全类型 */
rt_wlan_connect_adv(&wifi_info, "123mydream");            /* 执行连接动作 */
while (rt_wlan_is_connected() == RT_FALSE);               /* 等待连接成功 */

}
