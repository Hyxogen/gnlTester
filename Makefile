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

SRCS				:= $(SRC_DIR)/tester.c $(SRC_DIR)/checker.c $(SRC_DIR)/test_utils.c
OBJS				:= $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
DEPENDENCIES		:= $(INC_DIR)/tester.h

GNL_DIR				:= ..
GNL_SRCS			:= $(GNL_DIR)/get_next_line.c $(GNL_DIR)/get_next_line_utils.c
GNL_DEPENDENCIES	:= $(GNL_DIR)/get_next_line.h
GNL_OBJS			:= $(GNL_SRCS:$(GNL_DIR)/%.c=$(OBJ_DIR)/%.o)

#TESTER_OBJ			:= $(TESTER_SRC:.c=.o)
#GNL_OBJ				:= $(GNL_SRC:.c=.o)
CFLAGS				:= -Wall -Wextra -Werror
CC					:= gcc $(CFLAGS)
LD					:= gcc

all: $(NAME)

test: all
	./$(NAME) ./tests/simple

$(NAME): $(DEPENDENCIES) $(OBJS) $(GNL_DEPENDENCIES) $(GNL_OBJS)
	$(LD) $(OBJS) $(GNL_OBJS) -o $(NAME)

$(OBJS): $(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) -c $< -o $@

$(GNL_OBJS): $(OBJ_DIR)/%.o: $(GNL_DIR)/%.c
	$(CC) -c $< -o $@

clean:
	rm -f $(OBJS) $(GNL_OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all