#include "cmalloc.h"


void print_heap_group(t_heap *heap){

switch(heap->group){

case TINY:
cus_putstr("TINY");
break;

case SMALL:
cus_putstr("SMALL");
break;

case LARGE:
cus_putstr("LARGE");
break;

}




}