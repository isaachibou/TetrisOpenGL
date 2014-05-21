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

    Canvas win;
    win.show();



    while(win.getSolid().getFloor(0) == 0)
    {
        /** Spawn the Shape **/
        win.GenShape();
        win.GenStock();

        for(int i=4;i<44;i++)
        {
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
        }

        if(win.CleanFullLine() )
        {
             win.Clear("Ghost");
        }
     }




    return app.exec();
}
