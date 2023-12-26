# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hsawamur <hsawamur@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/02 13:00:37 by hsawamur          #+#    #+#              #
#    Updated: 2023/12/25 18:08:40 by hsawamur         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror
DEBUGCFLAGS = -g -fsanitize=address -fno-omit-frame-pointer
# DEBUGCFLAGS = -g -fsanitize=thread
# CFLAGS += -MMD -MP

SRCS_DIR = srcs
SRCS = $(SRCS_DIR)/main.c \
		$(SRCS_DIR)/simulation.c \
		$(SRCS_DIR)/new.c \
		$(SRCS_DIR)/create.c \
		$(SRCS_DIR)/delete.c \
		$(SRCS_DIR)/eating.c \
		$(SRCS_DIR)/sleeping.c \
		$(SRCS_DIR)/thinking.c \
		$(SRCS_DIR)/died.c \
		$(SRCS_DIR)/read.c \
		$(SRCS_DIR)/time.c \
		$(SRCS_DIR)/ft_strlen.c \
		$(SRCS_DIR)/ft_atoi.c \

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

debug: CFLAGS += $(DEBUGCFLAGS)
debug: re

re: fclean all
