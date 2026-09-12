#include "cmalloc.h"


void cus_putchar_fd(char c, int fd){

write(fd, &c, 1);

}