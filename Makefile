# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: mstegema <mstegema@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2023/08/01 18:15:02 by cschabra      #+#    #+#                  #
#    Updated: 2023/11/24 19:40:08 by cschabra      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #


NAME = minishell
TEST_NAME = minishell_test

CFLAGS = -Wall -Werror -Wextra ${HEADERS} #-Wunreachable-code -Ofast

LIBFT = 42lib

# READLINE_DIR = $(shell brew --prefix readline)
# READLINE_LIB = -lreadline -lhistory -L $(READLINE_DIR)/lib
READLINE_LIB = -lreadline -lhistory

HEADERS	= -I include -I ${LIBFT}/include -I $(READLINE_DIR)/include
LIBS	= ${LIBFT}/libft.a

SRCS	= ${shell find srcs -iname "*.c"}
OBJS	= ${SRCS:.c=.o}

TEST_SRCS = ${shell find tests -iname "*.c"}
TEST_OBJS	= ${TEST_SRCS:.c=.o}

all: ${NAME}

tests: ${TEST_NAME}

${NAME}: ${OBJS}
	@${MAKE} -C ${LIBFT}
	@${CC} -o ${NAME} ${CFLAGS} ${SRCS} ${LIBS} ${READLINE_LIB}

${TEST_NAME}: ${OBJS} ${TEST_OBJS}
	@${MAKE} -C ${LIBFT}
	@${CC} -o ${TEST_NAME} ${CFLAGS} ${SRCS} ${TEST_SRCS} ${LIBS} ${READLINE_LIB}

clean:
	@rm -f ${OBJS}
	@rm -f ${TEST_OBJS}
	@${MAKE} -C ${LIBFT} clean

fclean: clean
	@rm -f ${NAME}
	@rm -f ${TEST_NAME}
	@${MAKE} -C ${LIBFT} fclean

re: fclean all

debug: CFLAGS += -g #-fsanitize=address
debug: re

.PHONY: all, tests, clean, fclean, re, debug
