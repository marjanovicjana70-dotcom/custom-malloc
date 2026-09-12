
#include "cmalloc.h"


t_heap_group get_heap_group_from_block(size_t block){

if(block <= (size_t)TINY_HEAP_ALLOCATION_SIZE) 
{
    return (TINY);
}
else if(block <= (size_t)SMALL_HEAP_ALLOCATION_SIZE)
{
    return (SMALL);
}
return (LARGE);

}


size_t get_heap_size_from_block_size(size_t block_size){

t_heap_group group;

group = get_heap_group_from_block(block_size);

if(group == TINY){
    return (size_t)TINY_HEAP_ALLOCATION_SIZE;
}
else if(group == SMALL){
    return (size_t)SMALL_HEAP_ALLOCATION_SIZE;
}
return block_size + sizeof(t_heap) + sizeof(t_block);
//trebace nam i prostor za meta podatke heap i block segmenta
}
