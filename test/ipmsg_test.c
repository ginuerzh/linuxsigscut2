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

#include "ipmsg_test.h"
#include "../core/ipmsg.h"
#include "../core/ipmsg_protocol.h"
#include "../core/userUtils.h"
#include "../core/messageUtils.h"
#include "../core/core.h"
#include "../core/network.h"

#include <stdio.h>
#include <string.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <pthread.h>

bool quit = false;

const char* command_list[] = {"list", "showuser", "sendmsg", "sendfile", "recvfile", "reflesh", "exit", 
			      "help", "recvmsg", "recvallmsg", "sendmsg"};
const char* command_desc[] = {"show command list", "show user list", "send message", "send file", 
			      "receive file", "reflesh the user list", "exit", "show help information", 
			      "display one message from message list", "display all the messages from message list", "send message"};

const int command_num = 11;

//处理用户输入
void user_interaction()
{
	//show_user_list();
	//show_command_list();
	printf("\ntip: you can use [list] command to display the command list.\n");
	process_input();
}


//显示命令列表
void show_command_list()
{
	int i;
	printf("\n----------------------------------------------command list-------------------------------------------");
	printf("\nCommand        |description");
	for(i = 0; i < command_num; i++){
		printf("\n%-15s %-20s", command_list[i], command_desc[i]);
	}
}

//处理用户输入
void process_input()
{
	bool exit =  false;
	char input[50];
	//char history[10][50];//增加历史记录功能，待扩展......
	char c;
	int i;
	while(0 == exit) {
		printf("\nIPMSG >");
		fflush(stdout);
		//c = getch();
		i = 0;
		do {
			fflush(stdout);
			fflush(stdin);
			c = getch();
			if(c == 127 && i > 0) {
				printf("\b \b");
				input[i] = '\0';
				i--;
			}
			else if((c >= 'a' && c <= 'z') || (c >= '0' && c <= '9')) {
				//printf("[a-z]%c", c);
				putchar(c);
				input[i] = c;
				i++;
				//scanf("%s", input+1);
			}
			else if(c >= 'A' && c <= 'Z') {
				c += 32;
				//printf("[A-Z]%c", c);
				putchar(c);
				input[i] = c;
				i++;
				//scanf("%s", input+1);
			}
			else if(c == 10 && i == 0 && c !=127) {
				input[i] = c;
			}
			else if(c == 10 && i > 0) {
				input[i] = '\0';
			}
			else if(c >= 24 && c<=27) {
				getch();
				getch();
			}
		}while(c != 10 && i < 50);
		if(input[0] != 10) {
			if(0 == strcmp(input, command_list[0])) {
				show_command_list();
			} 
			else if(0 == strcmp(input, command_list[1])) {
				show_user_list();
			}
			else if(0 == strcmp(input, command_list[2])) {
				send_msg();
			}
			else if(0 == strcmp(input, command_list[3])) {

			}
			else if(0 == strcmp(input, command_list[4])) {

			}
			else if(0 == strcmp(input, command_list[5])) {
				login();
			}
			else if(0 == strcmp(input, command_list[6])) {
				printf("\nPreparing exit ............\n");
				exit = true;
				quit = true;
				fflush(stdout);
				close_udp_socket();

			}
			else if(0 == strcmp(input, command_list[7])) {
				show_help_information();
			}
			else if(0 == strcmp(input, command_list[8])) {
				show_recv_msg();
			}
			else if(0 == strcmp(input, command_list[9])) {
				show_all_recv_msg();
			}
			//else if(MATCH(10)) {
			else if(0 == strcmp(input, command_list[10])) {
				printf("\nplease input the message:\n");
				fflush(stdout);	
			}
			else {
				printf("\ninvalid command");
			}
		}
	}
}



/* 显示帮助信息 */

void show_help_information()
{
	printf("\ni am help information.");
	show_command_list();
	//show_msg_list();
}

