#ifndef COMM_H
#define COMM_H
#include "lwip/sockets.h"  // lwIP 3rd-party library


int  comm_get_server_port(void);
const void* comm_get_server_addr(void);
int  comm_err(void);

int  comm_connect(void);
void comm_disconnect(void);

void comm_setsockopt(int lTimeoutSecs, int lIsSend);

int  comm_send(void *pvBuffer, int lSize);
int  comm_recv(void *pvBuffer, int lSize);


#endif // COMM_H