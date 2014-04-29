#include "board.h"


#include "iostream"

using namespace std;

    // Constructors
Board::Board()
{
    this->height = 40;
    this->width = 10;
    this->Floor = (int*) malloc(height* sizeof(int));
    if(this->Floor == NULL)
    {
        printf("\n\n Board Memory Allocation Failed");
        exit(0);
    }
    for(int i=0; i < height; i++)
    {
        this->Floor[i] = 0;
    }
}

Board::Board(int l, int w)
{
    this->height = l;
    this->width = w;
    if(this->height > 0)
    {
        this->Floor = (int*) malloc(this->height* sizeof(int));
    }
    if(this->Floor == NULL)
    {
        printf("\n\n Board Memory Allocation Failed");
        exit(0);
    }
    for(int i=0; i < this->height; i++)
    {
        this->Floor[i] = 0;
    }
}

    // Destructors
Board::~Board()
{
    free(this->Floor);
}

    // Accessors
int
Board::getFloor(int i)
{
    return this->Floor[i];
}

void
Board::setFloor(int i, int value)
{
    if(i < 40)
    {
        this->Floor[i] = value;
    }
}

int
Board::getHeight()
{
    return this->height;
}

int
Board::getWidth()
{
    return this->width;
}

    // Calculation
int*
Board::DevelopFloor(int i)
{
        string res;
        int floor = this->Floor[i];
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

    // Action
void
Board::SpawnShape(Shape s)
{
    bool crash = 0;
    int i;
    for(i=0;i<4;i++)
    {
        if( (s.getLines(i) & this->Floor[i]) != 0 )
        {
            crash = 1;
        }
    }
    if(!crash)
    {
        for (i=0;i<4;i++)
        {
            this->Floor[i] = s.getLines(i);
        }
    }
}

void
Board::DropShape(Shape s,int i)
{
     int h = s.getHeight();
     i -= h;
     for(int j = i + h; j > -1; j--)
     {
          if(!(j == i))
          { this->Floor[j] = this->Floor[j-1]; }
          else
          { this->Floor[j] = 0; }
     }
}

void
Board::LandShape(Board Ghost, Shape s, int i)
{
    int h = s.getHeight();
    int j=i-h;

    if(i == 2 && h == 1 && this->Floor[1] != 0)
    {
        for(j=j;j<i;j++)
        {
            this->Floor[j-1] = this->Floor[j-1] + Ghost.getFloor(j);
        }
    }
    else
    {
        for(j=j;j<i;j++)
        {
            this->Floor[j-1] = this->Floor[j] + Ghost.getFloor(j);
        }
    }

}

bool
Board::DetectCollision(Board Ghost, Shape s, int i)
{
    bool crash = 0;
    int h = s.getHeight();
    int j=i-h;

    if(i == 40)
    { crash = 1; }
    else
    {
        for(j=j;j<i;j++)
        {
            if( (Ghost.getFloor(j) & this->Floor[j+1]) != 0 )
            { crash = 1; }
        }
    }

    return crash;
}


    // Display
void
Board::DrawConsoleBoard()
{
    int* tmp;
    char c =254, d=255;


    for(int i=0; i< getHeight(); i++)
    {
        printf("\n                            |");
        for(int j=0; j<getWidth();j++)
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

void
Board::ReInitBoard()
{
    for(int i=0 ; i < getHeight();i++)
    {
        setFloor(i,0);
    }
}
