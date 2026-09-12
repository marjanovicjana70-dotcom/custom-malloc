#include "cmalloc.h"



static size_t print_block_list(t_block *block){

char *start;
char *end;
size_t total_size;

start = NULL;
end = NULL;
total_size = 0;

while(block){

    

if(!block->freed){

    start = (char *)SHIFT_BLOCK(block);
    end = start + block->allocated_memory;

    cus_itoa_base((size_t)start, 16, 9, TRUE);
    cus_putstr(" - ");
    cus_itoa_base((size_t)end, 16, 9, TRUE);
    cus_putstr(" : ");
    cus_itoa_base(block->allocated_memory, 10, 0, FALSE);
    cus_putstr("octets\n");

    total_size += block->allocated_memory;

}

block = block->next;

}



return total_size;

}




static void print_heap_head(char *name, t_heap *heap){

cus_putstr(name);
cus_putstr(" : ");
cus_itoa_base((size_t)heap, 16, 9, TRUE);
cus_putstr("\n");

}


void start_show_alloc(void){

t_heap *first_heap;
t_heap *last_heap;
size_t total_size;

total_size = 0;
first_heap = g_heap_anchor;
last_heap = get_last_heap(first_heap);

while(last_heap){

if(last_heap->group == TINY){

print_heap_head("TINY",last_heap);

}
else if(last_heap->group == SMALL){

print_heap_head("SMALL",last_heap);

}
else {


print_heap_head("LARGE",last_heap);

}
if(last_heap->block_count){

    total_size+= print_block_list((t_block *)SHIFT_HEAP(last_heap));
}


last_heap = last_heap->prev;
}
cus_putstr("Total size: ");
cus_itoa_base(total_size, 10, 0, FALSE);
cus_putstr(" octets\n");

}


void show_alloc_mem(void){
     pthread_mutex_lock(&g_malloc_mutex);
     start_show_alloc();
     pthread_mutex_unlock(&g_malloc_mutex);
}