/*
  *
  * 操作和维护用户列表的工具集
  *
  */


#ifndef USER_UTILS_H
#define USER_UTILS_H

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>

typedef struct user{
	char user_name[30];//用户名
	char host_name[30];//主机名
	char group_name[30];//工作组名
	char load_name[30];//登录名
	struct sockaddr_in address;//用户地址
	struct user* next;
}user;

/*
  *
  * 创建用户列表
  * 参数:  空
  * 返回值:  待定
  */
void create_user_list();

/*
  *
  * 插入用户
  * 参数:  用户名user_name, 主机名host_name,  登录名load_name,  用户地址address
  * 返回值:  待定
  */
void insert_user(char user_name[], char host_name[], char load_name[], struct sockaddr_in address);

/*
  *
  * 删除用户--无意义，应根据用户IP删除
  * 参数:  no为该用户在列表中的序号
  * 返回值:  待定
  */
void delete_user_by_no(int no);

/*
  *
  * 显示用户
  * 参数:  空
  * 返回值:  待定
  */
void show_user_list();


/*
  *
  * 得到用户自身的信息
  * 参数:  空
  * 返回值:  待定
  */
void get_own_msg();

#endif
