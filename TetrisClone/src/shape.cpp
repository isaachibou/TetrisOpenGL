#include "shape.h"

#include "iostream"

using namespace std;


Shape::Shape()
{
    this->index = 0;
    this->rotation = 0;

    for(int i=0;i<4;i++)
    {
        this->Lines[i] = 0;
    }
}

Shape::~Shape()
{

}

    // Accessors
int
Shape::getLines(int i)
{
    return this->Lines[i];
}

void
Shape::setLines(int i, int value)
{
    this->Lines[i] = value;
}
    // Calculation
int*
Shape::DevelopFloor(int i)
{
    string res;
    int floor = this->Lines[i];
    int SIZE = 10;
    int *Buffer = (int*) malloc(SIZE*sizeof(Buffer));

    for(i=0; i<10; i++)
    {
        if(floor%2 == 0)
        {
            res = '0' + res;
            floor /= 2;
        }
        else
        {
            res = '1' + res;
            floor /= 2;
        }
    }

    for(i=0; i<SIZE; i++)
    {
        Buffer[i] = res[i]-48;
    }

    return Buffer;
}

int
Shape::getHeight()
{
    int h=0;

    for(int i=0;i<4;i++)
    {
        if(this->Lines[i] != 0)
        { h++; }

    }

    return h;
}

int
Shape::getIndex()
{
    return this->index;
}

void
Shape::setIndex(int value)
{
    this->index = value;
}

int
Shape::getRotation()
{
    return this->rotation;
}

void
Shape::setRotation(int value)
{
    this->rotation = value;
}

int
Shape::getLineRotation(int rotation, int index,int k)
{
    return this->Collection[index][rotation][k];
}
    // Display
void
Shape::drawShape()
{
    int* tmp;
    char c =254, d=255;


    for(int i=0; i<4; i++)
    {
        printf("\n                            |");
        for(int j=0; j<10;j++)
        {
            tmp = DevelopFloor(i);
            if(tmp[j] == 1)
            {
                printf(" %c", c);
            }
            else
            {
                printf(" %c", d);
            }
        }
        printf(" |");
    }
}

    // Fill
void
Shape::GetShape()
{
    srand(time(NULL));

    int randNum = rand() %(0+6);

    for(int i=0;i<4;i++)
    {
        this->Lines[i] = this->Collection[randNum][0][i];
    }

    this->index = randNum;
}
