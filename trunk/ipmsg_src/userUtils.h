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
