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

#ifndef NETWORK_H
#define NETWORK_H 

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>

typedef int socket_fd;

/* initial the socket */
int init_socket(socket_fd *sock, int type);

/* initial the udp socket */
int init_udp_socket(socket_fd *sock);

/* return the udp socket */
int get_udp_socket();

/* free the udp socket */
int close_udp_socket();

/* initial the tcp socket */
int init_tcp_socket(socket_fd *sock);

/* return the tcp socket */
int get_tcp_socket();

/* free the tcp socket */
int close_tcp_socket();

#endif
