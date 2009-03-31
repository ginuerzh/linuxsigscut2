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

//��¼
void login();

//����UDP ���ݰ�
void parse_udp(char* udp, int len, struct sockaddr_in sender_addr);

//����UDP ���ݰ�
void* recv_udp_packets_thread();

//������Ϣ��
void* process_messages_thread();

#endif

