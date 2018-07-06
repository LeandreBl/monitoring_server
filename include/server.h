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
# include <pthread.h>

# include "lblcbuffer.h"
# include "lblgtab.h"
# include "lblstr.h"
# include "trace.h"

enum socket_use_e {
	S_LISTENER,
	S_CLIENT,
};

typedef struct client_s {
	cbuffer_t *cbuffer;
	int fd;
	struct sockaddr_in *saddr;
	enum socket_use_e use;
	bool connected;
} cclient_t;

typedef struct server_s {
	pthread_t *stdin;
	int epoll;
	size_t esize;
	struct epoll_event *events;
	cclient_t *listener;
	gtab_t *clients;
	uint16_t port;
	bool is_running;
} cserver_t;

int client_mode(const char *ipaddr, uint16_t port);

int create_server(uint16_t port, int backlog, struct sockaddr_in *ptr);
int accept_client(int sockfd, struct sockaddr_in *buf);
int connect_to(const char *ip, uint16_t port, struct sockaddr_in *buffer);
uint32_t get_addr(const char *str);

int cserver_create(cserver_t *server, uint16_t port);
int cserver_run(cserver_t *server);
void cserver_destroy(cserver_t *server);

int cserver_poll(cserver_t *server, int size);
int cserver_add_in_poll(cserver_t *server, cclient_t *client);
int cserver_del_in_poll(cserver_t *server, cclient_t *client);

int cclient_create(cclient_t *client, int fd,
	struct sockaddr_in *saddr, enum socket_use_e use);
void cclient_destroy(cclient_t *client);
void cclient_fdestroy(cclient_t *client);
int rdonly(cserver_t *server, cclient_t *client);

int _listener(cserver_t *server, cclient_t *client);
int _client(cserver_t *server, cclient_t *client);

int int_parser(gtab_t *tab, const char *line);
void *stdin_thread(void *server);
int _stdin(cserver_t *server, const char *line);
int _pretty_ls(cserver_t *server, const char *line);
int _stop(cserver_t *server, const char *line);
int _help(cserver_t *server, const char *line);
int _ack(cserver_t *server, const char *line);
int _stdin_exec(cserver_t *server, const char *line);
int _stdin_dump(cserver_t *server, const char *line);

int scalloc(void *pptr, size_t nmemb, size_t size);

#endif /* !COBRA_SERVER_H_ */
