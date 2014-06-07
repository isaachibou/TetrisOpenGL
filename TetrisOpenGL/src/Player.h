//
//  Player.h
//  Tetris
//
//  Created by Thibault Miclo on 07/06/2014.
//  Copyright (c) 2014 to52. All rights reserved.
//

#ifndef __Tetris__Player__
#define __Tetris__Player__

#include <iostream>
#include "canvas.h"
#include "board.h"

class Player {
public:
    Player(Canvas win);
    ~Player();
    void play();
    int getByte(int byte, int nb);
    int getBestRow(Board solid);
    int getCurrentRow(Board ghost);
    int getLineSize(int l, int max);
    
private:
    boolean isTurnOver;
    Canvas game;
};

#endif /* defined(__Tetris__Player__) */
