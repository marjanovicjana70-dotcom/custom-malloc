#include "cmalloc.h"


void *cus_memcpy(void *dest,const void *src, size_t bytes){

char *dest_str;
char *src_str;

if(dest == src) return (dest);

dest_str = (char *)dest;
src_str = (char *)src;

while(bytes--){
    *dest_str++ = *src_str++;
}

return (dest);

}