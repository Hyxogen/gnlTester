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

NAME			:= gnlTester

OBJ_FOLDER		:= obj/
GNL_FOLDER		:= ../

TESTER_SRC		:= src/tester.c src/checker.c
GNL_SRC			:= ../get_next_line.c ../get_next_line_utils.c

TESTER_OBJ		:= $(patsubst %.c,$(OBJ_FOLDER)/%.o,$(notdir $(TESTER_SRC)))
GNL_OBJ			:= $(patsubst %.c,$(OBJ_FOLDER)/%.o,$(notdir $(GNL_SRC)))

DEPENDENCIES	:= ./include/tester.h ../get_next_line.h
TESTER_OBJ		:= $(TESTER_SRC:.c=.o)
GNL_OBJ			:= $(GNL_SRC:.c=.o)
CFLAGS			:= -Wall -Wextra -Werror
CC				:= gcc $(CFLAGS)
LD				:= gcc

all: $(NAME)

$(NAME): $(DEPENDENCIES) $(TESTER_OBJ) $(GNL_OBJ)
	$(LD) $(TESTER_OBJ) $(GNL_OBJ) -o $(NAME)

$(OBJ_FOLDER)/%.o: %.c
	$(CC) -c $< -o $@

clean:
	rm -f $(TESTER_OBJ) $(GNL_OBJ)

fclean: clean
	rm -f $(NAME)
