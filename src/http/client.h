#ifndef HTTP_CLIENT
#define HTTP_CLIENT

char *http_client_get(char *url, unsigned short port);
void http_client_free_response(char *buf);

#endif /* ifndef HTTP_CLIENT */
