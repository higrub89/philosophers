# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rhiguita <rhiguita@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/11 16:04:17 by rhiguita          #+#    #+#              #
#    Updated: 2026/09/22 17:30:00 by rhiguita         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        := philo

CC          := gcc
CFLAGS      := -Wall -Wextra -Werror -pthread
OPTFLAGS    ?= -O2

SRC_DIR     := ./
OBJ_DIR     := obj
INC_DIR     := ./

SRCS        := \
	main.c \
	time.c \
	utils.c \
	init.c \
	parser.c \
	simulation.c \
	monitor.c \
	actions.c

OBJS        := $(SRCS:%.c=$(OBJ_DIR)/%.o)
DEPS        := $(OBJS:.o=.d)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OPTFLAGS) $(OBJS) -o $(NAME)
	@printf "\033[32m✓ %s compiled successfully\033[0m\n" "$(NAME)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(OPTFLAGS) -I$(INC_DIR) -MMD -MP -c $< -o $@

clean:
	@rm -rf $(OBJ_DIR)
	@printf "\033[33m✓ %s object files cleaned\033[0m\n" "$(NAME)"

fclean: clean
	@rm -f $(NAME)
	@printf "\033[31m✓ %s executable removed\033[0m\n" "$(NAME)"

re: fclean all

# ThreadSanitizer target for detecting data races
tsan: CFLAGS += -fsanitize=thread -g
tsan: OPTFLAGS = -Og
tsan: re

# AddressSanitizer and LeakSanitizer target
debug: CFLAGS += -fsanitize=address,undefined -g3
debug: OPTFLAGS = -Og
debug: re

-include $(DEPS)

.PHONY: all clean fclean re debug tsan
