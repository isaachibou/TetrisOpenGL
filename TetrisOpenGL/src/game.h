#ifndef GAME_H
#define GAME_H

class Game
{
    private:
        int score;
        int level;
        int fallFrequency;

    public:
        /* Constructor */
        Game();
        int getScore();
        void setScore(int value);
        int getLevel();
        void setLevel(int value);
        int getFrequency();
        void setFrequency(int value);
};

#endif // GAME_H
