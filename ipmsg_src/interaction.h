/*
  *
  *
  *
  *
  */


#ifndef INTERACTION_H
#define INTERACTION_H

#define COMMAND_NUM 8;//供用户使用的命令数量
#define true 1;
#define false 0;
typedef short int bool;

//用户交互函数
void user_interaction();

//处理用户输入
void process_input();


//显示帮助信息
void show_help_information();


//显示命令列表
void show_command_list();

//自定义Linux 下的getch函数
char getch();


#endif
