#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    char *ip = "127.0.0.1";
    int port = 5566;

    int sock;
    struct sockaddr_in addr;
    char buffer[1024]; // Declare buffer for communication

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("[-]Socket error");
        exit(1);
    }
    printf("[+]TCP client socket created.\n");

    memset(&addr, '\0', sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port); // Use htons for port conversion
    addr.sin_addr.s_addr = inet_addr(ip);

    if (connect(sock, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
        perror("[-]Connection error");
        exit(1);
    }
    printf("[+]Connected to the server.\n");

    // Code to communicate with the server
    bzero(buffer, sizeof(buffer)); // Clear the buffer
    strcpy(buffer, "Hello, this is the client speaking.");
    printf("Client: %s\n", buffer);
    send(sock, buffer, strlen(buffer), 0);
    
    bzero(buffer, sizeof(buffer)); // Clear the buffer again
    recv(sock, buffer, sizeof(buffer), 0);
    printf("Server: %s\n", buffer);

    close(sock); // Close the socket
    printf("[+]Client Disconnected....\n\n"); 
    return 0;
}
