# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jareste- <jareste-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/10 14:07:30 by jareste-          #+#    #+#              #
#    Updated: 2023/07/31 09:18:22 by jareste-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = libftprintf.a
SRC_PATH = .
LIBFT_PATH = ../libft/libft.a

SRCS = ft_printf.c \
	ft_print_ptr.c \
	ft_print_uinteger.c \
	ft_print_decimal.c \
	ft_print_hex.c \
	ft_print_string.c \
	ft_print_char_fd.c

OBJS := $(SRCS:.c=.o)

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJS)
	@ar rcs $(NAME) $(OBJS) $(LIBFT_PATH)
	@echo "PRINTF compiled!✍"

%.o: %.c ft_printf.h Makefile
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJS)
	@echo "PRINTF objects removed."

fclean: clean
	@rm -f $(NAME)
	@echo "PRITF everything removed."

re: fclean all

