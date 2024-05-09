
#include "../http/response.h"

void handle_home(int client_socket) {
    char response[BUFFER_SIZE];
    char html[] = "<h1>Welcome to the home page!</h1>";

    snprintf(response, BUFFER_SIZE,
             "HTTP/1.1 200 OK\r\n"
             "Content-Type: text/html\r\n"
             "Content-Length: %lu\r\n"
             "\r\n"
             "%s",
             strlen(html), html);

    send_response(client_socket, response);
}

void handle_json(int client_socket) {
    char response[BUFFER_SIZE];
    char json[] = "{\"message\": \"Hello, world!\"}";

    snprintf(response, BUFFER_SIZE,
             "HTTP/1.1 200 OK\r\n"
             "Content-Type: application/json\r\n"
             "Content-Length: %lu\r\n"
             "\r\n"
             "%s",
             strlen(json), json);

    send_response(client_socket, response);
}
