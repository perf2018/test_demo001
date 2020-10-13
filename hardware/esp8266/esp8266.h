#ifndef __ESP8266_H__
#define __ESP8266_H__

#include "stm32f4xx.h"

typedef void (*wifi_recv_handler)(char *buf, int len);

extern void set_wifi_recv_handler(wifi_recv_handler h);
extern void esp8266_init(void);//��ʼ��esp8266
extern int esp8266_link_wifi(char *ssid, char *passwd);//����wifi
extern uint32_t esp8266_connect(char *ip, char *port);//��������
extern uint32_t esp8266_disconnect(void);//�Ͽ�����
extern uint32_t esp8266_send(char *msg, char *len);//��������
extern void dataHandler(unsigned char c);

#endif

