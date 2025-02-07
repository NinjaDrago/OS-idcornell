#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <string.h>  // Include string.h

#define FILE_NAME "results.csv"
#define START_MONEY 5
#define ROUNDS 5  // Number of rounds to play

int main() {
    int money = START_MONEY;
    char guess_input[10];

    // Seed random number generator
    srand(time(NULL) ^ getpid());

    // Open file in write mode to create and write the header
    FILE *file = fopen(FILE_NAME, "w");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }
    fprintf(file, "Process ID,Round,Guess,Roll,Outcome,Money\n");
    fclose(file);  // Close the file to prevent issues in child processes

    printf("Game Start! Initial Money: $%d\n", money);
    printf("--------------------------------------------------\n");

    for (int round = 1; round <= ROUNDS; round++) {
        pid_t pid = fork();

        if (pid < 0) {
            perror("Fork failed");
            return 1;
        }

        if (pid == 0) {  // Child process
            exit(0); // Child does nothing
        } else {  // Parent process
            // Prompt the user for input
            printf("Round %d | Your current money: $%d\n", round, money);
            printf("Guess if the roll will be 'Above' or 'Below' 3: ");
            fgets(guess_input, 10, stdin);  // Read user input

            // Check if the user input is valid
            int guess = -1;
            if (strncmp(guess_input, "Above", 5) == 0) {
                guess = 1;  // Above
            } else if (strncmp(guess_input, "Below", 5) == 0) {
                guess = 0;  // Below
            } else {
                printf("Invalid input! Please enter 'Above' or 'Below'.\n");
                continue;  // Skip the current round
            }

            // Roll a random number between 1 and 6
            int roll = (rand() % 6) + 1;
            int win = (guess == 0 && roll < 3) || (guess == 1 && roll > 3);

            if (win) {
                money += 1;
            } else {
                money -= 1;
            }

            // Print results to screen
            printf("Round %d | PID: %d | Guess: %s | Roll: %d | %s | Money: $%d\n",
                   round, getpid(), guess == 0 ? "Below" : "Above",
                   roll, win ? "Win" : "Lose", money);

            // Open file in append mode to add round results
            FILE *file = fopen(FILE_NAME, "a");
            if (file == NULL) {
                perror("Error opening file");
                exit(1);
            }

            // Write the round result to the CSV file
            fprintf(file, "%d,%d,%s,%d,%s,%d\n",
                    getpid(), round, guess == 0 ? "Below" : "Above",
                    roll, win ? "Win" : "Lose", money);

            fflush(file);
            fclose(file);
        }

        wait(NULL);  // Wait for child to finish
    }

    printf("--------------------------------------------------\n");
    printf("Game Over! Results saved to %s\n", FILE_NAME);
    return 0;
}
