#include "cmalloc.h"


t_block *get_last_block(t_block *block){

if(block && block->next){

block = block->next;

}

return block;


}

void find_available_block(t_block **res_block,t_heap **res_heap, size_t size){

t_heap *heap;
t_block *block;
t_heap_group group;

group = get_heap_group_from_block(size);
heap = g_heap_anchor;


while(heap){

block = (t_block *)SHIFT_HEAP(heap);
while(heap->group == group && block){

if(block->freed && (block->allocated_memory >= (size + sizeof(t_block)))){

     *res_block = block;
     *res_heap = heap;

    return;
}


block = block->next;
}


    heap = heap->next;
}
*res_block = NULL;
*res_heap = NULL;
}