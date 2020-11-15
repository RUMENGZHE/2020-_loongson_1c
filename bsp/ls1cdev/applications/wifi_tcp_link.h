
#ifndef __WIFI_TCP_LINK_H
#define __WIFI_TCP_LINK_H

#include <rtthread.h>
#include <arpa/inet.h>
#include <netdev.h>

#define SERVER_HOST   "192.168.1.115"
#define SERVER_PORT   8080

int scoket_des;


void wifi_tcp_link(void);



#endif

