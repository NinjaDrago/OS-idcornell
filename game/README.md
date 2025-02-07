# Game of Chance

Game starts with two players each with 5 dollars.

In each turn,
* Player is asked "Above" or "Below" 3
* If the Player is right they gain a dollar.
* If the Player is wrong they lose a dollar

The simulation gives the probabilities and outcomes after 10 turns.

## Build

```bash
gcc -o game game.c
```

## Run
To produce the CSV file of outcomes:
```bash
nice ./game > game.csv
```
