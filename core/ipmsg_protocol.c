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

extern socket_fd udp_sockfd;

/*
  *
  *  发送udp数据包
  *  参数:暂时想到的是命令字、附加消息，待扩展
  *  返回值:待定
  */
void send_udp_packet(command_word command, char extra_msg[], struct sockaddr_in client_addr)
{
	user own;
	get_own_msg(&own);
	char send_buf[COMLEN];
	int buf_len;
	int client_addr_len;
	int cur_time = (int)time((time_t *)NULL);//获取系统时间
	
	switch(command & 0x000000FF){//处理消息，待完成......
		case IPMSG_NOOPERATION: //不进行任何操作
			
			break;
		case IPMSG_BR_ENTRY:
			
			break;
		case IPMSG_BR_EXIT:
			
			break;
		case IPMSG_ANSENTRY:
			buf_len = sprintf(send_buf, "1:%d:%s:%s:%u:%s", cur_time, own.user_name, own.host_name, command, own.load_name);
			client_addr_len = sizeof(client_addr);
			if(-1 == sendto(udp_sockfd, send_buf,buf_len, 0, (struct sockaddr*)&client_addr, client_addr_len)){
				perror("\nbroadcast error");
			}
			break;
		case IPMSG_RECVMSG:
			buf_len = sprintf(send_buf, "1:%d:%s:%s:%u:%s", cur_time, own.user_name, own.host_name, command, extra_msg);
			client_addr_len = sizeof(client_addr);
			if(-1 == sendto(udp_sockfd, send_buf, buf_len, 0, (struct sockaddr *)&client_addr, client_addr_len)) {
				perror("\nresponse error");
			}
		case IPMSG_SENDMSG:
			buf_len = sprintf(send_buf, "1:%d:%s:%s:%u:%s", cur_time, own.user_name, own.host_name, command, extra_msg);
			client_addr_len = sizeof(client_addr);
			if(-1 == sendto(udp_sockfd, send_buf, buf_len, 0, (struct sockaddr *)&client_addr, client_addr_len)) {
				perror("\nsend error");
			}
			break;
		default:

			break;
	}	
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

