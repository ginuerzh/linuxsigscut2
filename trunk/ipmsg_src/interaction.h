/*
  *
  *
  *
  *
  */


#ifndef INTERACTION_H
#define INTERACTION_H

#define COMMAND_NUM 8;//���û�ʹ�õ���������
#define true 1;
#define false 0;
typedef short int bool;

//�û���������
void user_interaction();

//�����û�����
void process_input();


//��ʾ������Ϣ
void show_help_information();


//��ʾ�����б�
void show_command_list();

//�Զ���Linux �µ�getch����
char getch();


#endif
