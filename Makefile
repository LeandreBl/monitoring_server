##
## EPITECH PROJECT, 2018
## cobra server
## File description:
## makefile
##

NAME		= lbl-monitor

CC		= gcc

LIBS		= -lpthread -lreadline

SRCS		= src/main.c
SRCS		+= src/lblcbuffer.c
SRCS		+= src/lblgtab.c
SRCS		+= src/lblstr.c
SRCS		+= src/trace.c
SRCS		+= src/socket_api.c
SRCS		+= src/scalloc.c
SRCS		+= src/cserver_api.c
SRCS		+= src/cclient_api.c
SRCS		+= src/cserver_run.c
SRCS		+= src/rdonly.c
SRCS		+= src/_client.c
SRCS		+= src/_listener.c
SRCS		+= src/_stdin.c
SRCS		+= src/cserver_poll.c
SRCS		+= src/_stdin_exec.c
SRCS		+= src/_stdin_dump.c
SRCS		+= src/int_parser.c
SRCS		+= src/_stop.c
SRCS		+= src/_pretty_ls.c
SRCS		+= src/client_mode.c
SRCS		+= src/_ack.c
SRCS		+= src/stdin_thread.c

OBJS		= $(SRCS:.c=.o)

RM		= rm -f

CFLAGS		= -Werror -Wall -Wextra -g3
CFLAGS		+= -I ./include

# uncomment this for debug flag
CFLAGS	+= -g3 -DDEBUG

GREEN		= '\033[0;32m'
NO_COLOR	= '\033[0m'

%.o : %.c
	@$ $(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@
	@echo "$(CC) $(LIBS) $(CFLAGS) $(CPPFLAGS) $< -o $@ ["$(GREEN)"OK"$(NO_COLOR)"]"
.SUFFIXES: .o .c

all: $(NAME)

$(NAME): $(OBJS)
	@$ $(CC) $(LDFLAGS) $(OBJS) $(LIBS) -o $@
	@echo "$(CC) $(LIBS) $(OBJS) -o $@ \
	["$(GREEN)"LINKING OK"$(NO_COLOR)"]"

tests_run:

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re tests_run install

install: all
	@cp $(NAME) /usr/bin 2> /dev/null || printf "Run install as super user:\nsudo make install\n"
