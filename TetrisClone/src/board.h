#ifndef BOARD_H
#define BOARD_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "shape.h"

class Board
{

public:
    // Constructors
    Board();
    Board(int h, int w);

    // Destructors
    ~Board();

    // Accessors
    int getFloor(int i);
    void setFloor(int i, int value);
    int getHeight();
    int getWidth();

    // Calculation
    int* DevelopFloor(int i);

    // Action
    bool SpawnShape(Board Solid, Shape s);
    void DropShape(int i);
    void LandShape(Board Ghost, int h, int i);
    bool DetectCollision(Board Ghost, int h, int i);
    void MoveLeft();
    void MoveRight();


    // Display
    void DrawConsoleBoard();
    void ReInitBoard(int h, int w);

private:
    // Attributes
    int height;
    int width;
    int Floor[40];
};

#endif // BOARD_H
