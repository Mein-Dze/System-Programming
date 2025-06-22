// server.c
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>

int main() {
    // Simulate server preparation
    printf("Server is preparing...\n");
    sleep(2); // Delay to simulate preparation time

    int res = open("fifo1", O_WRONLY);
    if (res == -1) {
        perror("open error");
        return 1;
    }
    
    // Notify that server is ready to send data
    printf("Server is ready to send data.\n");
    sleep(2); // Additional delay before sending data

    write(res, "Hello from server!", 18);
    printf("*** Server sent data ***\n");
    
    close(res);
    return 0;
}
