#include "cmalloc.h"


void divide_block(t_block *block, t_heap *heap, size_t size){

t_block *free_block;

free_block = SHIFT_BLOCK(block) + size;
setup_block(free_block, (char *)block->next - (char *)free_block);
//nalazimo razliku u bajtovima

free_block->freed = TRUE;

free_block->next = block->next;
free_block->prev = block;

if(block->next){

block->next->prev = free_block;

}

block->next = free_block;

block->allocated_memory = size;
block->freed = FALSE;

heap->block_count++;




}


t_block *try_filling_available_block(size_t size){

t_heap *heap;
t_block *block;

find_available_block(&block, &heap, size);

if(heap && block){

divide_block(block, heap, size);
return block;
}

return NULL;

}