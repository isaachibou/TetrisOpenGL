#include "game.h"

Game::Game()
{
    this->score = 0;
    this->level = 0;
    this->fallFrequency = 100000;
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
