#include "definitions.h"

int getHumanMove(const int *board) {
    char userInput[4];
    int moveOk = 0;
    int move = -1;

    while(moveOk == 0) {
        printf("Please enter a position from 1 to 9: ");
        fgets(userInput, 3, stdin);
        fflush(stdin);

        if(strlen(userInput) != 2) {
            printf("Invalid Input!\n");
            continue;
        }

        if(sscanf(userInput, "%d", &move) != 1) {
            printf("Invalid Input!\n");
            continue;
        }

        if(move < 1 || move > 9) {
            move = -1;
            printf("Invalid Move Range!\n");
            continue;
        }

        move--;

        if(board[convertInto25[move]] != EMPTY) {
            move = -1;
            printf("Square not available!\n");
            continue;
        }

        moveOk = 1;
    }

    printf("Played Move: %d\n", move + 1);
    return convertInto25[move];
}