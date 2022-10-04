# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lbouchon <lbouchon@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/30 16:27:15 by lbouchon          #+#    #+#              #
#    Updated: 2022/09/30 11:35:08 by lbouchon         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
RM = rm -f
DIR = srcs/
CC = gcc
CFLAGS = -Wall -Wextra -Werror
NORMINETTE = norminette

SRCS = $(DIR)process.c		\
		$(DIR)path.c 		\
		$(DIR)main.c		\
		$(DIR)ft_split.c	\
		$(DIR)ft_strjoin.c	\
		$(DIR)ft_utils.c	\

OBJS = ${SRCS:.c=.o}

all : ${NAME}

${NAME} : ${OBJS}
		@$(CC) $(CFLAGS) -o $(NAME) $(OBJS)
		@echo "\033[0;42mPipex is now compile !"

clean :
		@echo "\033[9;31m"
		${RM} ${OBJS}

fclean : clean
	@echo "\033[9;31m"
	${RM} ${NAME}

re : fclean all

%.o: %.c
		@echo "\033[1;33mCompiling pipex...\033[0m"
		${CC} ${FLAGS} -o $@ -c $<

norm :
		@echo "\033[1;34m"
		${NORMINETTE}

.PHONY: all clean fclean re norm