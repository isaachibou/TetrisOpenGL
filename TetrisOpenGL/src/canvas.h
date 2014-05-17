#ifndef Canvas_h
#define Canvas_h


#include "GlWindow.h"
#include "board.h"
#include <unistd.h>

using namespace std;


class Canvas : public GlWindow
{
    private:

        Board Solid;
        Board Ghost;
        Shape Current;

    public:

        Canvas();
        ~Canvas();


        /* Access */
        Board getSolid();
        Board getGhost();
        Shape getCurrent();
        void setSolidFloor(int i, int v);
        int getSolidFloor(int i);
        int getShapeHeigth();

        /* Actions */
        void GenShape();
        bool Spawn(Shape s);
        void Drop(int i);
        void Fall();
        void Left();
        void Right();
        void Rotate();
        bool Detect(int i);
        void Land(int i);
        void Clear(string Board);

        /* Calculation */
        int LocateShapeX();
        int LocateShapeY();

        /* Drawing */
        void timerEvent(QTimerEvent *);
        void paintGL();
        bool initializeObjects();
        void render();
        void drawBoard();
        void drawGhost();
        void drawFrame();

        /* Key Handling */
        void keyPressEvent(QKeyEvent *);
};


#endif