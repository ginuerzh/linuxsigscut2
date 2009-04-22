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

#include "core.h"
#include "ipmsg.h"
#include "ipmsg_protocol.h"
#include "userUtils.h"
#include "messageUtils.h"

#include <sys/socket.h>
#include <sys/types.h>
#include <stdio.h>
#include <netinet/in.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>

extern socket_fd udp_sockfd;
extern struct sockaddr_in my_address;
extern bool quit;


void login()
{
	int so_broadcast=1;
	socket_fd client_sockfd;
	struct sockaddr_in client_address;
	int client_addr_len;
	char *user_name, host_name[HOST_NAME_LEN];

	user_name = (char *)getlogin();
	if ( 0 != gethostname(host_name, HOST_NAME_LEN) )
		strcpy(host_name, "HostName");

	client_address.sin_family = AF_INET;
	client_address.sin_port = htons(2425);
	client_address.sin_addr.s_addr = inet_addr("255.255.255.255");
	bzero(&(client_address.sin_zero),8);
	
	setsockopt(udp_sockfd,SOL_SOCKET,SO_BROADCAST,
		&so_broadcast,sizeof(so_broadcast));
	
	command_word command;
	command = IPMSG_BR_ENTRY;
	char send_buf[COMLEN];

	//生成广播消息，应重新设计一个函数来生成消息,待完成......
	int buf_len=sprintf(send_buf, "1:1:%s:%s:%u:%s", user_name, host_name, command, user_name);
	
	client_addr_len = sizeof(client_address);
	if (-1 == sendto(udp_sockfd, send_buf,buf_len, 0, 
		(struct sockaddr*)&client_address, client_addr_len)) {
		perror("\nbroadcast error");
	}
}


//接收UDP数据包的线程
void* recv_udp_packets_thread()
{
	//printf("\nHello,i am recv_udp_packets_thread");
	char recv_buf[COMLEN];
	int buf_len;
	int client_sockfd;
	struct sockaddr_in client_address;
	int client_addr_len = sizeof(client_address);
	
	while (!quit) {
		buf_len = recvfrom(udp_sockfd, recv_buf, COMLEN, 0, 
			(struct sockaddr *)&client_address, &client_addr_len);
		if (buf_len == -1) {
			perror("\nrecv error");
			return 0;
		}
		//printf("\n%s",recv_buf);
		recv_buf[buf_len] = '\0';
		parse_udp(recv_buf, buf_len, client_address);
	}
	return 0;
}

//处理消息的线程
void* process_messages_thread()
{
	//printf("\nHello,i am process_messages_thread");
	msg m;
	while (!quit) {
		if (0 == get_msg(&m)) {
			switch (m.command & 0x000000FF) {//处理消息，待完成......
            case IPMSG_NOOPERATION: //不进行任何操作
                //printf("\ni am IPMSG_NOOPERATION");
                break;
            case IPMSG_BR_ENTRY:
                //printf("\ni am IPMSG_BR_ENTRY");
                //printf("\nsomeone broadcast");
                insert_user(m.sender_name, m.sernder_host_name, m.extra_msg, m.sender_addr);
                send_udp_packet(IPMSG_ANSENTRY, NULL, m.sender_addr);
                break;
            case IPMSG_BR_EXIT:
                //printf("\ni am IPMSG_NOOPERATION");
                break;
            case IPMSG_ANSENTRY:
                //printf("\ni am IPMSG_ANSENTRY");
                insert_user(m.sender_name, m.sernder_host_name, m.extra_msg, m.sender_addr);
                break;
            case IPMSG_SENDMSG:
                //printf("\nrecv one message");
		recv_msg(m);
                insert_recv_msg(m);
		//printf("\n%s",m.extra_msg);
		break;
            case IPMSG_RECVMSG:
            
                break;
            
            default:
                //printf("\ni am default");
                break;
			}
		}
		else {
			//printf("\nmessage list is empty.");
			//sleep(200);//暂时没消息，睡眠等待一会，以免浪费CPU时间
		}
	}
	
	return 0;
}


//处理UDP数据包
void parse_udp(char* udp, int len, struct sockaddr_in sender_addr)
{
	char* end;
	char* start;
	start = udp;
	end = 0;
	char tmp_buf[6][COMLEN/6];
	int tmp_index = 0;

	do {
		end = strpbrk(start, ":");//得到start串中第一个':'号的地址，若没有则返回0
		if (0 != end && end < (udp+len)) {
			strncpy(tmp_buf[tmp_index], start, (int)(end-start));
			tmp_buf[tmp_index][(int)(end-start)] = '\0';
			start = end + 1;
			tmp_index++;
		}
	} while (0 != end);

	strcpy(tmp_buf[tmp_index], start);

	//将分析结果插入消息列表
	insert_msg(atoi(tmp_buf[0]), atoi(tmp_buf[1]), tmp_buf[2], tmp_buf[3], 
		strtoul(tmp_buf[4], NULL, 10), tmp_buf[5], sender_addr);
	//show_msg_list();
	//printf("\nfinish");
}

