# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: mstegema <mstegema@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2023/08/01 18:15:02 by cschabra      #+#    #+#                  #
#    Updated: 2023/12/18 19:03:33 by cschabra      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #


NAME = minishell

CFLAGS = -Wall -Werror -Wextra ${HEADERS} #-Wunreachable-code -Ofast

LIBFT = 42lib

# READLINE_DIR = $(shell brew --prefix readline)
# READLINE_LIB = -lreadline -lhistory -L $(READLINE_DIR)/lib
READLINE_LIB = -lreadline -lhistory

HEADERS	= -I include -I ${LIBFT}/include -I $(READLINE_DIR)/include
LIBS	= ${LIBFT}/libft.a

SRCS	= ${shell find srcs -iname "*.c"}
OBJS	= ${SRCS:.c=.o}

all: ${NAME}

${NAME}: ${OBJS}
	@${MAKE} -C ${LIBFT}
	@${CC} -o ${NAME} ${CFLAGS} ${SRCS} ${LIBS} ${READLINE_LIB}

clean:
	@rm -f ${OBJS}
	@${MAKE} -C ${LIBFT} clean

fclean: clean
	@rm -f ${NAME}
	@${MAKE} -C ${LIBFT} fclean

re: fclean all

debug: CFLAGS += -g #-fsanitize=address
debug: re

.PHONY: all, clean, fclean, re, debug
