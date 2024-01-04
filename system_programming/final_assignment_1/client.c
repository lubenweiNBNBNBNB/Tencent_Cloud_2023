#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>

#define BUFFER_SIZE 1024

void error(const char *message) {  perror(message);exit(1);}

int main() {
    int client_socket;
    struct sockaddr_in server_address;
    int port_number = 8888;
    char server_ip[] = "127.0.0.1";
    char buffer[BUFFER_SIZE];
    int bytes_received;

    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket < 0)  error("Error in creating client socket");

    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = inet_addr(server_ip);
    server_address.sin_port = htons(port_number);

    if (connect(client_socket, (struct sockaddr *)&server_address, sizeof(server_address)) < 0)  error("Error in connecting to server");

    printf("Connected to server\n");

    while (1) {
        memset(buffer, 0, sizeof(buffer));
        printf("Enter message: ");
        fgets(buffer, sizeof(buffer), stdin);

        if (send(client_socket, buffer, strlen(buffer), 0) < 0)  error("Error in sending data");

        bytes_received = recv(client_socket, buffer, sizeof(buffer), 0);
        if (bytes_received < 0)  error("Error in receiving data");

        printf("Server: %s", buffer);
    }

    close(client_socket);

    return 0;
}
