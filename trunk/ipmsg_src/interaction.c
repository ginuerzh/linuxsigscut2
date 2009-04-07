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

//�����û�����
void user_interaction(){
	//show_user_list();
	//show_command_list();
	process_input();
}


//��ʾ�����б�
void show_command_list(){
	int i;
	printf("\n----------------------------------------------command list-------------------------------------------");
	printf("\nCommand        |description");
	for(i = 0; i < 8; i++){
		printf("\n%-15s %-20s", command_list[i], command_desc[i]);
	}
}

//�����û�����
void process_input(){
	bool exit =  false;
	char input[50];
	char history[10][50];//������ʷ��¼���ܣ�����չ......
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



//��ʾ������Ϣ

void show_help_information(){
	printf("\ni am help information.");
	show_command_list();
	show_msg_list();
}


//ʵ��Linux �µ�getch����:
//�ܼ�� PageUP PageDown�Լ�Arrows�Ȱ�����F1, F2�ȹ��ܼ���
//�ᱻ���ͳ�����һ���ַ����С����ܵ�ʵ����ͨ��ioctl�����ն˵����ԡ�--��������

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


