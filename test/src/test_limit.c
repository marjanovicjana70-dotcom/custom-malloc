#include "test.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/resource.h>


void run_limit_test(){
    char *t;
   struct rlimit rlm;

rlm.rlim_cur = TINY_HEAP_ALLOCATION_SIZE;
rlm.rlim_max = TINY_HEAP_ALLOCATION_SIZE;

if(setrlimit(RLIMIT_DATA, &rlm) < 0){

    printf("Did not work;\n");
}

if(!(t = (char *)cmalloc(TINY_HEAP_ALLOCATION_SIZE - sizeof(t_block) - sizeof(t_heap)) )){
    printf("it should return ptr\n");
    free(t);
}

if((t = (char *)cmalloc(TINY_HEAP_ALLOCATION_SIZE)))
printf("it should return NULL\n");
free(t);

}