#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "socket.h"

static char* _socket_create_incoming_buffer()
{
    return malloc(sizeof(char) * HTTP_SOCKET_BUF_SIZE);
}

static int _socket_connect_to(char* addr, unsigned short port)
{
    int socket_handle;
    struct sockaddr_in socket_details;

    socket_handle = socket(AF_INET, SOCK_STREAM, 0);

    socket_details.sin_family = AF_INET;
    socket_details.sin_addr.s_addr = inet_addr(addr);
    socket_details.sin_port = htons(port);
    bzero(&(socket_details.sin_zero), 8);

    if (connect(
            socket_handle,
            (struct sockaddr *) &socket_details,
            sizeof(struct sockaddr)) == -1
        ) {
        printf("HttpClient::Socket >> Could not connect\n");
    }

    return socket_handle;
}

static void _socket_close(int socket_handle)
{
    if (socket_handle) {
       close(socket_handle);
    }
}

static char* _send_request(int socket_handle, char* http_request)
{
    ssize_t bytes;
    char* buf = _socket_create_incoming_buffer();

    printf("Sending REQ: %s\n", http_request);

    bytes = send(socket_handle, http_request, strlen(http_request), 0);
    printf("Sent HTTP Request [%ld bytes]\n", bytes);

    // TODO: Read response in chunks and increase buffer size if needed
    bytes = recv(socket_handle, buf, HTTP_SOCKET_BUF_SIZE, 0);
    printf("Received HTTP Response [%ld bytes]\n", bytes);

    return buf;
}

void socket_free_buffer(char* buf)
{
    if (buf) {
        free(buf);
    }
}

char *socket_send(char *url, unsigned short port, char *http_request)
{
    int s = _socket_connect_to(url, port);
    char* buf = _send_request(s, http_request);
    _socket_close(s);

    return buf;
}
