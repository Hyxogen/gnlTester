# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: dmeijer <dmeijer@student.codam.nl>           +#+                      #
#                                                    +#+                       #
#    Created: 2021/10/28 11:12:21 by dmeijer       #+#    #+#                  #
#    Updated: 2021/10/28 13:15:51 by dmeijer       ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME				:= gnlTester

OBJ_DIR				:= ./obj
SRC_DIR				:= ./src
INC_DIR				:= ./include

SRCS				:= $(SRC_DIR)/GNLTester.c $(SRC_DIR)/TestUtils.c $(SRC_DIR)/MemUtils.c $(SRC_DIR)/LinkedList.c \
						$(SRC_DIR)/ReadUtils.c $(SRC_DIR)/Logger.c $(SRC_DIR)/ProfilingUtils.c
OBJS				:= $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
DEPENDENCIES		:= $(INC_DIR)/tester.h

GNL_DIR				:= ..
GNL_SRCS			:= $(GNL_DIR)/get_next_line.c $(GNL_DIR)/get_next_line_utils.c
GNL_DEPENDENCIES	:= $(GNL_DIR)/get_next_line.h
GNL_OBJS			:= $(GNL_SRCS:$(GNL_DIR)/%.c=$(OBJ_DIR)/%.o)

TEST_FILES			:= $(notdir $(wildcard tests/*.txt))

LOGGING				:= -DTESTER_LOG
#-finstrument-functions
PROFILER_FLAGS		:= -finstrument-functions
MEMORY_CHECK		:= -fsanitize=address
#GLOBAL_CFLAGS		:= $(MEMORY_CHECK)
GNL_CFLAGS			:= -Wall -Wextra -Werror
CC					:= gcc
LD					:= gcc $(MEMORY_CHECK)

#BUF_SIZE			:= 1

all: $(NAME)

debug: GLOBAL_CFLAGS += -g $(MEMORY_CHECK) $(LOGGING)
debug: $(NAME)

profiler: GLOBAL_CFLAGS += -DTESTER_PROFILER_ENABLE
profiler: $(NAME)

mandatory: GLOBAL_CFLAGS += $(MEMORY_CHECK) $(LOGGING) -DTEST_MANDATORY
mandatory: $(NAME)

memfail: GLOBAL_CFLAGS += $(MEMORY_CHECK) -DTEST_MALLOC_FAIL $(LOGGING)
memfail: $(NAME)

readfail: GLOBAL_CFLAGS += $(MEMORY_CHECK) -DTEST_REAF_FAIL $(LOGGING)
readfail: $(NAME)

test: re
	./$(NAME) ./tests/simple

$(NAME): $(DEPENDENCIES) $(OBJS) $(GNL_DEPENDENCIES) $(GNL_OBJS)
	$(LD) $(OBJS) $(GNL_OBJS) -o $(NAME) -D BUFFER_SIZE=$(BUF_SIZE)

$(OBJS): $(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(GLOBAL_CFLAGS) -c $< -o $@ -D BUFFER_SIZE=$(BUF_SIZE) -DTESTER_ASSERT_ENABLE

$(GNL_OBJS): $(OBJ_DIR)/%.o: $(GNL_DIR)/%.c
	$(CC) $(GNL_CFLAGS) $(GLOBAL_CFLAGS) -c $< -o $@ -DBUFFER_SIZE=$(BUF_SIZE) -D'malloc(x)=MallocTracked(x)' -D'free(x)=FreeTracked(x)'

$(TEST_FILES): %.txt: $(NAME)
	@./$(NAME) ./tests/$@

clean:
	rm -f $(OBJS) $(GNL_OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all