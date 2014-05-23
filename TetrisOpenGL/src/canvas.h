#ifndef Canvas_h
#define Canvas_h


#include "GlWindow.h"
#include "board.h"
#include "game.h"
#include "shape.h"
#include <unistd.h>

using namespace std;


class Canvas : public GlWindow
{
    private:

        Game Tetris;
        Board Solid;
        Board Ghost;
        Shape Current;
        Shape Stock;
        int Colors[40][10];

    public:

        Canvas();
        ~Canvas();


        /* Access */
        Board getSolid();
        Board getGhost();
        Shape getCurrent();
        Shape getStock();
        Game getGame();
        void setSolidFloor(int i, int v);
        int getSolidFloor(int i);
        int getShapeHeigth();

        /* Actions */
        bool GenShape();
        bool GenStock();
        bool Spawn(Shape s);
        void Drop(int i);
        void Left();
        void Right();
        void Rotate();
        void StockCurrent();
        bool Detect(int i);
        void Land(int i);
        void Clear(string Board);
        bool CleanFullLine();

        /* Game */
        void NewGame();
        void Pause();
        void ResetGame();
        void GameOver();
        void Store();
        /* Calculation */
        int LocateShapeY();

        /* Drawing */
        void timerEvent(QTimerEvent *);
        void paintGL();
        bool initializeObjects();
        void render();
        void drawBoard();
        void drawGhost();
        void drawStock();
        void drawFrame();
        void drawContext();
        void drawGameOver();
        void drawPause();

        /* Key Handling */
        void keyPressEvent(QKeyEvent *);
};


#endif
