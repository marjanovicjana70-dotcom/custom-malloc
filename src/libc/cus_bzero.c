#include "cmalloc.h"


void cus_bzero(void *p, size_t n){

unsigned char *str;

str = (unsigned char *)p;

if(str == NULL) return;



while(n--){

str[n] = 0;

}


}