//
// Created by loic on 23/09/16.
//

#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include <string.h>
#include "serial.h"

void serial_open(Serial_com* sp,char *name) {
    if ((sp->fd = open(name, O_RDWR)) == -1) {
        perror("open failed");
        _exit(1);
    }
    else
        printf("open success\n");
}

void serial_close(Serial_com* sp){
    if(close(sp->fd) == -1){
        perror("close failed");
    }
    else
        printf("close success\n");

}

void serial_write(Serial_com* sp, char* buff){
    write (sp->fd, buff, strlen(buff));
}

void serial_read(Serial_com* sp, char * buff){
    int a;
    a = read(sp->fd, buff, 4);
    buff[4] = '\0';
}