#include "board.h"


#include "iostream"

using namespace std;

    // Constructors
Board::Board()
{
    this->height = 40;
    this->width = 10;
    for(int i=0; i < height; i++)
    {
        this->Floor[i] = 0;
    }
}

Board::Board(int l, int w)
{
    this->height = l;
    this->width = w;
    for(int i=0; i < this->height; i++)
    {
        this->Floor[i] = 0;
    }
}

    // Destructors
Board::~Board()
{

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

int
Board::getShapeH()
{
    int h=0;

    for(int i=0;i<40;i++)
    {
        if(this->Floor[i] != 0)
        { h++; }

    }

    return h;
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
bool
Board::SpawnShape(Board Solid, Shape s)
{
    bool crash = 0;
    int i;
    for(i=0;i<4;i++)
    {
        if( (s.getLines(i) & Solid.getFloor(i)) != 0 )
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

    return crash;
}

void
Board::DropShape(int i)
{
      this->Floor[i] = this->Floor[i-1];
      this->Floor[i-1] = this->Floor[i-2];
      this->Floor[i-2] = this->Floor[i-3];
      this->Floor[i-3] = this->Floor[i-4];
      this->Floor[i-4] = 0;
}

void
Board::LandShape(Board Ghost, int h, int i)
{
    int j=i-4;
    int end = j +h;

    if(i == 4 && h == 1 && this->Floor[1] != 0)
    {
        for(j=j;j<i;j++)
        {
            this->Floor[j-1] = this->Floor[j-1] + Ghost.getFloor(j);
        }
    }
    if(h == 1)
    {
        this->Floor[i-4] = this->Floor[i-4] + Ghost.getFloor(i-4);
    }
    else
    {
        for(j=j;j<end;j++)
        {
            this->Floor[j] = this->Floor[j] + Ghost.getFloor(j);
        }
    }

}

bool
Board::DetectCollision(Board Ghost, int h, int i)
{
    bool crash = 0;
    int j=i-4;
    int laps = j+h;
    if(laps > 40) { laps = 40; }
    if( i == 44-h)
    { return crash=1; }
    else
    {
        for(j=j;j<laps;j++)
        {
            if((Ghost.getFloor(j) & this->Floor[j+1]) != 0)
            {
                return crash = 1;
            }
        }
    }

    return crash;

}

void
Board::MoveLeft()
{
    int *tmp;
    for(int i=0; i< getHeight(); i++)
    {
            tmp = DevelopFloor(i);
            if( (tmp[0] != 0) || (tmp[9] != 0) )
            {
                system("cls");
            }
            else
            {
                if(this->Floor[i] != 0)
                {
                    this->Floor[i] = this->Floor[i] << 1;
                }
            }
    }

}

void
Board::MoveRight()
{
    int *tmp;
    for(int i=0; i< getHeight(); i++)
    {
            tmp = DevelopFloor(i);
            if( (tmp[0] != 0) || (tmp[9] != 0) )
            {
                system("cls");
            }
            else
            {
                if(this->Floor[i] != 0)
                {
                    this->Floor[i] = this->Floor[i] >> 1;
                }
            }
    }

}

    // Display
void
Board::DrawConsoleBoard()
{
    int* tmp;
    char c =254, d=255;


    for(int i=0; i< getHeight(); i++)
    {
        if(i<10)
        { printf("\n                            %d     |",i); }
        else
        { printf("\n                            %d    |",i); }

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
        printf("  |");
    }
}

void
Board::ReInitBoard(int h, int w)
{
    for(int i=0 ; i < getHeight();i++)
    {
        setFloor(i,0);
    }
    this->height = h;
    this->width = w;
}
