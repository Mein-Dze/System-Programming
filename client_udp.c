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
    char buffer[1024]; // Buffer for communication

    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) {
        perror("[-]Socket error");
        exit(1);
    }
    printf("[+]UDP client socket created.\n");

    memset(&addr, '\0', sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port); // Use htons for port conversion
    addr.sin_addr.s_addr = inet_addr(ip);

    // Indicate connection to server
    printf("[+]Connected to server at %s:%d\n", ip, port);

    // Send message to server
    bzero(buffer, sizeof(buffer)); // Clear the buffer
    strcpy(buffer, "Hello, this is the client speaking.");
    printf("Client: %s\n", buffer);
    sendto(sock, buffer, strlen(buffer), 0, (struct sockaddr*)&addr, sizeof(addr));
    printf("[+]Message sent to server.\n");

    // Receive response from server
    bzero(buffer, sizeof(buffer)); // Clear the buffer again
    recvfrom(sock, buffer, sizeof(buffer), 0, NULL, NULL);
    printf("Server: %s\n", buffer); // Print received response

    close(sock); // Close the socket
    printf("[+]Client Disconnected....\n\n");
    return 0;
}
