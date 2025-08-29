#include <stdio.h>
#include <unistd.h>
int main() {
    // Create a child process
    pid_t pid = fork();

    if (pid < 0) {
        printf("Fork failed!\n");
        return 1;
    }
    else if (pid == 0) {
        printf("Hello from the Child Process! PID: %d\n", getpid());
    }
    else {
        printf("Hello from the Parent Process! PID: %d, Child PID: %d\n", getpid(), pid);
    }

    return 0;
}
