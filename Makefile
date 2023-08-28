# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jareste- <jareste-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/31 09:20:31 by jareste-          #+#    #+#              #
#    Updated: 2023/08/28 18:10:10 by jareste-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC_PATH = ./SRC/parser
INC_PATH = ./INC

PRINTF = INC/PRINTF/libftprintf.a
PRINTF_MAKE = INC/PRINTF
LIBFT = INC/libft/libft.a
LIBFT_MAKE = INC/LIBFT
READLINE_MAKE = INC/READLINE

HEADER = INC/minishell.h

SRCS = ./SRC/main.c

SRCS += $(addprefix $(SRC_PATH)/, parser.c \
	   parser_utils.c \
	   msh_words.c \
	   msh_words_utils.c \
	   check_errors.c)

EXPANDER_PATH = ./SRC/expander

SRCS += $(addprefix $(EXPANDER_PATH)/, expander.c \
		expand_utils.c \
		expand_utils2.c \
		expand_dots.c) 

BUILTINS_PATH = ./SRC/builtins

SRCS += $(addprefix $(BUILTINS_PATH)/, blt_exit.c \
		blt_echo.c \
		blt_cd.c \
		blt_pwd.c \
		blt_env_utils.c \
		blt_export.c \
		blt_env.c \
		blt_unset.c)

EXECUTOR_PATH = ./SRC/executor

SRCS += $(addprefix $(EXECUTOR_PATH)/, executor.c \
		exe_redirects.c \
		heredoc.c \
		blt_checks.c \
		exe_cmd.c \
		exe_utils.c)

SIGNALS_PATH = ./SRC/signals

SRCS += $(addprefix $(SIGNALS_PATH)/, signals.c \
		) 


CC = cc 
RM = rm -f
CFLAGS = -Wall -Wextra -Werror -I ./INC

RDLFL = -lreadline -ltermcap #-lhistory -lft 
READL = INC/readline/libreadline.a 
HISTORY = INC/readline/libhistory.a

%.o: %.c ${HEADER} Makefile
		@${CC} ${CFLAGS} -c $< -o $@	

OBJS = ${SRCS:.c=.o}

all:
		@$(MAKE) -C $(LIBFT_MAKE) --no-print-directory
		@$(MAKE) -C $(PRINTF_MAKE) --no-print-directory
		@$(MAKE) -C $(READLINE_MAKE) --no-print-directory
		@$(MAKE) ${NAME} --no-print-directory

${NAME}:: ${OBJS} $(LIBFT) $(PRINTF)
	@${CC} $(CFLAGS) $(OBJS) $(LIBFT) $(PRINTF) $(HISTORY) $(READL) $(RDLFL) -o ${NAME}
	@echo "EVERYTHING DONE✌️   "

clean:
			@$(MAKE) clean -C $(LIBFT_MAKE) --no-print-directory
			@$(MAKE) clean -C $(PRINTF_MAKE) --no-print-directory
			@$(MAKE) clean -C $(READLINE_MAKE) --no-print-directory
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
