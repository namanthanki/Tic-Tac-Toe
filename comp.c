#include "definitions.h"

int getComputerMove(int *board, const int side) {
    play = 0;
    positions = 0;
    maxPlay = 0;
    int best = minMax(board, side);
    printf("Finished Searching Positions: %d Max-Depth: %d Best Move: %d\n", positions, maxPlay, best);
    return best;
}