#include "test.h"
#include <stdio.h>
#include <unistd.h>

static void test_malloc_null(){

void *p = cmalloc(0);

if(p){

printf("Malloc should return NULL\n");
}



cfree(p);

}


static void test_malloc_one(){

char *t = (char *)cmalloc(1);

if(!t){
    printf("Malloc(1) should return ptr\n");
    return;
}

t[0] = 0xFF;
t[1] = 0xFF;
t[2] = 0xFF;
t[3] = 0xFF;

show_alloc_mem_hex();

t[0] = 0;
cfree(t);

}

static void test_malloc_pagesize(){

void *p = cmalloc(getpagesize());
free(p);

}


static void test_malloc_limits(){

void *t = cmalloc(1);

void *t0 = cmalloc(TINY_BLOCK_ALLOCATION);
void *t00 = cmalloc(TINY_BLOCK_ALLOCATION);
void *t000 = cmalloc(TINY_BLOCK_ALLOCATION);

void *t1 = cmalloc(SMALL_BLOCK_ALLOCATION);
void *t2 = cmalloc(SMALL_BLOCK_ALLOCATION + 1);

show_alloc_mem();
show_alloc_mem_hex();
show_heap_list();

cfree(t0);

t0 = cmalloc(TINY_BLOCK_ALLOCATION + sizeof(t_block));

show_alloc_mem();

cfree(t);
cfree(t0);
cfree(t00);
cfree(t000);
cfree(t1);
cfree(t2);


}


static void show_free_size(){

void *p = cmalloc(SMALL_BLOCK_ALLOCATION + 1);

show_heap_list();

cfree(p);



}


void run_test_malloc(){

//test_malloc_null();

test_malloc_one();

//test_malloc_pagesize();
//test_malloc_limits();
//show_free_size();
//show_heap_list();

}
