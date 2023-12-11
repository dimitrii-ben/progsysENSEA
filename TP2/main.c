#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>

int main() {
    struct addrinfo hints, *result, *p;
    int status;

    // Set hints
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_INET;     // Allow IPv4 or IPv6
    hints.ai_socktype = SOCK_DGRAM; 
    hints.ai_protocol = 17;
    // Call getaddrinfo
    char* argv[3] = {"prg","localhost","1069"};
    if ((status = getaddrinfo(argv[1], argv[2], &hints, &result)) != 0) {
        fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(status));
        return 1;
    }

    // Iterate over the results
    for (p = result; p != NULL; p = p->ai_next) {
        char host[NI_MAXHOST], service[NI_MAXSERV];

        // Call getnameinfo
        if (getnameinfo(p->ai_addr, p->ai_addrlen, host, sizeof host, service, sizeof service, NI_NUMERICHOST|NI_NUMERICSERV) != 0) {
            fprintf(stderr, "getnameinfo error\n");
            continue;
        }

        // Print the results
        printf("Host: %s, Service: %s\n", host, service);
    }

    // Free the memory allocated for the results
    freeaddrinfo(result);

    return 0;
}
