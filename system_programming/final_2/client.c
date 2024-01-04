#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/epoll.h>

#define BUFFER_SIZE 1024
#define EPOLL_SIZE 10

void error(const char *message) {
    perror(message);
    exit(1);
}

int main() {
    int client_socket;
    struct sockaddr_in server_address;
    char server_ip[] = "127.0.0.1";
    int server_port = 8888;
    int epoll_fd, event_count, i, n;
    struct epoll_event events[EPOLL_SIZE];
    char buffer[BUFFER_SIZE];

    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket < 0) error("Error in creating client socket");

    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = inet_addr(server_ip);
    server_address.sin_port = htons(server_port);

    if (connect(client_socket, (struct sockaddr *)&server_address, sizeof(server_address)) < 0)
        error("Error in connecting to server");

    printf("Connected to server %s:%d\n", server_ip, server_port);

    // Create epoll instance
    epoll_fd = epoll_create(EPOLL_SIZE);
    if (epoll_fd < 0) error("Error in creating epoll instance");

    struct epoll_event client_event;
    client_event.events = EPOLLIN;
    client_event.data.fd = client_socket;

    // Add the client socket to epoll
    if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, client_socket, &client_event) < 0)
        error("Error in adding client socket to epoll");

    while (1) {
        event_count = epoll_wait(epoll_fd, events, EPOLL_SIZE, -1);
        if (event_count < 0) error("Error in epoll_wait");

        for (i = 0; i < event_count; i++) {
            if (events[i].data.fd == client_socket) {
                // Data from server
                n = recv(client_socket, buffer, sizeof(buffer), 0);
                if (n <= 0) {
                    // Connection closed or error occurred
                    printf("Disconnected from server\n");
                    close(client_socket);
                    exit(0);
                } else {
                    printf("Received message from server: %s\n", buffer);
                }
            } else {
                // User input
                fgets(buffer, sizeof(buffer), stdin);
                buffer[strcspn(buffer, "\n")] = '\0';  // Remove newline character

                // Send message to server
                send(client_socket, buffer, strlen(buffer), 0);
            }
        }
    }

    close(epoll_fd);
    close(client_socket);

    return 0;
}