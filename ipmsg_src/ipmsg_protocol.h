

#ifndef IPMSG_PROTOCOL_H
#define IPMSG_PROTOCOL_H

#include "messageUtils.h"


/*
  *
  *  ����udp���ݰ�
  *  ����:��ʱ�뵽���������֡�������Ϣ������չ
  *  ����ֵ:����
  */
void send_udp_packet(command_word command, char extra_msg[], struct sockaddr_in client_addr);


#endif
