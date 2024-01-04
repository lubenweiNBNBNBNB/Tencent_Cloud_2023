#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <pthread.h>

#define MAX_CLIENTS 10
#define BUFFER_SIZE 1024

void error(const char *message)  { perror(message);exit(1);}

void* handle_client(void* arg) {
    int client_socket = *((int*)arg);
    free(arg);

    char buffer[BUFFER_SIZE];
    int bytes_received;

    while (1) {
        memset(buffer, 0, sizeof(buffer));
        bytes_received = recv(client_socket, buffer, sizeof(buffer), 0);
        if (bytes_received < 0)  error("Error in receiving data");
        else if (bytes_received == 0)
            break;

        printf("Client: %s", buffer);
        strcat(buffer, " [Server Echo]");
        send(client_socket, buffer, strlen(buffer), 0);
    }

    close(client_socket);
    pthread_exit(NULL);
}

int main() {
    int server_socket, client_socket;
    struct sockaddr_in server_address, client_address;
    socklen_t client_address_len;
    int port_number = 8888;

    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0) error("Error in creating server socket");

    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(port_number);

    if (bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address)) < 0)  error("Error in binding server socket");

    if (listen(server_socket, MAX_CLIENTS) < 0)  error("Error in listening");
    printf("Server started and listening on port %d\n", port_number);

    while (1) 
    {
        //printf("#### touching client_address_len\n");
        client_address_len = sizeof(client_address);
        //printf("#### touching client_socket\n");
        client_socket = accept(server_socket, (struct sockaddr *)&client_address, &client_address_len);
        if (client_socket < 0)  error("Error in accepting client connection");

        printf("New client connected: %s\n", inet_ntoa(client_address.sin_addr));

        int* client_socket_ptr = (int*)malloc(sizeof(int));
        *client_socket_ptr = client_socket;

        pthread_t thread;
        if (pthread_create(&thread, NULL, (void*)handle_client, (void*)client_socket_ptr) < 0)  error("Error in creating thread");

        pthread_detach(thread);
    }

    close(server_socket);

    return 0;
}
