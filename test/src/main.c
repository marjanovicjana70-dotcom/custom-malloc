#include "test.h"
#include <stdio.h>

static void *run_test_thread(){

    void *ret = cmalloc(80);
    pthread_exit(NULL);
    return ret;

}
int main(void){
pthread_t *thread = cmalloc(sizeof(pthread_t) * 2);

run_test_malloc();


}