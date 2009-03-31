/*
  *
  * main.h...
  *
  */
#ifndef MAIN_H
#define MAIN_H 

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>

typedef int socket_fd;

//登录
void login();

//分析UDP 数据包
void parse_udp(char* udp, int len, struct sockaddr_in sender_addr);

//接收UDP 数据包
void* recv_udp_packets_thread();

//处理消息的
void* process_messages_thread();

#endif

