#ifndef C_MALLOC
#define C_MALLOC 1 


#define SHIFT_BLOCK(start) ((void *)start + sizeof(t_block))
#define SHIFT_HEAP(start) ((void *)start + sizeof(t_heap))

#define TINY_HEAP_ALLOCATION_SIZE (4 * getpagesize())
#define TINY_BLOCK_ALLOCATION (TINY_HEAP_ALLOCATION_SIZE / 128)

#define SMALL_HEAP_ALLOCATION_SIZE (16 * getpagesize())
#define SMALL_BLOCK_ALLOCATION (SMALL_HEAP_ALLOCATION_SIZE / 128)

#define LOGS_PATH "/tmp/malloc.log"

# include <fcntl.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/mman.h>
# include <sys/resource.h>
# include <unistd.h>
#include <stdint.h>


typedef enum e_bool {

FALSE,
TRUE

} t_bool;


typedef enum e_heap_group {

TINY,
SMALL,
LARGE


} t_heap_group;

typedef enum e_stack_event {

ALLOCATE,
DEALLOCATE

} t_stack_event;


typedef enum e_detail_event {
MALLOC,
FREE,
HEAP_CREATE,
HEAP_DESTROY

} t_detail_event;


typedef enum e_env {
ENV_STACK_LOGGING = 1 << 0,
ENV_FULL_LOGGING = 1 << 1,
ENV_SCRIBBLE = 1 << 2


} t_env;

typedef struct e_heap{

size_t total_size;
size_t available;
size_t block_count;
t_heap_group group;
struct e_heap *prev;
struct e_heap *next;



} t_heap;

extern pthread_mutex_t		g_malloc_mutex;
extern t_heap				*g_heap_anchor;

typedef struct s_block {

t_bool freed;
size_t allocated_memory;

struct s_block *prev;
struct s_block *next;

} t_block;


void *start_cmalloc(size_t size);
void *cmalloc(size_t size);
void start_cfree(void *ptr);
void cfree(void *ptr);
void show_alloc_mem_hex(void);
void show_alloc_mem(void);


void print_heap_group(t_heap *heap);
void log_stack(t_stack_event event, size_t size);
void log_detail(t_detail_event event);
void start_show_alloc(void);

//libc funkcije 

void cus_bzero(void *p, size_t n);
void cus_itoa_fd(size_t num, char base, int fd, t_bool prefix);
void cus_itoa_base(size_t num, char base, char len, t_bool prefix);
void *cus_memcpy(void *dest,const void *src, size_t bytes);
void *cus_memmove(void *dest, const void *src, size_t bytes);
void *cus_memset(void *ptr, int x, size_t bytes);
void cus_putchar_fd(char c, int fd);
void cus_putstr_fd(const char *s, int fd);
void cus_putstr(const char *s);


t_block *get_last_block(t_block *block);
void find_available_block(t_block **res_block,t_heap **res_heap, size_t size);
t_block *merge_block(t_heap *heap, t_block *block);
void remove_if_last(t_heap *heap, t_block *block);
void setup_block(t_block *block, size_t size);
void divide_block(t_block *block, t_heap *heap, size_t size);
t_block *try_filling_available_block(size_t size);
t_bool getenv_cached(t_env env);
t_heap *get_heap_of_block_size(const size_t size);
t_heap *get_last_heap(t_heap *heap);


void *append_empty_block(t_heap *heap, size_t size);
t_heap *create_heap(t_heap_group group, size_t size);
t_heap *get_last_heap(t_heap *heap);
void delete_heap_if_empty(t_heap *heap);

t_heap_group get_heap_group_from_block(size_t block);
size_t get_heap_size_from_block_size(size_t block_size);
void search_ptr(t_heap **res_heap, t_block **res_block, t_heap *heap, void *ptr);

#endif