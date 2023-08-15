# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jareste- <jareste-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/31 09:20:31 by jareste-          #+#    #+#              #
#    Updated: 2023/08/15 01:10:40 by jareste-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC_PATH = ./SRC/parser
INC_PATH = ./INC

PRINTF = INC/PRINTF/libftprintf.a
PRINTF_MAKE = INC/PRINTF
LIBFT = INC/libft/libft.a
LIBFT_MAKE = INC/LIBFT

HEADER = INC/minishell.h

SRCS = $(addprefix $(SRC_PATH)/, main.c \
	   parser.c \
	   parser_utils.c \
	   msh_words.c \
	   msh_words_utils.c)

EXPANDER_PATH = ./SRC/expander

SRCS += $(addprefix $(EXPANDER_PATH)/, expander.c \
		expand_utils.c \
		expand_dots.c) 

BUILTINS_PATH = ./SRC/builtins

SRCS += $(addprefix $(BUILTINS_PATH)/, blt_exit.c \
		)

EXECUTOR_PATH = ./SRC/executor

SRCS += $(addprefix $(EXECUTOR_PATH)/, executor.c \
		)

CC = cc -g -fsanitize=address 
RM = rm -f
CFLAGS = -Wall -Wextra -Werror -I ./INC

RDLFL = -lreadline -ltermcap #-lhistory #-lft 
READL = INC/libft/libreadline.a 
HISTORY = INC/libft/libhistory.a


%.o: %.c ${HEADER} Makefile
		@${CC} ${CFLAGS} -c $< -o $@	

OBJS = ${SRCS:.c=.o}

all:
		@$(MAKE) -C $(LIBFT_MAKE) --no-print-directory
		@$(MAKE) -C $(PRINTF_MAKE) --no-print-directory
		@$(MAKE) ${NAME} --no-print-directory

${NAME}:: ${OBJS} $(LIBFT) $(PRINTF)
	@${CC} $(CFLAGS) $(OBJS) $(LIBFT) $(PRINTF) $(HISTORY) $(READL) $(RDLFL) -o ${NAME}
	@echo "EVERYTHING DONE✌️   "

clean:
			@$(MAKE) clean -C $(LIBFT_MAKE) --no-print-directory
			@$(MAKE) clean -C $(PRINTF_MAKE) --no-print-directory
			@${RM} ${OBJS} 
			@echo "OBJECTS REMOVED😭   "

fclean: clean 
			@$(MAKE) fclean -C $(LIBFT_MAKE) --no-print-directory
			@$(MAKE) fclean -C $(PRINTF_MAKE) --no-print-directory
			@${RM} ${OBJS} ${NAME}
			@echo "EVERYTHING REMOVED😭 "

re: 
			@$(MAKE) fclean --no-print-directory
			@$(MAKE) all --no-print-directory

.PHONY: all clean fclean re
