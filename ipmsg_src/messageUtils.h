/* Copyright (C) 2009 Linux SIG of SCUT
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

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

/* ���������Ϣ */
void insert_recv_msg(msg m);


/* ȡ������Ϣ */
int get_recv_msg(msg *m);

/* ��ȡ������Ϣ���� */
int get_recv_msg_count();



#endif
