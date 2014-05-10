#include <QApplication>

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

    return app.exec();
}
