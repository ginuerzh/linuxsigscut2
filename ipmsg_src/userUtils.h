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
  * ������ά���û��б�Ĺ��߼�
  *
  */


#ifndef USER_UTILS_H
#define USER_UTILS_H

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>

typedef struct user{
	char user_name[30];//�û���
	char host_name[30];//������
	char group_name[30];//��������
	char load_name[30];//��¼��
	struct sockaddr_in address;//�û���ַ
	struct user* next;
}user;

/*
  *
  * �����û��б�
  * ����:  ��
  * ����ֵ:  ����
  */
void create_user_list();

/*
  *
  * �����û�
  * ����:  �û���user_name, ������host_name,  ��¼��load_name,  �û���ַaddress
  * ����ֵ:  ����
  */
void insert_user(char user_name[], char host_name[], char load_name[], struct sockaddr_in address);

/*
  *
  * ɾ���û�--�����壬Ӧ�����û�IPɾ��
  * ����:  noΪ���û����б��е����
  * ����ֵ:  ����
  */
void delete_user_by_no(int no);

/*
  *
  * ��ʾ�û�
  * ����:  ��
  * ����ֵ:  ����
  */
void show_user_list();


/*
  *
  * �õ��û��������Ϣ
  * ����:  ��
  * ����ֵ:  ����
  */
void get_own_msg();

#endif
