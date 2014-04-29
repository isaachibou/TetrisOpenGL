#ifndef SHAPE_H
#define SHAPE_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>

class Shape
{
public:
    // Constructors
    Shape();

    // Destructor
    ~Shape();

    // Accessors
    int getLines(int i);

    // Calculation
    int* DevelopFloor(int i);
    int getHeight();

    // Display
    void drawShape();

    // Types
    void GetShape();



private:
    // Attributes
    int* Lines;
    int index;
    int Collection[7][4][4]=
    {
        {   // I
            {120,0,0,0},
            {16,16,16,16},
            {0,0,120,0},
            {32,32,32,32}
        },
        {   // J
            {64,112,0,0},
            {96,64,64,0},
            {112,32,0,0},
            {48,16,16,0}
        },
        {   // S
            {48,96,0,0},
            {32,48,16,0},
            {48,96,0,0},
            {64,96,32,0}
        },
        {
            // O
            {48,48,0,0},
            {48,48,0,0},
            {48,48,0,0},
            {48,48,0,0}
        },
        {
            // L
            {16,112,0,0},
            {48,16,16,0},
            {112,64,0,0},
            {96,64,64,0}
        },
        {   // Z
            {96,48,0,0},
            {16,48,32,0},
            {96,48,0,0},
            {32,96,64,0}
        },
        {   // T
            {32,112,0,0},
            {32,48,32,0},
            {112,32,0,0},
            {32,96,32,0}
        },

    };
};

#endif // SHAPE_H
