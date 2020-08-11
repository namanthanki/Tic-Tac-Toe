#include "definitions.h"

int minMax(int *board, int side) {
    int moveList[9];
    int moveCount = 0;
    int bestScore = -2;
    int score = -2;
    int bestMove = -1;
    int move;

    if(play > maxPlay) maxPlay = play;
    positions++;

    if(play > 0) {
        score = evaluateForWinning(board, side);
        if(score != 0) return score;
    }

    for(int i = 0; i < 9; i++) {
        if(board[convertInto25[i]] == EMPTY) moveList[moveCount++] = convertInto25[i];
    }

    for(int i = 0; i < moveCount; i++) {
        move = moveList[i];
        board[move] = side;
        play++;
        score = -minMax(board, side ^ 1);

        if(score > bestScore) {
            bestScore = score;
            bestMove = move;
        }
        board[move] = EMPTY;
        play--;
    }

    if(moveCount == 0) bestScore = findThreeInRowAllBoard(board, side);
    if(play != 0) return bestScore;
    else return bestMove;
}

int getNextBest(const int *board) {
    int ourMove = convertInto25[inMiddle];
    if(board[ourMove] == EMPTY) return ourMove;
    ourMove = -1;
    for(int i = 0; i < 4; i++) {
        ourMove = convertInto25[corners[i]];
        if(board[ourMove] == EMPTY) {
            break;
        }
        ourMove = -1;
    }
    return ourMove;
}

int getWinningMove(int *board, const int side) {
    int ourMove = -1;
    int winMove =  0;
    for(int i = 0; i < 9; i++) {
        if(board[convertInto25[i]] == EMPTY) {
            ourMove = convertInto25[i];
            board[ourMove] = side;
            if(findThreeInRow(board, ourMove, side) == 3) {
                winMove = 1;
            }
            board[ourMove] = EMPTY;
            if(winMove == 1) {
                return ourMove;
            }
            ourMove = -1;
        }
    }
    return ourMove;
}
