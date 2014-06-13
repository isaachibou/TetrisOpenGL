#include <QApplication>
#include <QCoreApplication>

#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include <unistd.h>
#include <time.h>
#include <qtimer.h>


#include "board.h"
#include "shape.h"
#include "GlWindow.h"
#include "canvas.h"
#include "Player.h"

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

    Player ia;

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
                win.GenStock();
                win.GenShape();

            }
            else
            {
                /** Spawn the Shape **/
                if(win.GenShape()) { break; }
            }

            /* Start the Game */
            for(i=4;i<44;i++)
            {
                /** Drop the Shape **/
                if( !win.Detect(i) )
                {
                    QEventLoop loop;
                    QTimer::singleShot(win.getGame().getFrequency(), &loop, SLOT(quit()));
                    loop.exec();

                    win.Drop(i);

                    //IA plays
                    string move = ia.play(win.getGhost(),win.getSolid());
                    if(move == "left")
                    {
                          win.Left();
                    }
                    else if(move == "right") {
                          win.Right();
                    }





                    app.processEvents();
                }
                else
                {
                    win.Land(i);

                    QEventLoop l;
                    QTimer::singleShot(100, &l, SLOT(quit()));
                    l.exec();

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
                 win.updateContext();
            }
        }
            /* Game Over */
            win.GameOver();
            QEventLoop il;
            QTimer::singleShot(5000, &il, SLOT(quit()));
            il.exec();


    }




    return app.exec();
}
