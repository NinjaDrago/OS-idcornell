#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
//#include <sys/wait.h>

int main() {
    printf("Simulating a dice roll in Docker...\n");

    for (int i = 1; i <= 6; i++) {
        pid_t pid = fork();

        if (pid < 0) {
            perror("Fork failed");
            return 1;
        }

        if (pid == 0) {  // Child process represents a die roll outcome
            printf("Process %d: The dice rolled a %d! (16.67%% probability)\n", getpid(), i);
            exit(0);  // Exit child process
        }
    }

    // Parent waits for all child processes
    for (int i = 1; i <= 6; i++) {
        wait(NULL);
    }

    return 0;
}
