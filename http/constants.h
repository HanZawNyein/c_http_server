#ifndef CONSTANTS_H
#define CONSTANTS_H

// Define your constants here
#define PORT 8080
#define BUFFER_SIZE 1024

typedef void (*HandlerFunc)(int);

// Define your struct RouteEntry here
typedef struct {
    const char *method;
    const char *route;
    HandlerFunc handler;
} RouteEntry;

#endif /* CONSTANTS_H */

