#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    int fd1[2]; // Pipe for parent to child
    int fd2[2]; // Pipe for child to parent
    pid_t pid;

    // Create the first pipe (parent to child)
    if (pipe(fd1) == -1) {
        perror("pipe1 error");
        exit(1);
    }

    // Create the second pipe (child to parent)
    if (pipe(fd2) == -1) {
        perror("pipe2 error");
        exit(1);
    }

    // Fork the process
    pid = fork();
    if (pid < 0) {
        perror("fork error");
        exit(1);
    }

    if (pid > 0) { // Parent process
        close(fd1[0]); // Close unused read end of pipe1
        close(fd2[1]); // Close unused write end of pipe2

        int value = 5; // Integer to send
        write(fd1[1], &value, sizeof(value)); // Write integer to pipe
        printf("Parent sent: %d\n", value);

        close(fd1[1]); // Close write end after sending

        // Wait for the child process to finish
        wait(NULL);

        int result;
        read(fd2[0], &result, sizeof(result)); // Read result from child
        printf("Parent received: %d\n", result);

        close(fd2[0]); // Close read end
    } else { // Child process
        close(fd1[1]); // Close unused write end of pipe1
        close(fd2[0]); // Close unused read end of pipe2

        int received_value;
        read(fd1[0], &received_value, sizeof(received_value)); // Read integer from pipe
        printf("Child received: %d\n", received_value);

        // Process the data (multiply by 2)
        int processed_value = received_value * 2;

        write(fd2[1], &processed_value, sizeof(processed_value)); // Write result back to parent
        close(fd2[1]); // Close write end after sending

        close(fd1[0]); // Close read end
        exit(0); // Exit child process
    }

    return 0;
}
