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
#include <unistd.h>

extern bool quit;

void login()
{
	command_word command;
	command = IPMSG_BR_ENTRY;
	char send_buf[COMLEN];
	char *user_name, host_name[HOST_NAME_LEN];

	user_name = (char *)getlogin();
	if ( 0 != gethostname(host_name, HOST_NAME_LEN) )
		strcpy(host_name, "HostName");

	//生成广播消息，应重新设计一个函数来生成消息,待完成......
	int buf_len=sprintf(send_buf, "1:1:%s:%s:%u:%s", 
			user_name, host_name, (unsigned int)command, user_name);
	
	udp_broadcast_packer(send_buf, buf_len, DEFAULT_PORT);
}


//接收UDP数据包的线程
void* recv_udp_packets_thread()
{
	int udp_socket;
	struct sockaddr_in my_address, client_address;
	char recv_buf[COMLEN];
	int buf_len;
	int client_addr_len = sizeof(client_address);

	udp_socket = socket(AF_INET,SOCK_DGRAM,0);
	if (udp_socket == -1) {
		printf("socket() ERROR!!!\n");
		quit = 1;
	}

	bzero(&my_address, sizeof(my_address));
	my_address.sin_family = AF_INET;
	my_address.sin_addr.s_addr = htonl(INADDR_ANY);
	my_address.sin_port = htons(DEFAULT_PORT);
 
	int bd = bind(udp_socket, (struct sockaddr *)&my_address, 
			(socklen_t)(sizeof(my_address)));
	if (bd == -1) {
		printf("bind() ERROR!!!\n");
		quit = 1;
	}

	while (!quit) {
		buf_len = recvfrom(udp_socket, recv_buf, COMLEN, 0, 
			(struct sockaddr *)&client_address, &client_addr_len);
		if (buf_len < 0) {
			perror("recvfrom() ERROR!!\n");
			continue;
		}
		recv_buf[buf_len] = '\0';
		parse_udp(recv_buf, buf_len, client_address);
	}
	close(udp_socket);
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

