#ifndef GAME_H
#define GAME_H

class Game
{
    private:
        int score;
        int level;
        int lines;
        int fallFrequency;

        bool Over;
        bool Storing;
        bool Pause;
        bool New;

    public:
        /* Constructor */
        Game();

        /* Access */
        int getScore();
        void setScore(int value);
        int getLevel();
        void setLevel(int value);
        int getFrequency();
        void setFrequency(int value);
        int getLines();
        void setLines(int value);
        bool getPaused();
        void setPaused(bool  b);
        bool getNew();
        void setNew(bool b);
        bool getStoring();
        void setStoring(bool b);
        bool isOver();
        void setOver(bool b);

        /* Tetris */
        void UpdateLevel();

};

#endif // GAME_H
