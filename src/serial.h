//
// Created by loic on 23/09/16.
//

#ifndef ARDUINO1_SERIAL_H
#define ARDUINO1_SERIAL_H

typedef struct{
    char nom [256];
    int fd;
}Serial_com;

void serial_open(Serial_com* sp,char *name);
void serial_close(Serial_com* sp);
void serial_write(Serial_com* sp, char* buff);
void serial_read(Serial_com* sp, char * buff);

#endif //ARDUINO1_SERIAL_H
