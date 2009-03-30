/*
  *
  *  操作和维护消息的工具集
  *
  */


#include "messageUtils.h"
#include <stdlib.h>
#include <string.h>

extern struct sockaddr_in my_address;

//消息列表
msg* msg_list_head = NULL;
msg* msg_list_tail = NULL;

/*
  *
  *  建立消息列表, 即创建一个头结点
  *  参数:  空
  *  返回值: 待定
  *
  */
void create_msg_list(){
	msg_list_head = malloc(sizeof(msg));
	msg_list_tail = msg_list_head;
	msg_list_head->version = 1;
	msg_list_head->packet_num = 0;
	strcpy(msg_list_head->sender_name, "v_bmouth");
	strcpy(msg_list_head->sernder_host_name, "v_HP");
	msg_list_head->command = 0;
	strcpy(msg_list_head->extra_msg, "v_bmouth");
	msg_list_head->sender_addr = my_address;
	msg_list_tail->next = NULL;
}

/*
  *
  *  插入消息
  *  参数:  版本号、包编号、发送者姓名、发送者主机名、命令字、附加信息
  *  返回值: 待定
  *
  */
void insert_msg(int version, int packet_num, char sender_name[], char sender_host_name[], 
					command_word comman, char extra_msg[], struct sockaddr_in sender_addr){
	if(NULL == msg_list_head || NULL == msg_list_tail)
		create_msg_list();
	msg* p;
	p = malloc(sizeof(msg));
	p->version = version;
	p->packet_num = packet_num;
	strcpy(p->sender_name, sender_name);
	strcpy(p->sernder_host_name, sender_host_name);
	p->command = comman;
	strcpy(p->extra_msg, extra_msg);
	p->sender_addr = sender_addr;
	msg_list_tail->next = p;
	msg_list_tail = p;
	msg_list_tail->next = NULL;
}


/*
  *
  *  删除第一条消息
  *  参数:  空
  *  返回值:  待定
  *
  */
void delete_first_msg(){
	if(msg_list_tail != msg_list_head && NULL != msg_list_head && NULL != msg_list_tail){
		msg* p;
		p = msg_list_head->next; //删除第二个节点
		msg_list_head->next = p->next;
		if(NULL == msg_list_head->next)
			msg_list_tail = msg_list_head;
		free(p);
	}
}


/*
  *
  *  获取消息
  *
  */
int get_msg(msg *m){
	if(msg_list_tail != msg_list_head && msg_list_head != NULL && msg_list_tail != NULL){
		*m = *( msg_list_head->next); 
		delete_first_msg();
		//printf("\nget msg success.");
		return 0;
	}else{
		return -1;
	}
}



/*
  *
  * 显示消息
  * 参数:  空
  * 返回值:  待定
  */
void show_msg_list(){
	msg* p;
	printf("\n----------------------------------------------msg list-------------------------------------------");
	printf("\nversion   |packet number       |sender name         |sender host name    |command             |extra msg           |sender IP");
	for(p = msg_list_head; p != NULL; p = p->next){
		printf("\n%-10d|%-20d|%-20s|%-20s|%-20u|%-20s|%20s", p->version, p->packet_num, p->sender_name, p->sernder_host_name, p->command, p->extra_msg,inet_ntoa((p->sender_addr).sin_addr ));
	}
}

