#ifndef HTTP_SOCKET
#define HTTP_SOCKET

#define HTTP_SOCKET_BUF_SIZE 1048576

char *socket_send(char* url, unsigned short port, char* http_request);
void socket_free_buffer(char* buf);

#endif /* ifndef HTTP_SOCKET */
