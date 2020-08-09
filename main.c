#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h> 

enum { NOUGHT, CROSS, BORDER, EMPTY };
enum { HUMANWIN, COMPUTERWIN, DRAW };

const int directions[4] = { 1, 5, 4, 6 };

const int convertInto25[9] = {
    6 ,  7,  8,
    11, 12, 13,
    16, 17, 18
};

const int inMiddle = 4;
const int corners[4] = { 0, 2, 6, 8 };

int play = 0;
int positions = 0;
int maxPlay = 0;

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

int getComputerMove(int *board, const int side) {
    /*int numOfEmptySquares = 0;
    int availableSquares[9];
    int randMove = 0;

    randMove = getWinningMove(board, side);
    if(randMove != -1) {
        return randMove;
    }

    randMove = getWinningMove(board, side ^ 1);
    if(randMove != -1) {
        return randMove;
    }

    randMove = getNextBest(board);
    if(randMove != -1) {
        return randMove;
    }

    randMove = 0;
    for(int i = 0; i < 9; i++) {
        if(board[convertInto25[i]] == EMPTY) {
            availableSquares[numOfEmptySquares++] = convertInto25[i];
        }
    }

    randMove = rand() % numOfEmptySquares;
    return availableSquares[randMove];*/

    play = 0;
    positions = 0;
    maxPlay = 0;
    int best = minMax(board, side);
    printf("Finished Searching Positions: %d Max-Depth: %d Best Move: %d\n", positions, maxPlay, best);
    return best;
}

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

void runGame() {
    int gameOver = 0;
    int side = CROSS;
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

int main(int argc, char **argv) {
    srand(time(NULL));
    runGame();
    return 0;
} 