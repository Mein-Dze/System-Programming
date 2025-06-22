
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    int fd[2]; // File descriptors for the pipe
    pid_t pid;

    // Create the pipe
    if (pipe(fd) == -1) {
        perror("pipe error");
        exit(1);
    }

    // Fork the process
    pid = fork();
    if (pid < 0) {
        perror("fork error");
        exit(1);
    }

    if (pid > 0) { // Parent process
        close(fd[0]); // Close unused read end of the pipe

        int value = 42; // Integer to send
        write(fd[1], &value, sizeof(value)); // Write integer to pipe
        printf("Parent sent: %d\n", value);

        close(fd[1]); // Close write end after sending
    } else { // Child process
        close(fd[1]); // Close unused write end of the pipe

        int received_value;
        read(fd[0], &received_value, sizeof(received_value)); // Read integer from pipe
        printf("Child received: %d\n", received_value);

        close(fd[0]); // Close read end
        exit(0); // Exit child process
    }

    return 0;
}
