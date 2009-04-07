

#ifndef IPMSG_PROTOCOL_H
#define IPMSG_PROTOCOL_H

#include "messageUtils.h"


/*
  *
  *  发送udp数据包
  *  参数:暂时想到的是命令字、附加消息，待扩展
  *  返回值:待定
  */
void send_udp_packet(command_word command, char extra_msg[], struct sockaddr_in client_addr);


#endif
