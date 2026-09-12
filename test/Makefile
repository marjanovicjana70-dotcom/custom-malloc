INC_PATH = -I../inc -I./src
LIB_PATH = ..
BUILD_PATH = obj
SRC_PATH = src

SOURCES = print.c test_malloc.c test_limit.c main.c 
LIB_SOURCES = $(shell printenv HOME)/custom-malloc/custom_malloc.so

OBJECTS = $(SOURCES:%.c=$(BUILD_PATH)/%.o)

NAME = test
FLAGS_CC = -Wall -Wextra 
CC = gcc

.PHONY: all clean

all: $(NAME)

$(NAME): $(OBJECTS)
	@make -C $(LIB_PATH)
	$(CC) $^ $(FLAGS_CC) -o $@ $(LIB_SOURCES)
	@echo "made exe file"

$(BUILD_PATH)/%.o: $(SRC_PATH)/%.c
	@mkdir -p $(@D)
	$(CC) -c $< $(FLAGS_CC) -o $@ $(INC_PATH)
	@echo "turned files into obj files"

clean:
	@make fclean -C $(LIB_PATH) 
	@rm -rf $(BUILD_PATH)
	@rm -f test
	@echo "cleaned everything"