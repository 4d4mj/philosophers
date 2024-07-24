# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefiles                                          :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ajabado <ajabado@student.42beirut.com>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/24 03:11:49 by ajabado           #+#    #+#              #
#    Updated: 2024/07/24 03:11:49 by ajabado          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# color codes
RESET	= \033[0m
BLACK 	= \033[1;30m
RED 	= \033[1;31m
GREEN 	= \033[1;32m
YELLOW 	= \033[1;33m
BLUE	= \033[1;34m
PURPLE 	= \033[1;35m
CYAN 	= \033[1;36m
WHITE 	= \033[1;37m
HIDE	= \033[?25l
SHOW	= \033[?25h
BOLD	= \033[1m

OBJS = $(SRCS:.c=.o)
SRCS = $(addprefix $(SRC_DIR), \
utils.c utils2.c actions.c init.c threads.c main.c \
)

CC = cc
RM = rm -rf
CFLAGS	= -Wall -Wextra -Werror -I $(INC_DIR)
MK		= --no-print-directory

NAME = philosophers

HEADER			= philo.h
INC_DIR			= ./
SRC_DIR			= ./

COUNTER = 0
TOTAL_FILES = $(words $(SRCS))

all: $(NAME) $(HEADER)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "$(BOLD)${GREEN}> Compiled $(NAME) successfully$(RESET)"

%.o : %.c $(HEADER)
	@$(eval COUNTER=$(shell echo $$(($(COUNTER) + 1))))
	@$(CC) $(CFLAGS) -c $< -o $@ -I $(INC_DIR)
	@printf "$(HIDE)$(BOLD)$(YELLOW)\rCompiling $(NAME): $(RESET)["
	@printf "%0.s#" $(shell seq 1 $(COUNTER))
	@if [ $(COUNTER) -lt $(TOTAL_FILES) ]; then \
		printf "%0.s." $(shell seq 1 $$(($(TOTAL_FILES) - $(COUNTER)))); \
	fi
	@printf "] (%d/%d)" $(COUNTER) $(TOTAL_FILES)
	@if [ $(COUNTER) -eq $(TOTAL_FILES) ]; then \
		printf "\n$(SHOW)"; \
	fi

clean:
	@$(RM) $(OBJS)
	@echo "$(YELLOW)> ALL object files of $(NAME) have been deleted$(RESET)"

fclean: clean
	@$(RM) $(NAME)
	@echo "$(RED)> $(NAME) has been deleted$(RESET)$(SHOW)"

re: fclean all

.PHONY: all clean fclean re
