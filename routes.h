

#include <stddef.h>
#include <string.h>
#include "http/constants.h"
#include "controllers/home.h"
#include "http/response.h"

void handle_route(int client_socket, const char *method, const char *route) {
    static const RouteEntry routes[] = {
            {"GET", "/", handle_home},
            {"GET", "/json", handle_json},
            // Add more routes here
    };

    for (size_t i = 0; i < sizeof(routes) / sizeof(RouteEntry); ++i) {
        if (strcmp(method, routes[i].method) == 0 && strcmp(route, routes[i].route) == 0) {
            routes[i].handler(client_socket);
            return;
        }
    }

    handle_not_found(client_socket);
}