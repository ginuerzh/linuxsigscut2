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
  *  操作和维护消息的工具集
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
	int version;//版本号
	int packet_num;//包编号
	char sender_name[30];//发送者姓名
	char sernder_host_name[30];//发送者主机名
	command_word command;	//命令字
	char extra_msg[100];//附加信息
	struct sockaddr_in sender_addr;
	struct message* next;//下一条消息的指针
}msg;


/*
  *
  *  建立消息列表, 即创建一个头结点，包含空信息
  *  参数:  空
  *  返回值: 待定
  *
  */
void create_msg_list();

/*
  *
  *  插入消息
  *  参数:  版本号、包编号、发送者姓名、发送者主机名、命令字、附加信息
  *  返回值: 待定
  *
  */
void insert_msg(int version, int packet_num, char sender_name[], char sender_host_name[], command_word comman, char extra_msg[], struct sockaddr_in sender_addr);


/*
  *
  *  删除第一条消息
  *  参数:  空
  *  返回值:  待定
  *
  */
void delete_first_msg();

/*
  *
  *  获取消息
  *
  */
int get_msg(msg *m);

/*
  *
  * 显示消息
  * 参数:  空
  * 返回值:  待定
  */
void show_msg_list();

/* 插入接收信息 */
void insert_recv_msg(msg m);


/* 取接收消息 */
int get_recv_msg(msg *m);

/* 获取接收消息总数 */
int get_recv_msg_count();



#endif
