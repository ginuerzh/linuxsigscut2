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
  *  IPMsg协议源文件
  *
  */

#include "ipmsg_protocol.h"
#include "ipmsg.h"
#include "core.h"
#include "userUtils.h"

#include <sys/time.h>
#include <unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<sys/types.h>
#include<netdb.h>


extern socket_fd udp_sockfd;

/*
  *
  *  发送udp数据包
  *  参数:暂时想到的是命令字、附加消息，待扩展
  *  返回值: 0表示成功，-1失败
  */
int send_udp_packet(command_word command, char extra_msg[], struct sockaddr_in client_addr)
{
	user own;
	get_own_msg(&own);
	char send_buf[COMLEN];
	int buf_len, status = 0;
	int cur_time = (int)time((time_t *)NULL);//获取系统时间
	
	switch(command & 0x000000FF){//处理消息，待完成......
		case IPMSG_NOOPERATION: //不进行任何操作
			
			break;
		case IPMSG_BR_ENTRY:
			
			break;
		case IPMSG_BR_EXIT:
			
			break;
		case IPMSG_ANSENTRY:
			buf_len = sprintf(send_buf, "1:%d:%s:%s:%u:%s", 
					cur_time, own.user_name, own.host_name, (unsigned int)command, own.load_name);
			status = udp_packer(send_buf, buf_len, client_addr);
			break;
		case IPMSG_RECVMSG:
			buf_len = sprintf(send_buf, "1:%d:%s:%s:%u:%s", 
					cur_time, own.user_name, own.host_name, (unsigned int)command, extra_msg);
			status = udp_packer(send_buf, buf_len, client_addr);
			break;
		case IPMSG_SENDMSG:
			buf_len = sprintf(send_buf, "1:%d:%s:%s:%u:%s", 
					cur_time, own.user_name, own.host_name, (unsigned int)command, extra_msg);
			status = udp_packer(send_buf, buf_len, client_addr);
			break;
		default:
			status = -1;
			break;
	}
	return status;
}

/* 接收消息 */
void recv_msg(msg m)
{
	if((m.command & IPMSG_SENDCHECKOPT) == IPMSG_SENDCHECKOPT) {
		char extra_msg[100];
		sprintf(extra_msg, "%i", m.packet_num);
		send_udp_packet(IPMSG_RECVMSG, extra_msg, m.sender_addr);
	}
}

int send_msg_packet(const char *msg_text, size_t msg_len, int flags, 
			struct sockaddr_in client_addr)
{
	unsigned long send_command = IPMSG_SENDMSG;
	if (flags == 1) {
		send_command |= IPMSG_SENDCHECKOPT;
	}
	if (flags == 2) {
		send_command |= IPMSG_SENDCHECKOPT;
		send_command |= IPMSG_SECRETOPT;
	}
	send_udp_packet(send_command, msg_text, client_addr);
	printf("Send success!");
	return 0;
}


/*
 *  put the message into a udp package and send it
 *  return: 0 if succeeded, -1 otherwise
 */
int udp_packer_ip(char *message, int message_len, char *ip_address, int port)
{
	struct sockaddr_in address;
	bzero(&address, sizeof(address));
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = inet_addr(ip_address);
	address.sin_port = htons(port);

	int ret = udp_packer(message, message_len, address);

	return ret;
}


/*
 *  put the message into a udp package and send it
 *  return: 0 if succeeded, -1 otherwise
 */
int udp_packer(char *message, int message_len, struct sockaddr_in address)
{
	int my_socket;
	int sendto_rt;

	my_socket = socket(AF_INET, SOCK_DGRAM, 0);
	if (my_socket == -1){
		perror("\nsocket() fail");
		return -1;
	}
	sendto_rt = sendto(my_socket, message, message_len, 0,
					(struct sockaddr *)&address, sizeof(address));
	if (sendto_rt == -1){
		perror("\nsendto() fail");
		return -1;
	}

	close(my_socket);

	return 0;
}


/*
 *  分析UDP数据包, 并把结果保存在消息列表
 */
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


/*
 *  put the message into a udp BROADCAST package and send it
 *  it's DIFFERENT from function udp_packer & udp_packer_ip
 *
 *  return: 0 if succeeded, -1 otherwise
 */
int udp_broadcast_packer(char *message, int len, int port)
{
	int socket_br;
	struct sockaddr_in their_addr;
	struct in_addr addr;
	struct hostent *he;
	int broadcast = 1;

	if( inet_aton("255.255.255.255", &addr) == 0) {
		he = gethostbyname("255.255.255.255"); //Domain
		addr.s_addr = (*(unsigned int *)*he->h_addr_list[0]);
	}

	if( (socket_br = socket(AF_INET, SOCK_DGRAM, 0)) == -1 ) {
		perror("socket function!\n");
		return -1;
	}

	if( setsockopt(socket_br, SOL_SOCKET, SO_BROADCAST, &broadcast, sizeof(broadcast)) == -1) {
		perror("setsockopt function!\n");
		return -1;
	}

	their_addr.sin_family = AF_INET;
	their_addr.sin_port = htons(port);
	their_addr.sin_addr = addr;

	if( sendto( socket_br, message, len, 0, (struct sockaddr *)&their_addr, 
					sizeof(struct sockaddr) ) == -1) {
		perror("sendto function!\n");
		return -1;
	}

	close(socket_br);

	return 0;
}
