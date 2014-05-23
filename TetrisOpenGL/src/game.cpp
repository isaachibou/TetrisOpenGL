#include "game.h"

Game::Game()
{
    this->score = 0;
    this->level = 1;
    this->lines = 0;
    this->fallFrequency = 50000;
    this->Pause = false;
    this->New = true;
    this->Storing = false;
}

int
Game::getScore()
{
    return this->score;
}

void
Game::setScore(int value)
{
    this->score = value;
}

int
Game::getLines()
{
    return this->lines;
}

void
Game::setLines(int value)
{
    this->lines = value;
}

int
Game::getLevel()
{
    return this->level;
}

void
Game::setLevel(int value)
{
    this->level = value;
}

int
Game::getFrequency()
{
    return this->fallFrequency;
}

void
Game::setFrequency(int value)
{
    this->fallFrequency = value;
}

bool
Game::getStoring()
{
    return this->Storing;
}

void
Game::setStoring(bool b)
{
    this->Storing = b;
}

void
Game::UpdateLevel()
{
    if(this->lines == this->level * 10 )
    {
        this->level=this->level+1;
        this->fallFrequency -= 100*this->level;
    }
}

bool
Game::getPaused()
{
    return this->Pause;;
}

void
Game::setPaused(bool b)
{
    this->Pause = b;
}

bool
Game::getNew()
{
    return this->New;
}

void
Game::setNew(bool b)
{
    this->New = b;
}

bool
Game::isOver()
{
    return this->Over;
}

void
Game::setOver(bool b)
{
    this->Over = b;
}

