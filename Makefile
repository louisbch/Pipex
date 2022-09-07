# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lbouchon <lbouchon@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/30 16:27:15 by lbouchon          #+#    #+#              #
#    Updated: 2022/09/07 12:09:57 by lbouchon         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex.a
RM = rm -f
CC = gcc
CFLAGS = -Wall -Wextra -Werror
NORMINETTE = norminette

SRCS = \
		main.c \

OBJS = ${SRCS:.c=.o}

all : ${NAME}

${NAME} : ${OBJS}
		@$(CC) $()

clean :
		${RM} ${OBJS}

fclean : clean
	${RM} ${NAME}

re : fclean all

%.o: %.c
		${CC} ${FLAGS} -o $@ -c $<

norm :
		${NORMINETTE}

.PHONY: all clean fclean re norm