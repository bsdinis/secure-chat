/***
 * peer.h
 */

#pragma once

#include <arpa/inet.h>
#include <stdbool.h>
#include <stddef.h>

#include "ssl_info.h"
#include "ssl_util.h"

#define MAX_MSG_SZ (1 << 11)

typedef struct peer_t
{
  int socket;
  struct sockaddr_in address;

  ssl_info_t info;
} peer_t;

static inline bool peer_valid(const peer_t *peer) { return peer->socket != -1; }
static inline bool peer_has_message_to_send(const peer_t *peer) { return ssl_info_has_message_to_send(&peer->info); }
static inline bool peer_has_message_recv(const peer_t *peer) { return ssl_info_has_message_to_recv(&peer->info); }

int peer_create(peer_t *, SSL_CTX * ctx, bool server);
int peer_delete(peer_t *);

int peer_close(peer_t *);
int peer_connect(peer_t *, struct sockaddr_in *addr);
int peer_accept(peer_t *, int listen_socket);

int peer_recv(peer_t *, int (*message_handler)(peer_t *));
int peer_send(peer_t *);
int peer_get_buffer(peer_t *, const uint8_t **, ssize_t *);
int peer_prepare_send(peer_t *, uint8_t *blob, ssize_t sz);

const char * peer_get_addr(const peer_t *); // static mem
