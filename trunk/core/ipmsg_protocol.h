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

#ifndef IPMSG_PROTOCOL_H
#define IPMSG_PROTOCOL_H

#include "messageUtils.h"


/*
  *
  *  发送udp数据包
  *  参数:暂时想到的是命令字、附加消息，待扩展
  *  返回值:待定
  */
int send_udp_packet(command_word command, char extra_msg[], struct sockaddr_in client_addr);

/*
  *
  *  发送消息数据包
  *  参数:消息文本msg_text  消息长度msg_len  发送地址client_addr 
  *  	  选项： flags 0－默认，1－需要回复，2－封装
  *  返回值: 成功返回0   失败返回1
  */
int send_msg_packet(const char *msg_text, size_t msg_len, int flags, struct sockaddr_in client_addr);

/*
 *  put the message into a udp package and send it
 *  return: 0 if succeeded, -1 otherwise
 */
int udp_packer_ip(char *message, int message_len, char *ip_address, int port);
int udp_packer(char *message, int message_len, struct sockaddr_in address);

/*
 *  分析UDP数据包, 并把结果保存在消息列表
 */
void parse_udp(char* udp, int len, struct sockaddr_in sender_addr);

/*
 *  put the message into a udp BROADCAST package and send it
 *  it's DIFFERENT from function udp_packer & udp_packer_ip
 *
 *  return: 0 if succeeded, -1 otherwise
 */
int udp_broadcast_packer(char *message, int len, int port);
#endif
