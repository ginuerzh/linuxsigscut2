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
  *  IPMsgЭ��Դ�ļ�
  *
  */

#include "ipmsg_protocol.h"
#include "ipmsg.h"
#include "main.h"
#include "userUtils.h"
#include <sys/time.h>
#include <unistd.h>

extern socket_fd udp_sockfd;

/*
  *
  *  ����udp���ݰ�
  *  ����:��ʱ�뵽���������֡�������Ϣ������չ
  *  ����ֵ:����
  */
void send_udp_packet(command_word command, char extra_msg[], struct sockaddr_in client_addr)
{
	user own;
	get_own_msg(&own);
	char send_buf[COMLEN];
	int buf_len;
	int client_addr_len;
	int cur_time = (int)time((time_t *)NULL);//��ȡϵͳʱ��
	
	switch(command & 0x000000FF){//������Ϣ�������......
		case IPMSG_NOOPERATION: //�������κβ���
			
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
		default:

			break;
	}	
}

/* ������Ϣ */
void recv_msg(msg m)
{
	if((m.command & IPMSG_SENDCHECKOPT) == IPMSG_SENDCHECKOPT) {
		char extra_msg[100];
		sprintf(extra_msg, "%i", m.packet_num);
		send_udp_packet(IPMSG_RECVMSG, extra_msg, m.sender_addr);
	}
}

