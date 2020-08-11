#include "definitions.h"

const int directions[4] = {
    1, 5, 4, 6 
};
const int convertInto25[9] = {
    6 ,  7,  8,
    11, 12, 13,
    16, 17, 18
};
const int corners[4] = { 0, 2, 6, 8 };

const int inMiddle = 4;
int play = 0;
int positions = 0;
int maxPlay = 0;

int main(int argc, char **argv) {
    srand(time(NULL));
    runGame();
    return 0;
} 