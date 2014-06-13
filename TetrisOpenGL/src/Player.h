#ifndef __Tetris__Player__
#define __Tetris__Player__

#include <iostream>
#include "canvas.h"
#include "board.h"

class Player {
public:
    Player();
    ~Player();
    string play(Board ghost, Board solid);
    int getByte(int byte, int nb);
    int getBestRow(Board solid);
    int getCurrentRow(Board ghost);
    int getLineSize(int l, int max);

private:
    boolean isTurnOver;
};

#endif
