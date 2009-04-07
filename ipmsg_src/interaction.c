/*
  *
  *
  *
  */

#include "interaction.h"
#include "ipmsg.h"
#include "ipmsg_protocol.h"
#include "userUtils.h"
#include "messageUtils.h"
#include <stdio.h>
#include <string.h>
#include <sys/ioctl.h>
#include <termios.h>


extern bool quit;

const char* command_list[] = {"list", "showuser", "sendmsg", "sendfile", "recvfile", "reflesh", "exit", "help"};
const char* command_desc[] = {"show command list", "show user list", "send message", "send file", 
	"receive file", "reflesh the user list", "exit", "show help information"};

//处理用户输入
void user_interaction(){
	//show_user_list();
	//show_command_list();
	process_input();
}


//显示命令列表
void show_command_list(){
	int i;
	printf("\n----------------------------------------------command list-------------------------------------------");
	printf("\nCommand        |description");
	for(i = 0; i < 8; i++){
		printf("\n%-15s %-20s", command_list[i], command_desc[i]);
	}
}

//处理用户输入
void process_input(){
	bool exit =  false;
	char input[50];
	char history[10][50];//增加历史记录功能，待扩展......
	char c;
	int i,j = 0;
	while(0 == exit){
		printf("\nIPMSG >");
		fflush(stdout);
		//c = getch();
		i = 0;
		do{
			fflush(stdout);
			fflush(stdin);
			c = getch();
			if(c == 127 && i > 0){
				printf("\b \b");
				input[i] = '\0';
				i--;
			}else if(c >= 'a' && c <= 'z' || c >= '0' && c <= '9'){
				//printf("[a-z]%c", c);
				putchar(c);
				input[i] = c;
				i++;
				//scanf("%s", input+1);
			}else if(c >= 'A' && c <= 'Z'){
				c += 32;
				//printf("[A-Z]%c", c);
				putchar(c);
				input[i] = c;
				i++;
				//scanf("%s", input+1);
			}else if(c == 10 && i == 0 && c !=127){
				input[i] = c;
			}else if(c == 10 && i > 0){
				input[i] = '\0';
			}else if(c >= 24 && c<=27){
				getch();
				getch();
			}
		}while(c != 10);
		if(input[0] != 10){
			if(0 == strcmp(input, command_list[0])){
				show_command_list();
			}else if(0 == strcmp(input, command_list[1])){
				show_user_list();
			}else if(0 == strcmp(input, command_list[2])){

			}else if(0 == strcmp(input, command_list[3])){

			}else if(0 == strcmp(input, command_list[4])){

			}else if(0 == strcmp(input, command_list[5])){
				login();
			}else if(0 == strcmp(input, command_list[6])){
				printf("Preparing exit ............\n");
				exit = true;
				quit = true;
				fflush(stdout);
			}else if(0 == strcmp(input, command_list[7])){
				show_help_information();
			}else{
				printf("\nerror input!");
			}
		}
	}
}



//显示帮助信息

void show_help_information(){
	printf("\ni am help information.");
	show_command_list();
	show_msg_list();
}


//实现Linux 下的getch函数:
//能检测 PageUP PageDown以及Arrows等按键，F1, F2等功能键，
//会被解释成输入一个字符序列。功能的实现是通过ioctl调整终端的属性。--来自网络

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


