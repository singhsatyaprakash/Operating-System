#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main() {
    int fd[2];   // fd[0] = read end, fd[1] = write end
    pid_t pid;
    char message[] = "Hello from Parent!";
    char buffer[100];

    // Create pipe
    if (pipe(fd) == -1) {
        perror("Pipe failed");
        return 1;
    }

    pid = fork();  // create child process

    if (pid < 0) {
        perror("Fork failed");
        return 1;
    }

    if (pid > 0) {
        // Parent process
        close(fd[0]); // close read end (not needed by parent)
        write(fd[1], message, strlen(message) + 1);
        close(fd[1]); // close write end after writing
    } else {
        // Child process
        close(fd[1]); // close write end (not needed by child)
        read(fd[0], buffer, sizeof(buffer));
        printf("Child received: %s\n", buffer);
        close(fd[0]); // close read end after reading
    }

    return 0;
}