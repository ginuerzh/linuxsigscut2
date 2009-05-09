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

#include "ipmsg.h"
#include "network.h"

#include <sys/socket.h>
#include <sys/types.h>
#include <stdio.h>
#include <netinet/in.h>
#include <string.h>

/* initial the socket */
int init_socket(socket_fd *sock, int type)
{
	struct sockaddr_in my_address;

	*sock = socket(AF_INET, type, 0);
	if (*sock == -1) {
		printf("socket() ERROR!!!\n");
		return -1;
	}

	bzero(&my_address, sizeof(my_address));
	my_address.sin_family = AF_INET;
	my_address.sin_addr.s_addr = htonl(INADDR_ANY);
	my_address.sin_port = htons(DEFAULT_PORT);
 
	int bd = bind(*sock, (struct sockaddr *)&my_address, 
			(socklen_t)(sizeof(my_address)));
	if (bd == -1) {
		printf("bind() ERROR!!!\n");
		return -1;
	}

	return 0;
}



/* initial the udp socket */
int init_udp_socket(socket_fd *sock)
{
	return init_socket(sock, SOCK_DGRAM);
}


/* return the udp socket */
int get_udp_socket()
{
	static socket_fd udp_sock = -1;
	if (udp_sock == -1) {
		if ( -1 == init_udp_socket(&udp_sock) ) // only run once
			return -1;
	}

	return udp_sock;
}


/* free the udp socket */
int close_udp_socket()
{
	socket_fd udp_sock = get_udp_socket();
	if ( -1 == close(udp_sock) ) {
		perror("close() error!!\n");	
		return -1;
	}
	return 0;
}


/* initial the tcp socket */
int init_tcp_socket(socket_fd *sock)
{
	return init_socket(sock, SOCK_STREAM);
}


/* return the tcp socket */
int get_tcp_socket()
{
	static socket_fd tcp_sock = -1;
	if (tcp_sock == -1) {
		if ( -1 == init_tcp_socket(&tcp_sock) ) // only run once
			return -1;
	}

	return tcp_sock;
}


/* free the tcp socket */
int close_tcp_socket()
{
	socket_fd tcp_sock = get_tcp_socket();
	if ( -1 == close(tcp_sock) ) {
		perror("close() error!!\n");	
		return -1;
	}
	return 0;
}

