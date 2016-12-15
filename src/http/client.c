#include "client.h"

#include "lib/socket.h"
#include <stdlib.h>
#include <string.h>

static void _request_get(char *req)
{
    strcpy(req, "GET / HTTP/1.1\r\nHost: 127.0.0.1:8000/\r\n\r\n");
}

char *http_client_get(char *url, unsigned short port)
{
    char *req = (char *) malloc(sizeof(char) * 2048);
    bzero(req, sizeof(char) * 2048);
    _request_get(req);

    char *resp = socket_send(url, port, req);
    free(req);

    return resp;
}

void http_client_free_response(char *buf)
{
    socket_free_buffer(buf);
}
