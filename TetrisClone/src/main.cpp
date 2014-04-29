#include <QApplication>

#include <stdlib.h>
#include <stdio.h>
#include <windows.h>

#include "canvas.h"
#include "board.h"
#include "shape.h"

#include <iostream>

using namespace std;


int main(int argc, char *argv[])
{
	QApplication app(argc, argv);

    // Console Init
    system("mode con LINES=50 COLS=80");

    Canvas win;
    Shape Current;

    Board Solid, Ghost;

    Current.GetShape();
    //Current.drawShape();


    Solid.SpawnShape(Current);
    Solid.DropShape(Current,2);
    Solid.DrawConsoleBoard();


    printf("\n\n");

	return app.exec();
}
