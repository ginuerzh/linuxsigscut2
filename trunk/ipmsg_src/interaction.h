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

#ifndef INTERACTION_H
#define INTERACTION_H

#define true 1;
#define false 0;
typedef short int bool;

#define MATCH(n) 0 == strcmp(input, command_list[n]) 

#include "messageUtils.h"

/* 用户交互函数 */
void user_interaction();

/* 处理用户输入 */
void process_input();


/* 显示帮助信息 */
void show_help_information();


/* 显示命令列表 */
void show_command_list();

//自定义Linux 下的getch函数
char getch();

/* 接收消息 */
void recv_msg(msg m);

/* 显示接收到的消息 */
void show_recv_msg();

/* 显示所有接收到的消息 */
void show_all_recv_msg();

/*发送消息*/
int send_msg();

#endif
