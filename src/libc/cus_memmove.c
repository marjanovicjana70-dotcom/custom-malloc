#include "cmalloc.h"


void *cus_memmove(void *dest, const void *src, size_t bytes){


char *dest_str;
char *src_str;

dest_str = (char *)dest;
src_str = (char *)src;

if(dest == src) return dest;

if(dest_str < src_str) {
    return cus_memcpy(dest, src, bytes);
}
else {
while(bytes--){

    dest_str[bytes] = src_str[bytes];
}

}
return dest;



}