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

#ifndef MAIN_H
#define MAIN_H 

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>

typedef int socket_fd;

//��¼
void login();

//����UDP ���ݰ�
void parse_udp(char* udp, int len, struct sockaddr_in sender_addr);

//����UDP ���ݰ�
void* recv_udp_packets_thread();

//������Ϣ��
void* process_messages_thread();

#endif

