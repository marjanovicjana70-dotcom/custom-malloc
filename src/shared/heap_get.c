
#include "cmalloc.h"

static t_heap *get_available_heap(const t_heap *list, const t_heap_group group, const size_t required_size){

t_heap *search;

search = (t_heap *)list;

while(search){

if(search->group == group && search->available >= required_size){
return search;
}

search = search->next;

}

return NULL;

}

t_heap *get_heap_of_block_size(const size_t size){

t_heap *heap;
t_heap *defaultt;
t_heap_group group;

group = get_heap_group_from_block(size);

defaultt = g_heap_anchor;

heap = get_available_heap(defaultt, group, size + sizeof(t_block));
if(!heap){

if(!(heap = create_heap(group, size))){
    return NULL;
}
heap->next = (t_heap *)defaultt;

if(heap->next){
heap->next->prev = heap;
}

g_heap_anchor = heap;
}


return heap;
}

t_heap *get_last_heap(t_heap *heap){

if(!heap){
    return NULL;

}
while(heap && heap->next){
    heap = heap->next;
}

return heap;
}