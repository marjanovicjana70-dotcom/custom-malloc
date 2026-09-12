#include "cmalloc.h"


void *cus_memset(void *ptr, int x, size_t bytes){

if(ptr == NULL) return NULL; 

unsigned char *str;

str = (unsigned char *) ptr;

while(bytes--){

str[bytes] = (unsigned char)x;

}

return ptr;

}

