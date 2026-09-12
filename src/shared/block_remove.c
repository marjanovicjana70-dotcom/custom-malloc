#include "cmalloc.h"


void remove_if_last(t_heap *heap, t_block *block){

if(block->freed && !block->next){

if(block->prev){
    block->prev->next = NULL;
}

  heap->available += block->allocated_memory + sizeof(t_block);
    heap->block_count--;
}



}   