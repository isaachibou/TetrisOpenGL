#include <QApplication>
#include <QCoreApplication>

#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include <unistd.h>
#include <time.h>

#include "board.h"
#include "shape.h"
#include "GlWindow.h"
#include "canvas.h"

#include <iostream>

using namespace std;


int main(int argc, char *argv[])
{
	QApplication app(argc, argv);

    // Console Init
    system("mode con LINES=50 COLS=80");

    int i = 4;

    Canvas win;
    win.show();

    usleep(10000);

    while(win.getGame().getNew())
    {
        while(win.getSolid().getFloor(0) == 0)
        {
            /* Init following the Game State */
            if(win.getGame().getNew())
            {
                win.NewGame();

                /* Empty Boards*/
                win.Clear("Ghost");
                win.Clear("Solid");

                /* Reset Game */
                win.ResetGame();
                win.getGame().setLines(0);
                win.getGame().setScore(0);
                win.getGame().setLevel(1);

                /* Restart a new game after a while ( wait the user to be ready) */
                sleep(1);
                win.GenShape();
            }
            else if(win.getGame().getStoring() == true)
            {
                win.GenStock();
                win.Store();
            }
            else
            {
                /** Spawn the Shape **/
                if(win.GenShape()) { break; }
            }

            /* Start the Game */
            for(i=4;i<44;i++)
            {
                if(win.getGame().getStoring() == true)
                {
                    break;
                }
                /** Drop the Shape **/
                if( !win.Detect(i) )
                {
                    usleep(win.getGame().getFrequency());
                    win.Drop(i);
                    app.processEvents();
                    system("cls");
                    win.getGhost().DrawConsoleBoard();
                }
                else
                {
                    win.Land(i);
                    usleep(10000);
                    break;
                }

                if(win.getGame().getNew())
                {
                    break;
                }
            }

            /* Points Computation */
            if(win.CleanFullLine() )
            {
                 win.Clear("Ghost");
                 win.getGame().UpdateLevel();
            }
         }
            /* Game Over */
            win.GameOver();
    }




    return app.exec();
}
