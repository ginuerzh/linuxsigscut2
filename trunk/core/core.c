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

#include "network.h"
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
	socket_fd udp_socket;
	struct sockaddr_in client_address;
	char recv_buf[COMLEN];
	int buf_len;
	int client_addr_len = sizeof(client_address);

	udp_socket = get_udp_socket();
	if (udp_socket == -1) {
		printf("recv_udp_packets_thread() ERROR!!!\n");
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
			sleep(1);//暂时没消息，睡眠等待一会，以免浪费CPU时间
		}
	}
	
	return 0;
}


//wait for the incoming TCP connection
void* recv_tcp_packets_thread()
{
	socket_fd new_tcp, tcp_socket;
	char recv_buf[COMLEN];
	int buf_len;
	struct sockaddr_in claddr;
	int claddrlen = sizeof(claddr);

	tcp_socket = get_tcp_socket();

	if (listen(tcp_socket, 5)) {
		printf("listen() error!\n");	
		quit = 1;
	}

	/*TODO: create a new child process when accept a connection*/
	while (!quit) {
		new_tcp = accept(tcp_socket, (struct sockaddr *) &claddr, &claddrlen);
		if ( new_tcp < 0) {
			printf("accept() error! \n");
			continue;
		}

		while (!quit) {
			if ( (buf_len = read(new_tcp, recv_buf, COMLEN) ) < 0) {
				printf("read() error!\n");
				close(new_tcp);
				break;
			}
			if (buf_len == 0) {
				close(new_tcp);
				break;
			}
			recv_buf[buf_len] = 0;
			printf("got message:%s\n", recv_buf);
		}
	}

	return 0;
}


