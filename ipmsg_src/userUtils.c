/*
  *
  * 操作和维护用户列表的工具集
  *
  *//*
  *
  * 操作和维护用户列表的工具集
  *
  */

#include "userUtils.h"
#include "main.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern socket_fd udp_sockfd;
extern struct sockaddr_in my_address;

//用户列表表头和表尾，表头存放当前用户自身的信息
user* user_list_head = NULL;
user* user_list_tail = NULL;

void create_user_list(){
	//将自己添加到用户列表表头
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
	printf("\nuser name           |host name            |load name           |IP                  ");
	for(p = user_list_head; p != NULL; p = p->next){
		printf("\n%-20s|%-20s|%-20s|%-20s", p->user_name, p->host_name, p->load_name,inet_ntoa((p->address).sin_addr ));
	}
}



