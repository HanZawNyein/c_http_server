#ifndef RESPONSE_H
#define RESPONSE_H

#include <sys/socket.h>
#include <string.h>

void send_response(int client_socket, const char *response) {
    send(client_socket, response, strlen(response), 0);
    close(client_socket);
}

void handle_not_found(int client_socket) {
    char response[BUFFER_SIZE];
    char html[] = "<h1>404 Not Found</h1>";

    snprintf(response, BUFFER_SIZE,
             "HTTP/1.1 404 Not Found\r\n"
             "Content-Type: text/html\r\n"
             "Content-Length: %lu\r\n"
             "\r\n"
             "%s",
             strlen(html), html);

    send_response(client_socket, response);
}

#endif /* RESPONSE_H */
