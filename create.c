// create.c
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>

int main() {
    int res = mkfifo("fifo1", 0777);
    if (res == 0) {
        printf("*** Named pipe created ***\n");
    } else {
        perror("mkfifo error");
    }
    return 0;
}
