#include "cmalloc.h"



t_bool getenv_cached(t_env env){

static uint32_t env_cached;
static t_bool init;


if(!init){

if(getenv("MyMallocStackLogging")){
 env_cached |= ENV_STACK_LOGGING;
}
if(getenv("MyMallocFullLogging")){
 env_cached |= ENV_FULL_LOGGING;
}
if(getenv("MyMallocScribble")) {

env_cached |= ENV_SCRIBBLE;
}

init = TRUE;

}

return (env & env_cached);


}
//


