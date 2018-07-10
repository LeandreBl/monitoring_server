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
SRCS		+= src/client.c
SRCS		+= src/listener.c
SRCS		+= src/stdin.c
SRCS		+= src/cserver_poll.c
SRCS		+= src/stdin_exec.c
SRCS		+= src/stdin_dump.c
SRCS		+= src/int_parser.c
SRCS		+= src/stop.c
SRCS		+= src/pretty_ls.c
SRCS		+= src/client_mode.c
SRCS		+= src/ack.c
SRCS		+= src/stdin_thread.c
SRCS		+= src/eject.c
SRCS		+= src/packet.c
SRCS		+= src/send.c
SRCS		+= src/client_send_output.c
SRCS		+= src/read_wrapper.c
SRCS		+= src/client_eject.c
SRCS		+= src/client_exec.c
SRCS		+= src/client_receive.c
SRCS		+= src/client_send.c
SRCS		+= src/receive.c
SRCS		+= src/wordtab.c
SRCS		+= src/epur_str.c
SRCS		+= src/dump_execute.c
SRCS		+= src/dump_receive.c
SRCS		+= src/dump_ack.c

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

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
