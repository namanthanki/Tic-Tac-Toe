#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h> 
#ifndef DEFINITIONS_H
#define DEFINITIONS_H

//ENUMs
enum { NOUGHT, CROSS, BORDER, EMPTY };
enum { HUMANWIN, COMPUTERWIN, DRAW };

// GLOBALS
extern const int directions[4];
extern const int convertInto25[9];
extern const int corners[4];

extern const int inMiddle;
extern int play;
extern int positions;
extern int maxPlay;

//board.c
extern void initializeBoard(int *board);
extern void printBoard(const int *board);
extern int hasEmpty(const int *board);
extern void makeMove(int *board, const int sqr, const int side);

//human.c
extern int getHumanMove(const int *board);

//comp.c
extern int getComputerMove(int *board, const int side);

//winningRow.c
extern int getNumForDir(int startSquare, const int dir, const int *board, const int us); 
extern int findThreeInRow(const int *board, const int ourIndex, const int us);
extern int findThreeInRowAllBoard(const int *board, const int us);
extern int evaluateForWinning(const int *board, const int us);

//run.c
extern void runGame();

//evaluation.c
extern int minMax(int *board, int side);
extern int getNextBest(const int *board);
extern int getWinningMove(int *board, const int side);

#endif 