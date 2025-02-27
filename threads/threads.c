#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

#define NUM_PLAYERS 5
#define NUM_FLIPS 10

pthread_mutex_t mutex;
int heads_count = 0;
int tails_count = 0;

void* flip_coin(void* arg) {
    int id = *((int*)arg);
    for (int i = 0; i < NUM_FLIPS; i++) {
        usleep(rand() % 100000);
        int result = rand() % 2;

        pthread_mutex_lock(&mutex);
        if (result == 0) {
            heads_count++;
            printf("Player %d flipped Heads!\n", id);
        } else {
            tails_count++;
            printf("Player %d flipped Tails!\n", id);
        }
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

int main() {
    pthread_t players[NUM_PLAYERS];
    int player_ids[NUM_PLAYERS];
    
    pthread_mutex_init(&mutex, NULL);
    srand(time(NULL));
    
    for (int i = 0; i < NUM_PLAYERS; i++) {
        player_ids[i] = i;
        pthread_create(&players[i], NULL, flip_coin, &player_ids[i]);
    }
    
    for (int i = 0; i < NUM_PLAYERS; i++) {
        pthread_join(players[i], NULL);
    }
    
    pthread_mutex_destroy(&mutex);
    printf("Final Results: Heads: %d, Tails: %d\n", heads_count, tails_count);
    return 0;
}
