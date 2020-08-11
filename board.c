#include "definitions.h"

void initializeBoard(int *board) {
    for(int i = 0; i < 25; i++) board[i] = BORDER;
    for(int i = 0; i <  9; i++) board[convertInto25[i]] = EMPTY;
}

void printBoard(const int *board) {
    printf("\nTic Tac Toe\n");
    printf("\n");

    char pieceSigns[5] = "OX|-";
    for(int i = 0; i < 9; i++) {
        if(i != 0 && i % 3 == 0) printf("\n\n");
        printf("%4c", pieceSigns[board[convertInto25[i]]]);
    }
    printf("\n");
}

int hasEmpty(const int *board) {
    for(int i = 0; i < 9; i++) if(board[convertInto25[i]] == EMPTY) return 1;
    return 0;
}

void makeMove(int *board, const int sqr, const int side) {
    board[sqr] = side;
}