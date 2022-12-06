#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum GameChoice
{
    ROCK = 1,
    PAPER = 2,
    SCISSORS = 3,
} GameChoice;

typedef enum RoundResult
{
    LOSE = 0,
    DRAW = 3,
    WIN = 6,
} RoundResult;

GameChoice computeMyChoice(RoundResult result, GameChoice opponent_choice) {
    switch (opponent_choice) {
        case ROCK:
            switch (result) {
                case LOSE:
                    return SCISSORS;
                case DRAW:
                    return ROCK;
                case WIN:
                default:
                    return PAPER;
            }
        case PAPER:
            switch (result) {
                case LOSE:
                    return ROCK; 
                case DRAW:
                    return PAPER;
                case WIN:
                default:
                    return SCISSORS;
            }
        case SCISSORS:
        default:
            switch (result) {
                case LOSE:
                    return PAPER;
                case DRAW:
                    return SCISSORS;
                case WIN:
                default:
                    return ROCK; 
            }
    }
}

int getScoredPoints(RoundResult result, GameChoice opponent_choice) {
    GameChoice my_choice = computeMyChoice(result, opponent_choice);
    return (int)my_choice + (int)result;
}

int main() {
    FILE * fp = NULL;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    int acc_score = 0;

    if (!(fp = fopen("./input.txt", "r")))
        return -1;

    while ((read = getline(&line, &len, fp)) != -1) {
        int round_score = 0;

        GameChoice opponentChoice;

        char* first_token = strtok(line, " ");
        while (first_token != NULL) {
            switch (first_token[0]) {
                case 'A':
                    opponentChoice = ROCK;
                    break;
                case 'B':
                    opponentChoice = PAPER;
                    break;
                case 'C':
                    opponentChoice = SCISSORS;
                    break;
                case 'X':
                    round_score = getScoredPoints(LOSE, opponentChoice);
                    break;
                case 'Y':
                    round_score = getScoredPoints(DRAW, opponentChoice);
                    break;
                case 'Z':
                    round_score = getScoredPoints(WIN, opponentChoice);
                    break;
                default:
                    break;
            }
                
            first_token = strtok(NULL, " ");
        }

        acc_score += round_score;
    }

    if (line)
        free(line);
    fclose(fp);

   printf("acc_score: %d\n", acc_score);
   return 0;
}
