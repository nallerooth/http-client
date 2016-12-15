#include <stdio.h>

#include "http/client.h"

int main(int argc, char *argv[])
{
    printf("Starting HTTP Client..\n");

    char url[] = "127.0.0.1";
    char* resp = http_client_get(url, 8000);

    printf("Got response:\n\n%s\n\n", resp);

    http_client_free_response(resp);

    return 0;
}

