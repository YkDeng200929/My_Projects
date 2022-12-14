#ifndef _HEAD_H
#define _HAED_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <arpa/inet.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <pthread.h>
#include <signal.h>

#define LOG_IN 1
#define CHAT 2
#define LOG_OUT 3

/*登录用户信息表*/
typedef struct c_list
{
    int cfd;
    struct sockaddr_in addr;
    struct c_list *next;
}c_list;

/*客户端用户信息包*/
typedef struct pack
{
    int type;
    char name[64];
    char text[1024];
}pack;

/*初始化用户信息册*/
extern void init(c_list *info_book);

/*负责添加用户信息到 client_book*/
extern bool s_login(int connect_fd, pack * client_pack, c_list * info_book, struct sockaddr_in * client_addr);

/*负责传送用户信息并广播到所有人*/
extern bool s_chat(int connect_fd, pack * client_pack, c_list * info_book, struct sockaddr_in * client_addr);

/*负责关闭离线客户端后删除 client_book 中的离线用户信息*/
extern bool s_logout(int connect_fd, pack * client_pack, c_list * info_book, struct sockaddr_in * client_addr);

/*等待回收僵尸子进程*/
extern void signal_handler(int signum);

#endif