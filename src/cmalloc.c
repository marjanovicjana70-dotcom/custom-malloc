#include "cmalloc.h"

void *start_cmalloc(size_t size){

if(!size) return NULL;

t_heap *heap;
t_block *block;
void *res;

size = (size + 15) & ~15; //poravnjavamo velicinu tako da bude deljiva sa 16

if((block = try_filling_available_block(size))){

return SHIFT_BLOCK(block);

}
if(!(heap = get_heap_of_block_size((const size_t)size))){
    return NULL;
}

res = append_empty_block(heap, size);
log_stack(ALLOCATE, size);

return (res);

}



void *cmalloc(size_t size){


void *res;
pthread_mutex_lock(&g_malloc_mutex);
log_detail(MALLOC);
if((res = start_cmalloc(size)) && getenv_cached(ENV_SCRIBBLE)){

    cus_memset(res, 0xaa, size);
}

pthread_mutex_unlock(&g_malloc_mutex);
return res;

}