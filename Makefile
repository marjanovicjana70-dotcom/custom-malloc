ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

PATH_OBJ = obj
PATH_LIB = lib
PATH_INC = inc


SOURCES += $(addprefix src/shared/, block_merge.c block_setup.c heap.c helper.c shared.c fill.c getenv.c block_get.c block_remove.c heap_get.c ptr.c)
SOURCES += $(addprefix src/logs/, block_memory_aloc_ex.c block_memory_aloc.c show_heap.c call.c)
SOURCES += $(addprefix src/libc/, cus_itoa_base.c cus_putstr.c cus_bzero.c cus_putstr_fd.c cus_putchar_fd.c cus_memset.c cus_memcpy.c cus_memmove.c)
SOURCES += src/cfree.c src/cmalloc.c

OBJECTS = $(SOURCES:src/%.c=$(PATH_OBJ)/%.o)

NAME = custom_malloc_$(HOSTTYPE).so 
LIB_NAME = custom_malloc.so

FLAGS_LIB = -shared
FLAGS_CC = -Wall -Wextra -fPIC
CC = gcc

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJECTS)
	$(CC) $(FLAGS_LIB) -o $@ $(OBJECTS) 
	@rm -f $(LIB_NAME)
	ln -s $(NAME) $(LIB_NAME)
	@echo "Make done"

$(PATH_OBJ)/%.o: src/%.c
	@mkdir -p $(dir $@)
	$(CC) -c  $< $(FLAGS_CC) -o $@ -I $(PATH_INC)
	@echo "turned into obj files"

clean:
	@rm -rf $(PATH_OBJ)
	@echo "Clean done"

fclean: clean
	@rm -f $(NAME) $(LIB_NAME)
	@echo "Fclean done"

re: fclean $(NAME)
