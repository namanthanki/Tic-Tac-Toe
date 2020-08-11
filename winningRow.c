#include "definitions.h"

int getNumForDir(int startSquare, const int dir, const int *board, const int us) {
    int found = 0;
    while(board[startSquare] != BORDER) {
        if(board[startSquare] != us) break;
        found++;
        startSquare += dir;
    }
    return found;
}

int findThreeInRow(const int *board, const int ourIndex, const int us) {
    int dirIndex = 0;
    int dir = 0;
    int threeCount = 1;

    for(dirIndex = 0; dirIndex < 4; dirIndex++) {
        dir = directions[dirIndex];
        threeCount += getNumForDir(ourIndex + dir, dir, board, us);
        threeCount += getNumForDir(ourIndex + dir * - 1, dir * -1, board, us);
        if(threeCount == 3) break;
        threeCount = 1;
    }
    return threeCount;
}

int findThreeInRowAllBoard(const int *board, const int us) {
    int threeFound = 0;
    for(int i = 0; i < 9; i++) {
        if(board[convertInto25[i]] == us) {
            if(findThreeInRow(board, convertInto25[i], us) == 3) {
                threeFound = 1;
                break;
            }
        }
    }    
    return threeFound;
}

int evaluateForWinning(const int *board, const int us) {
    if(findThreeInRowAllBoard(board, us) != 0) return 1;
    if(findThreeInRowAllBoard(board, us ^ 1) != 0) return -1;
    return 0;
}