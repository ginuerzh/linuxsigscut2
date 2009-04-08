/*
  *	������
  *
  */

#include "main.h"
#include "ipmsg.h"
#include "ipmsg_protocol.h"
#include "userUtils.h"
#include "messageUtils.h"
#include "interaction.h"

#include <sys/socket.h>
#include <sys/types.h>
#include <stdio.h>
#include <netinet/in.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>


socket_fd udp_sockfd;
struct sockaddr_in my_address;


bool quit = false;

int main(int argc, char *argv[]){

	pthread_t receiver_thread_id;
	pthread_t processor_thread_id;
	
	udp_sockfd = socket(AF_INET,SOCK_DGRAM,0);
	my_address.sin_family = AF_INET;
	my_address.sin_addr.s_addr = htonl(INADDR_ANY);
	my_address.sin_port = htons(2425);
	bind(udp_sockfd, (struct sockaddr *)&my_address, (socklen_t)(sizeof(my_address)));//��UDP socket

	create_user_list();//�����û��б�
	create_msg_list();//������Ϣ�б�
	login();	

	//��������UDP���ݰ��̺߳ʹ�����Ϣ�߳�
	pthread_create(&receiver_thread_id, NULL, (void *)*recv_udp_packets_thread, NULL);
	pthread_create(&processor_thread_id, NULL, (void *)*process_messages_thread, NULL);

	user_interaction();
	
	/*int* retn;
	//�ȵ����߳̽���
	if(-1 == pthread_join(receiver_thread_id, (void **)&retn) ||
		-1 == pthread_join(processor_thread_id, (void **)&retn)){
		perror("\nthread error");
	}*/

	//ֱ��ȡ�����̣߳����ȴ�
	if(0 != pthread_cancel(receiver_thread_id)){
		perror("\nThread of receiver cancelation failed");
	}else if( 0 != pthread_cancel(processor_thread_id)){
		perror("\nThread of processor cancelation failed");
	}
	
	return 0;
}

void login(){
	int so_broadcast=1;
	socket_fd client_sockfd;
	struct sockaddr_in client_address;
	int client_addr_len;
	client_address.sin_family = AF_INET;
	client_address.sin_port = htons(2425);
	client_address.sin_addr.s_addr =  inet_addr("255.255.255.255");
	bzero(&(client_address.sin_zero),8);
	
	setsockopt(udp_sockfd,SOL_SOCKET,SO_BROADCAST,&so_broadcast,sizeof(so_broadcast));
	
	command_word command;
	command = IPMSG_BR_ENTRY;
	char send_buf[COMLEN];

	//���ɹ㲥��Ϣ��Ӧ�������һ��������������Ϣ,�����......
	int buf_len=sprintf(send_buf, "1:1:userName:hostName:%u:nickname", command);
	
	client_addr_len = sizeof(client_address);
	if(-1 == sendto(udp_sockfd, send_buf,buf_len, 0, (struct sockaddr*)&client_address, client_addr_len)){
		perror("\nbroadcast error");
	}	
}



//����UDP ���ݰ�
void* recv_udp_packets_thread(){
	//printf("\nHello,i am recv_udp_packets_thread");
	char recv_buf[COMLEN];
	int buf_len;
	int client_sockfd;
	struct sockaddr_in client_address;
	int client_addr_len = sizeof(client_address);
	
	while(!quit){
		if(-1 == (buf_len = recvfrom(udp_sockfd, recv_buf, COMLEN, 0, (struct sockaddr *)&client_address, &client_addr_len))){
			perror("\nrecv error");
			return 0;
		}
		//printf("\n%s",recv_buf);
		recv_buf[buf_len] = '\0';
		parse_udp(recv_buf, buf_len, client_address);
	}
	return 0;
}

//������Ϣ��
void* process_messages_thread(){
	//printf("\nHello,i am process_messages_thread");
	msg m;
	while(!quit){
		if(0 == get_msg(&m)){
			switch(m.command & 0x000000FF){//������Ϣ�������......
				case IPMSG_NOOPERATION: //�������κβ���
					//printf("\ni am IPMSG_NOOPERATION");
					break;
				case IPMSG_BR_ENTRY:
					//printf("\ni am IPMSG_BR_ENTRY");
					printf("\nsomeone broadcast");
					insert_user(m.sender_name, m.sernder_host_name, m.extra_msg, m.sender_addr);
					send_udp_packet(IPMSG_ANSENTRY, NULL, m.sender_addr);
					break;
				case IPMSG_BR_EXIT:
					//printf("\ni am IPMSG_NOOPERATION");
					break;
				case IPMSG_ANSENTRY:
					//printf("\ni am IPMSG_ANSENTRY");
					insert_user(m.sender_name, m.sernder_host_name, m.extra_msg, m.sender_addr);
					break;
				case IPMSG_SENDMSG:
					printf("\nrecv one message");

					break;
				case IPMSG_RECVMSG:
				
					break;
				
				default:
					//printf("\ni am default");
					break;
			}
		}else{
			//printf("\nmessage list is empty.");
			//sleep(200);//��ʱû��Ϣ��˯�ߵȴ�һ�ᣬ�����˷�CPUʱ��
		}
	}
	
	return 0;
}

//����UDP���ݰ�
void parse_udp(char* udp, int len, struct sockaddr_in sender_addr){
	char* end;
	char* start;
	start = udp;
	end = 0;
	char tmp_buf[6][COMLEN/6];
	int tmp_index = 0;
	do{
		end = strpbrk(start, ":");//�õ�start���е�һ��':'�ŵĵ�ַ����û���򷵻�0
		if(0 != end  && end < (udp+len)){
			strncpy(tmp_buf[tmp_index], start, (int)(end-start));
			tmp_buf[tmp_index][(int)(end-start)] = '\0';
			start = end + 1;
			tmp_index++;
		}
	}while(0 != end);
	strcpy(tmp_buf[tmp_index], start);
	//���������������Ϣ�б�
	insert_msg(atoi(tmp_buf[0]), atoi(tmp_buf[1]), tmp_buf[2], tmp_buf[3], strtoul(tmp_buf[4], NULL, 10), tmp_buf[5], sender_addr);
	//show_msg_list();
	//printf("\nfinish");
}