/* 显示接收到的消息 */
void show_recv_msg()
{
	msg m;
	if(-1 == get_recv_msg(&m)) {
		printf("\nrecv_msg_list is empty");
	}
	else {
		printf("\n%s: %s", m.sender_name, m.extra_msg);
	}
}

/* 显示所有接收到的消息 */
void show_all_recv_msg()
{
	msg m;
	while(-1 != get_recv_msg(&m)) {
		printf("\n%s: %s", m.sender_name, m.extra_msg);
	}
	printf("\nrecv_msg_list is empty");
}


/* 
 * 实现Linux 下的getch函数:
 * 能检测 PageUP PageDown以及Arrows等按键，F1, F2等功能键，
 * 会被解释成输入一个字符序列。功能的实现是通过ioctl调整终端的属性。--来自网络
 *
 */

char getch()
{
    char ch;
    struct termios save, ne;
    ioctl(0, TCGETS, &save);
    ioctl(0, TCGETS, &ne);
    ne.c_lflag &= ~(ECHO | ICANON);
    ioctl(0, TCSETS, &ne);
    read(0, &ch, 1);
    ioctl(0, TCSETS, &save);
    return ch;
}

int send_msg()
{
	char user_name[30], msg_text[100];
	struct user select_user;
	int flags = 0;

	show_user_list();
	printf("\nPlease input an user's name:\n");
	scanf("%s",user_name);
	getchar(); //Get the newline input from the keyboard. --Yegui
	if(get_user_by_name(user_name, &select_user) != 0){
		printf("\nWrong input! This user is not exist!");
		return 1;
	}
	printf("\nPlease input the message:\n");
	fgets(msg_text, sizeof(msg_text), stdin); //Get the full sentence with a safe way. --Yegui
	printf("\nPlease input the flags:\n");
	scanf("%d",&flags);

	if(send_msg_packet(msg_text, sizeof(msg_text), flags, select_user.address) != 0){
		printf("\nSend failed!");
		return 1;
	}
	return 0;
}


int main(int argc, char *argv[])
{
	pthread_t udp_receiver_thread_id;
	pthread_t tcp_receiver_thread_id;
	pthread_t processor_thread_id;
	
	create_user_list();//创建用户列表
	create_msg_list();//创建消息列表

	//创建接收UDP数据包线程和处理消息线程
	pthread_create(&udp_receiver_thread_id, NULL,
		(void *)*recv_udp_packets_thread, NULL);

	pthread_create(&tcp_receiver_thread_id, NULL,
		(void *)*recv_tcp_packets_thread, NULL);

	pthread_create(&processor_thread_id, NULL, 
		(void *)*process_messages_thread, NULL);

	login();	
	// ************* file test ****************
	/*
	sleep(1);
	char message[1024], ip[]="125.216.243.216";
	char zero = 0;
	int msgLen;
	command_word commd = IPMSG_SENDMSG | IPMSG_FILEATTACHOPT;
		
	msgLen = snprintf(message, 1024, "1_iptux_0#4#5:a:pire:blackbox:%lu:%c10001:file.txt:a:49f5e357:1%c",
			(unsigned long)commd, zero, zero);
	printf("%s\n", message);
	udp_packer_ip(message, msgLen, ip, 2425);
	while (1) {
		sleep(1);
		//show_msg_list();
	}
	*/
	// ************* file test ****************end
	user_interaction();

	
	/*int* retn;
	//等等子线程结束
	if(-1 == pthread_join(receiver_thread_id, (void **)&retn) ||
		-1 == pthread_join(processor_thread_id, (void **)&retn)){
		perror("\nthread error");
	}*/

	//直接取消子线程，不等待
	if (0 != pthread_cancel(udp_receiver_thread_id)) {
		perror("\nThread of udp receiver cancelation failed");
	}

	if (0 != pthread_cancel(tcp_receiver_thread_id)) {
		perror("\nThread of tcp receiver cancelation failed");
	}

	if ( 0 != pthread_cancel(processor_thread_id)) {
		perror("\nThread of processor cancelation failed");
	}
	
	return 0;
}


