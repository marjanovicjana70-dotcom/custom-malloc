#include "cmalloc.h"



void cus_itoa_fd(size_t num, char base, int fd, t_bool prefix){

char *str;

str = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

if(num / base){

    cus_itoa_fd(num / base, base, fd, prefix);
}
else if(prefix){

    cus_putstr_fd("0x",fd);
}
cus_putchar_fd(str[num % base],fd);


}


void cus_itoa_base(size_t num, char base, char len, t_bool prefix){

char *str;

str = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

if(num / base){

    cus_itoa_base(num / base, base, len - 1,prefix );
}
else {
    if(prefix){
        cus_putstr("0x");

    }
    while(--len > 0){
        cus_putchar_fd('0',1);

    }
}
cus_putchar_fd(str[num % base],1);

}