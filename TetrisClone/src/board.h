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
    void SpawnShape(Shape s);
    void DropShape(Shape s, int i);
    void LandShape(Board Ghost, Shape s, int i);
    bool DetectCollision(Board Ghost, Shape s, int i);


    // Display
    void DrawConsoleBoard();
    void ReInitBoard();

private:
    // Attributes
    int height;
    int width;
    int* Floor;
};

#endif // BOARD_H
