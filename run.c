#include "definitions.h"

void runGame() {
    int gameOver = 0;
    int side = NOUGHT;
    int lastMove = 0;
    int board[25];

    initializeBoard(&board[0]);
    printBoard(&board[0]);

    while(!gameOver) {
        if(side == NOUGHT) {
            lastMove = getHumanMove(&board[0]);
            makeMove(&board[0], lastMove, side);
            side = CROSS;
        }
        else {
            lastMove = getComputerMove(&board[0], side);
            makeMove(&board[0], lastMove, side);
            side = NOUGHT;
            printBoard(&board[0]);
        }

        if(findThreeInRow(board, lastMove, side ^ 1) == 3) {
            printf("Game Over!\n");
            gameOver = 1;
            if(side == NOUGHT) printf("Computer Wins!\n");
            else printf("Human Wins!\n");
        }
        
        if(!hasEmpty(board)) {
            printf("Game Over!\n");
            gameOver = 1;
            printf("It's a Draw!\n");
        }
    }
    printBoard(&board[0]);
}
