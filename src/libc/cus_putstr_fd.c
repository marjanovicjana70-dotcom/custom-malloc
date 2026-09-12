#include "cmalloc.h"



void cus_putstr_fd(const char *s, int fd){

if(s == NULL) return;

size_t i;

i = 0;

while(s[i] != '\0'){

    i++;
}

write(fd, s, i);


}