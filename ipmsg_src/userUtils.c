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
  *//*
  *
  * ������ά���û��б�Ĺ��߼�
  *
  */

#include "userUtils.h"
#include "main.h"
#include "interaction.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern socket_fd udp_sockfd;
extern struct sockaddr_in my_address;

//�û��б��ͷ�ͱ�β����ͷ��ŵ�ǰ�û��������Ϣ
user* user_list_head = NULL;
user* user_list_tail = NULL;

void create_user_list(){
	//���Լ���ӵ��û��б��ͷ
	user* tmp_user;
	tmp_user = (user *)malloc(sizeof(user));
	strcpy(tmp_user->user_name, "v_bmouth");
	strcpy(tmp_user->host_name, "v_HP");
	strcpy(tmp_user->load_name, "v_bmouth");
	tmp_user->address = my_address;
	
	user_list_head = tmp_user;
	user_list_tail = tmp_user;
	user_list_tail->next = NULL;
}




void insert_user(char user_name[], char host_name[], char load_name[], struct sockaddr_in address){
	if(NULL == user_list_head ||NULL == user_list_tail)
		create_user_list();
	//����û��Ƿ������б���
	bool exist = false;
	char old_ip[20];
	char new_ip[20];
	inet_ntop(AF_INET, &address.sin_addr, new_ip, 16);
	user* p;
	p = user_list_head;
	while(p != user_list_tail){
		//ʹ��inet_ntop����Ϊ�����̰߳�ȫ�ģ�
		//ʹ��inet_ntoa�Ļ����Ͳ��ܹ���ͬһ�������ļ������������ϯ������inet_ntoa��
		//�����ǵ�һ��inet_ntoaδʹ�ý���֮ǰ����Ҫʹ�õڶ���
		inet_ntop(AF_INET, &(p->address).sin_addr, old_ip, 16);
		//inet_ntop(AF_INET, &address.sin_addr, new_ip, 16);
		if(0 == strcmp(old_ip, new_ip)){
			exist = true;
			break;
		}
		p = p->next;
	}
	if(!exist ){
		inet_ntop(AF_INET, &(p->address).sin_addr, old_ip, 16);
		//inet_ntop(AF_INET, &address.sin_addr, new_ip, 16);
		if(0 == strcmp(old_ip, new_ip)){
			exist = true;
		}
	}

	if(!exist){
		user* tmp_user;
		tmp_user = (user *)malloc(sizeof(user));
		strcpy(tmp_user->user_name, user_name);
		strcpy(tmp_user->host_name, host_name);
		strcpy(tmp_user->load_name, load_name);
		tmp_user->address = address;
	
		user_list_tail->next = tmp_user;
		user_list_tail = tmp_user;
		user_list_tail->next = NULL;
	}
}

void delete_user_by_no(int no){
	if(no > 1){
		int i;
		user* p = user_list_head;
		for(i = 1; i < no - 1 && p->next != NULL; i++){
			p = p->next;
		}
		if(p->next != NULL){
			user* q;
			q = p->next;
			p->next = q->next;
			if(p->next == NULL)
				user_list_tail = p;
			free(q);
		}else{
			printf("\nerror input: the NO exceed upper limit.");
		}
	}else if(1 == no){
		printf("\nyou can't delete yourself!");
	}else{
		printf("\nerror input: the NO is under lower limit.");
	}
}


void show_user_list(){
	user* p;
	printf("\n-------------------user list--------------------");
	printf("\nuser name           |host name           |load name           |IP                  ");
	for(p = user_list_head; p != NULL; p = p->next){
		printf("\n%-20s|%-20s|%-20s|%-20s", p->user_name, p->host_name, p->load_name,inet_ntoa((p->address).sin_addr ));
	}
}

void get_own_msg(user* own){
	if(NULL == user_list_head ||NULL == user_list_tail)
		create_user_list();
	*own = *user_list_head;
}



