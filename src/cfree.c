#include "cmalloc.h"



void start_cfree(void *ptr){

t_heap *heap;
t_block *block;
t_block *rep;

heap = g_heap_anchor;
if(!heap || !ptr)
return;

search_ptr(&heap, &block, heap, ptr);

if(block && heap){

block->freed = TRUE;
log_stack(DEALLOCATE, block->allocated_memory);
if(getenv_cached(ENV_SCRIBBLE)){
    cus_memset(ptr, 0xaa, block->allocated_memory);
}

rep = merge_block(heap,block);
block = rep ? rep : block;
remove_if_last(heap, block);
delete_heap_if_empty(heap);

}



}


void cfree(void *ptr){

pthread_mutex_lock(&g_malloc_mutex);

log_detail(FREE);
start_cfree(ptr);

pthread_mutex_unlock(&g_malloc_mutex);




}