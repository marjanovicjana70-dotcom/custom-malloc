#include "cmalloc.h"
static t_block *merge_previous_block(t_heap *heap, t_block *block){

    if(heap && block && block->prev && block->prev->freed){

     block->prev->next = block->next;
     if(block->next){
        block->next->prev = block->prev;
     }
  block->prev->allocated_memory += block->allocated_memory + sizeof(t_block);
  heap->block_count--;
  return (block->prev);
    }
  
return NULL;
}




static void merge_next_block(t_heap *heap, t_block *block){

if(heap && block && block->next && block->next->freed){

block->allocated_memory += block->next->allocated_memory + sizeof(t_block);    
block->next = block->next->next;
if(block->next->next){

    block->next->next->prev = block;

}

heap->block_count--;

}



}


t_block *merge_block(t_heap *heap, t_block *block){

merge_next_block(heap,block);
return merge_previous_block(heap,block);


}

/*ovim pokusavamo da resimo problem sa unutrasnjom fragmentacijom - kada dealociramo neki blok proveravamo da li su blokovi za koje je vezan, ako postoje,
slobodni da ih spojimo
*/