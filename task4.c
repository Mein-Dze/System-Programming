#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define NUM_VALUES 3 // Number of integers to send

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

        // Send multiple integers to the child
        int values[NUM_VALUES] = {1, 2, 3}; // Array of integers
        write(fd1[1], values, sizeof(values)); // Write array to pipe
        printf("Parent sent: ");
        for (int i = 0; i < NUM_VALUES; i++) {
            printf("%d ", values[i]);
        }
        printf("\n");

        close(fd1[1]); // Close write end after sending

        // Wait for the child process to finish
        wait(NULL);

        int result;
        read(fd2[0], &result, sizeof(result)); // Read result from child
        printf("Parent received sum: %d\n", result);

        close(fd2[0]); // Close read end
    } else { // Child process
        close(fd1[1]); // Close unused write end of pipe1
        close(fd2[0]); // Close unused read end of pipe2

        int received_values[NUM_VALUES];
        read(fd1[0], received_values, sizeof(received_values)); // Read array from pipe

        // Process the data (compute sum)
        int sum = 0;
        for (int i = 0; i < NUM_VALUES; i++) {
            sum += received_values[i];
        }
        printf("Child received: ");
        for (int i = 0; i < NUM_VALUES; i++) {
            printf("%d ", received_values[i]);
        }
        printf("\n");

        write(fd2[1], &sum, sizeof(sum)); // Write result back to parent
        close(fd2[1]); // Close write end after sending

        close(fd1[0]); // Close read end
        exit(0); // Exit child process
    }

    return 0;
}
