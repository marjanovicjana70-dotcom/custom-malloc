#include "cmalloc.h"


void setup_block(t_block *block, size_t size){

block->prev = NULL;
block->next = NULL;
block->freed = FALSE;
block->allocated_memory = size;

} 
