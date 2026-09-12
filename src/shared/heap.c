#include "cmalloc.h"

void *append_empty_block(t_heap *heap, size_t size){

t_block *new_block;
t_block *last_block;


last_block = NULL;

new_block = (t_block *)SHIFT_HEAP(heap);

if(heap->block_count){

last_block = get_last_block(new_block);

new_block = (t_block *)(SHIFT_BLOCK(last_block) + last_block->allocated_memory);



}
setup_block(new_block, size);

if(heap->block_count){

new_block->prev = last_block;
last_block->next = new_block;

}

heap->block_count++;
heap->available -= (size_t)(new_block->allocated_memory + sizeof(t_block));

return (void *)SHIFT_BLOCK(new_block);

}


static int get_system_limit(rlim_t *limit){

struct rlimit rlp;

if(getrlimit(RLIMIT_DATA, &rlp) < 0){

    return -1;
}
*limit = rlp.rlim_max;

return 0;

}

t_heap *create_heap(t_heap_group group, size_t size){

t_heap *heap;
size_t heap_size;
rlim_t res_limit;

if(get_system_limit(&res_limit) == -1) {

    return NULL;
}

heap_size = get_heap_size_from_block_size(size);

if(heap_size > res_limit){
    return NULL;
}

heap = (t_heap *)mmap(NULL, heap_size, PROT_WRITE | PROT_READ, MAP_PRIVATE | MAP_ANON, -1, 0);

if(heap == MAP_FAILED){

    return NULL;
}

cus_bzero(heap, sizeof(heap));
heap->group = group;
heap->total_size = heap_size;
heap->available = heap_size - sizeof(t_heap);
log_detail(HEAP_CREATE);
return heap;

}


static t_bool is_last_of_preallocated(t_heap *heap){

t_heap *heap_el;
t_heap_group group;
int i;


heap_el = g_heap_anchor;
group = heap->group;
if(group == LARGE)
return FALSE;

i = 0;

while(heap_el){


if(heap_el->group == group){

i++;

}
heap_el = heap_el->next;


}
return (i == 1);

}



void delete_heap_if_empty(t_heap *heap){

if(heap->block_count) 
return;

if(heap->prev){


    heap->prev->next = heap->next;
}
if(heap->next){

    heap->next->prev = heap->prev;
}

if(!is_last_of_preallocated(heap)){
//ne brisemo samo ako je poslednji heap te grupe
if(heap == g_heap_anchor)
g_heap_anchor = heap->next;


munmap(heap, heap->total_size);
log_detail(HEAP_DESTROY);


}

}