#include "test.h"
#include <stdio.h>

void show_heap_list(){

    int i = 0;
    t_heap *heap = g_heap_anchor;

    printf("DEBUG: heap list\n");

    while (heap) {
        printf(
            "%d. heap %p, prev: %p, next: %p (count: %zu, group: %d, total size: %zu, free_space: %zu)\n",
            i,
            heap,
            heap->prev,
            heap->next,
            heap->block_count,
            heap->group,
            heap->total_size,
            heap->available);
        heap = heap->next;
        i++;
    }

}