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
# include <stdio.h>

# include "lblcbuffer.h"
# include "lblgtab.h"
# include "lblstr.h"
# include "trace.h"

# define MAGIC (0xba0bab)

enum socket_use_e {
	S_LISTENER,
	S_CLIENT,
};

enum action_e {
	COMMAND,
	EJECT,
	SEND,
	SEND_FILE,
	RECEIVE,
};

typedef struct pkt_header_s {
	size_t magic;
	size_t pkt_size;
	size_t action;
} pkt_header_t;

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
	gtab_t *clients;
	uint16_t port;
	bool is_running;
} cserver_t;

typedef struct cmdthread_s {
	cclient_t *client;
	size_t pkt_size;
} cmdthread_t;

typedef struct client_parser_s {
	enum action_e action;
	int (*link)(cclient_t *client, size_t pkt_size);
} client_parser_t;

int client_mode(const char *ipaddr, uint16_t port);

int create_server(uint16_t port, int backlog, struct sockaddr_in *ptr);
int accept_client(int sockfd, struct sockaddr_in *buf);
int connect_to(const char *ip, uint16_t port, struct sockaddr_in *buffer);
uint32_t get_addr(const char *str);

int cserver_create(cserver_t *server, uint16_t port);
int cserver_run(cserver_t *server);
void cserver_destroy(cserver_t *server);

void pkt_header(pkt_header_t *header, size_t pkt_size, enum action_e action);
ssize_t client_send(cclient_t *client, pkt_header_t *header, const void *data);

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
int _eject(cserver_t *server, const char *line);
int _send(cserver_t *server, const char *line);

int scalloc(void *pptr, size_t nmemb, size_t size);
ssize_t read_wrapper(int fd, void *dest, size_t size);
int client_send_output(cclient_t *self, FILE *output);
int client_receive(cclient_t *client, size_t pkt_size);
int client_eject(cclient_t *client, size_t pkt_size);
int client_exec(cclient_t *client, size_t pkt_size);

#endif /* !COBRA_SERVER_H_ */
