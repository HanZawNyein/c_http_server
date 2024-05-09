#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "http/constants.h"
#include "http/logging.h"
#include "routes.h"



int main() {
    int server_fd, client_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    char message[100];
    snprintf(message, sizeof(message), "Server started. Listening on port %d...", PORT);
    log_message(message);

    while (1) {
        if ((client_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0) {
            perror("accept");
            exit(EXIT_FAILURE);
        }

        char buffer[BUFFER_SIZE] = {0};
        read(client_socket, buffer, BUFFER_SIZE);

        // Parse the request to extract the method and route
        char *method_start = buffer;
        char *method_end = strchr(method_start, ' ');
        if (method_end != NULL) {
            *method_end = '\0';  // Null-terminate the method
            char *route_start = method_end + 1;
            char *route_end = strchr(route_start, ' ');
            if (route_end != NULL) {
                *route_end = '\0';  // Null-terminate the route
                handle_route(client_socket, method_start, route_start);
                // Log the request
                char log_message_buffer[BUFFER_SIZE];
                snprintf(log_message_buffer, BUFFER_SIZE, "Request: %s %s", method_start, route_start);
                log_message(log_message_buffer);
            }
        }
    }

    return 0;
}
