#include "cmalloc.h"

t_heap *g_heap_anchor = NULL;

pthread_mutex_t g_malloc_mutex = PTHREAD_MUTEX_INITIALIZER;