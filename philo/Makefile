# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hsawamur <hsawamur@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/02 13:00:37 by hsawamur          #+#    #+#              #
#    Updated: 2023/10/09 15:03:20 by hsawamur         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror
# CFLAGS += -MMD -MP
# CFLAGS += -fsanitize=address -g

SRCS_DIR = srcs
SRCS = $(SRCS_DIR)/main.c \
		$(SRCS_DIR)/create.c \
		$(SRCS_DIR)/new.c \
		$(SRCS_DIR)/debug.c

OBJS_DIR = objs
OBJS = $(patsubst $(SRCS_DIR)/%.c, $(OBJS_DIR)/%.o, $(SRCS))

INCLUDES_DIR = includes
INCLUDES = -I$(INCLUDES_DIR)

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(RM) -r $(OBJS_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all
