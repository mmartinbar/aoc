#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum GameChoice
{
    ROCK,
    PAPER,
    SCISSORS,
} GameChoice;

int getScoredPoints(GameChoice my_choice, GameChoice opponent_choice) {
    if (my_choice == opponent_choice) {
        return 3;
    } else if ((my_choice == SCISSORS && opponent_choice == PAPER) || (my_choice == ROCK && opponent_choice == SCISSORS) || (my_choice == PAPER && opponent_choice == ROCK)) {
        return 6;
    } else {
        return 0;
    }
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
                    round_score = 1 + getScoredPoints(ROCK, opponentChoice);
                    break;
                case 'Y':
                    round_score = 2 + getScoredPoints(PAPER, opponentChoice);
                    break;
                case 'Z':
                    round_score = 3 + getScoredPoints(SCISSORS, opponentChoice);
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
