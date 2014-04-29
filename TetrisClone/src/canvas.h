#ifndef CANVAS_H
#define CANVAS_H

#include "GlWindow.h"
#include "board.h"

class Canvas : public GlWindow
{
public:
    Canvas();

    /*!
    *\brief Initialization des objets.
    */
    bool initializeObjects();

    /*!
    *\brief Rendu de la scène.
    */
    void render();

    // Accessors
    Board getBoard();
    Board getGhost();

    // Drawing
    void drawBoard();
    void drawEShape();

    // Key Input Handling
    void Rotate();
    void MoveLeft();
    void MoveRight();
    void keyPressEvent(QKeyEvent *);

private:
    // Attributes
    Board board;
    Board ghost;
};

#endif // CANVAS_H
