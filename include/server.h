/*
** EPITECH PROJECT, 2018
** cobra server
** File description:
** header
*/

#ifndef COBRA_SERVER_H_
# define COBRA_SERVER_H_

# include <arpa/inet.h>
# include <stdint.h>
# include <stdbool.h>

# include "lblcbuffer.h"
# include "lblgtab.h"
# include "lblstr.h"
# include "trace.h"

enum socket_use_e {
	S_LISTENER,
	S_CLIENT,
	S_STDIN,
};

typedef struct client_s {
	lblcbuffer *cbuffer;
	int fd;
	struct sockaddr_in *saddr;
	enum socket_use_e use;
	bool connected;
} cclient;

typedef struct server_s {
	int epoll;
	size_t esize;
	struct epoll_event *events;
	lblgtab *clients;
	uint16_t port;
	bool is_running;
} cserver;

int client_mode(const char *ipaddr, uint16_t port);

int create_server(uint16_t port, int backlog, struct sockaddr_in *ptr);
int accept_client(int sockfd, struct sockaddr_in *buf);
int connect_to(const char *ip, uint16_t port, struct sockaddr_in *buffer);
uint32_t get_addr(const char *str);

int cserver_create(cserver *server, uint16_t port);
int cserver_run(cserver *server);
int cserver_poll(cserver *server, int size);
int cserver_add_in_poll(cserver *server, cclient *client);
int cserver_del_in_poll(cserver *server, cclient *client);

int cclient_create(cclient *client, int fd,
	struct sockaddr_in *saddr, enum socket_use_e use);
void cclient_destroy(cclient *client);
int rdonly(cserver *server, cclient *client);

int _listener(cserver *server, cclient *client);
int _client(cserver *server, cclient *client);

int int_parser(lblgtab *tab, const char *line);
int _stdin(cserver *server, cclient *client);
int _pretty_ls(cserver *server, const char *line);
int _stop(cserver *server, const char *line);
int _help(cserver *server, const char *line);
int _ack(cserver *server, const char *line);
int _stdin_exec(cserver *server, const char *line);
int _stdin_dump(cserver *server, const char *line);

int scalloc(void *pptr, size_t nmemb, size_t size);

#endif /* !COBRA_SERVER_H_ */
