#include "cmalloc.h"


static void log_allocation(int fd, size_t size){

cus_putstr_fd("Allocated", fd);
cus_itoa_fd(size, 10, fd, TRUE);
cus_putstr_fd(" bytes\n", fd);
}


static void log_deallocation(int fd, size_t size){

cus_putstr_fd("Deallocated", fd);
cus_itoa_fd(size, 10, fd, TRUE);
cus_putstr_fd(" bytes\n", fd);


}


void log_stack(t_stack_event event, size_t size){

int fd;

if(getenv_cached(ENV_STACK_LOGGING) || getenv_cached(ENV_FULL_LOGGING)){

if((fd = open(LOGS_PATH, O_CREAT | O_WRONLY | O_APPEND,0644)) == -1)
 return;
if(event == ALLOCATE){
    log_allocation(fd, size);
}
else if(event == DEALLOCATE){
    log_deallocation(fd, size);
}

close(fd);

}



}


void log_detail(t_detail_event event){

    int fd;
if(getenv_cached(ENV_FULL_LOGGING)){

if((fd = open(LOGS_PATH, O_CREAT | O_WRONLY | O_APPEND, 0644))==-1){
    return;
}    

if(event == MALLOC){

cus_putstr_fd("Malloc call\n",fd);
}
else if(event == FREE){

cus_putstr_fd("Free call\n",fd);

}
else if(event == HEAP_CREATE){
cus_putstr_fd("Heap creation call\n",fd);

}
else {
    cus_putstr_fd("Heap removal call\n",fd);
}


close(fd);
}

}

