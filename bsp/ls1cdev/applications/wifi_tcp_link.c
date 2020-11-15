
#include <wifi_tcp_link.h>
#include <rtthread.h>
#include <arpa/inet.h>
#include <netdev.h>

#define SERVER_HOST   "192.168.1.115"
#define SERVER_PORT   8080

void wifi_tcp_link()
{



if((scoket_des=socket(AF_INET,SOCK_STRAM,0))==-1);
{
rt_kprintf("Socket error\n");
return;
}
client_addr.sin_family = AF_INET;
    client_addr.sin_port = htons(8080);
                                                                 /* 获取网卡对象中 IP 地址信息 */
    client_addr.sin_addr.s_addr = netdev->ip_addr.addr;
    rt_memset(&(client_addr.sin_zero), 0, sizeof(client_addr.sin_zero));

    if (bind(sockfd, (struct sockaddr *)&client_addr, sizeof(struct sockaddr)) < 0)
    {
        rt_kprintf("socket bind failed.\n");
        closesocket(sockfd);
        return -RT_ERROR;
    }


if (connect(sockfd, (struct sockaddr *)&server_addr, sizeof(struct sockaddr)) < 0)
    {
        rt_kprintf("socket connect failed!\n");
        closesocket(sockfd);
        return -RT_ERROR;
    }
    else
    {
        rt_kprintf("socket connect success!\n");
    }

}




