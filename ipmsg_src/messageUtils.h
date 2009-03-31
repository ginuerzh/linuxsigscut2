/*
  *
  *  ������ά����Ϣ�Ĺ��߼�
  *
  */

#ifndef MSG_UTILS_H
#define MSG_UTILS_H

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>

typedef unsigned long command_word;
/*typedef struct command_word{
	char base;
	char option[3];
}command_word;*/


typedef struct message{
	int version;//�汾��
	int packet_num;//�����
	char sender_name[30];//����������
	char sernder_host_name[30];//������������
	command_word command;	//������
	char extra_msg[100];//������Ϣ
	struct sockaddr_in sender_addr;
	struct message* next;//��һ����Ϣ��ָ��
}msg;


/*
  *
  *  ������Ϣ�б�, ������һ��ͷ��㣬��������Ϣ
  *  ����:  ��
  *  ����ֵ: ����
  *
  */
void create_msg_list();

/*
  *
  *  ������Ϣ
  *  ����:  �汾�š�����š��������������������������������֡�������Ϣ
  *  ����ֵ: ����
  *
  */
void insert_msg(int version, int packet_num, char sender_name[], char sender_host_name[], command_word comman, char extra_msg[], struct sockaddr_in sender_addr);


/*
  *
  *  ɾ����һ����Ϣ
  *  ����:  ��
  *  ����ֵ:  ����
  *
  */
void delete_first_msg();

/*
  *
  *  ��ȡ��Ϣ
  *
  */
int get_msg(msg *m);

/*
  *
  * ��ʾ��Ϣ
  * ����:  ��
  * ����ֵ:  ����
  */
void show_msg_list();

#endif
