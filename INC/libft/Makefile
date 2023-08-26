# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jareste- <jareste-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/04 12:08:30 by jareste-          #+#    #+#              #
#    Updated: 2023/08/26 02:03:33 by jareste-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

HEADER	=	libft.h

NAME	=	libft.a

SRCS	=	ft_atoi.c \
			ft_isdigit.c \
			ft_isalpha.c \
			ft_isalnum.c \
			ft_isascii.c \
			ft_isprint.c \
			ft_strlen.c \
			ft_memset.c \
			ft_bzero.c \
			ft_memcpy.c	\
			ft_memmove.c \
			ft_strlcpy.c \
			ft_strlcat.c \
			ft_strcmp.c \
			ft_toupper.c \
			ft_tolower.c \
			ft_memchr.c \
			ft_strchr.c \
			ft_strrchr.c \
			ft_strncmp.c \
			ft_memcmp.c \
			ft_strnstr.c \
			ft_calloc.c \
			ft_strdup.c \
			ft_substr.c \
			ft_strjoin.c \
			ft_strtrim.c \
			ft_split.c \
			ft_itoa.c \
			ft_strmapi.c \
			ft_striteri.c \
			ft_putchar_fd.c \
			ft_putstr_fd.c \
			ft_putendl_fd.c \
			ft_putnbr_fd.c \
		    get_next_line_bonus.c \
			get_next_line_utils_bonus.c	

OBJS	= 	$(SRCS:.c=.o)

CC	= 	cc

RM	= 	rm -f

LIBC	= 	ar -rcs

FLAGS	= 	-Wall -Wextra -Werror

all: 
	@$(MAKE) $(NAME) --no-print-directory

$(OBJ)%.o:%.c Makefile ${HEADER}
	@$(CC) $(FLAGS) -I ./ -c $< -o $@

$(NAME):: ${OBJS}
	@$(LIBC) $(NAME) $(OBJS)
	@echo "LIBFT compiled 🏄"

fclean: clean
	@$(RM) $(NAME)
	@echo "LIBFT everything removed."

clean:
	@$(RM) $(OBJS)
	@echo "LIBFT objects removed."

re: fclean all

.PHONY: all clean fclean re .c.o
