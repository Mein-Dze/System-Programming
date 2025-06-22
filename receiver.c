// client.c
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>

int main() {
    // Simulate client preparation
    printf("Client is preparing...\n");
    sleep(2); // Delay to simulate preparation time

    int res = open("fifo1", O_RDONLY);
    if (res == -1) {
        perror("open error");
        return 1;
    }
    
    // Notify that client is ready to receive data
    printf("Client is ready to receive data.\n");
    sleep(2); // Wait to ensure server has sent data

    char buffer[100];
    read(res, buffer, sizeof(buffer));
    printf("Data received by client: %s\n", buffer);
    
    close(res);
    return 0;
}
