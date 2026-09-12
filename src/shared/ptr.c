#include "cmalloc.h"


void search_ptr(t_heap **res_heap, t_block **res_block, t_heap *heap, void *ptr){


t_block *search;

search = NULL;

while(heap){

search = (t_block *)SHIFT_HEAP(heap);

while(search){

if(SHIFT_BLOCK(search) == ptr){

*res_heap = heap;
*res_block = search;
return;
}

search = search->next;

}

heap = heap->next;


}



*res_heap = NULL;
*res_block = NULL;

}