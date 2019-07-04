//
// Created by loic on 30/09/16.
//

#include <termios.h>
#include "serial.h"

void initialisation(Serial_com* sp){
    struct termios toption;
    tcgetattr(sp->fd, &toption);
    toption.c_cflag&=~PARENB;
    cfsetispeed(&toption, B9600);
    cfsetospeed(&toption, B9600);
    toption.c_cflag&=~CSTOPB;
    // a finir

}