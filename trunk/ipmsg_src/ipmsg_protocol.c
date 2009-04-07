/*
  *
  *  IPMsg协议源文件
  *
  */

#include "ipmsg_protocol.h"
#include "ipmsg.h"
#include "main.h"
#include "userUtils.h"


extern socket_fd udp_sockfd;

/*
  *
  *  发送udp数据包
  *  参数:暂时想到的是命令字、附加消息，待扩展
  *  返回值:待定
  */
void send_udp_packet(command_word command, char extra_msg[], struct sockaddr_in client_addr){
	user own;
	get_own_msg(&own);
	char send_buf[COMLEN];
	int buf_len;
	int client_addr_len;
	
	switch(command & 0x000000FF){//处理消息，待完成......
		case IPMSG_NOOPERATION: //不进行任何操作
			
			break;
		case IPMSG_BR_ENTRY:
			
			break;
		case IPMSG_BR_EXIT:
			
			break;
		case IPMSG_ANSENTRY:
			buf_len =  sprintf(send_buf, "1:1:%s:%s:%u:%s", own.user_name, own.host_name, command, own.load_name);
			client_addr_len = sizeof(client_addr);
			if(-1 == sendto(udp_sockfd, send_buf,buf_len, 0, (struct sockaddr*)&client_addr, client_addr_len)){
				perror("\nbroadcast error");
			}
			break;
		default:

			break;
	}	
}

