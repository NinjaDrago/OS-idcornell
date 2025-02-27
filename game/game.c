#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define START_MONEY 5
#define ROUNDS 5

int main() {
    double prob = 1.0;
    int money = START_MONEY;

    printf("Probability, Money, PID\n");

    for (int round = 0; round < ROUNDS; ++round) {
        if (fork() != 0) {  
            // Parent process (Tails - Lose $1)
            prob *= 0.5;
            money -= 1;
        } else {  
            // Child process (Heads - Win $1)
            prob *= 0.5;
            money += 1;
        }
    }

    printf("%lg, %d, %d\n", prob, money, getpid());
    return 0;
}
