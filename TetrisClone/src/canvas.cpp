#include "canvas.h"

#include "iostream"

using namespace std;

// Axis Stuff
GLfloat g_TabVertices[]=
{
    0,0,0,
    0,40,0,
    0,0,0,
    10,0,0,
    10,0,0,
    10,40,0
};

GLfloat g_TabColors[]=
{
    0,1,0,
    0,1,0,
    0,1,0,
    0,1,0,
    0,1,0,
    0,1,0
};

// E Shape
GLfloat EColor[]={  127,0,255,127,0,255,127,0,255,127,0,255,127,0,255,127,0,255,127,0,255,127,0,255,127,0,255,};

GLfloat EShape[]= {0,0,0,1,0,0,2,0,0,3,0,0,0,1,0,1,1,0,2,1,0,3,1,0,1,2,0,2,2,0};

GLuint EIndices[] = {0,1,5,5,4,0,1,2,6,6,5,1,2,3,7,7,6,2,5,6,9,9,8,5};

    // Constructors
Canvas::Canvas()
{
   this->board.ReInitBoard();
   this->ghost.ReInitBoard();
}

    // Accessors
Board
Canvas::getBoard()
{
    return this->board;
}

Board
Canvas::getGhost()
{
    return this->ghost;
}


    // Drawings
bool
Canvas::initializeObjects()
{
    // Fond gris
    glClearColor( 0.5f, 0.5f, 0.5f, 1.0f );
    glEnable( GL_DEPTH_TEST );

    // Chargement des shaders
    createShader( "Shaders/color" );

    return true;
}


void
Canvas::render()
{
    // Initialisation de la caméra
    lookAt( 12, 30, 75, 12, 30, 50);


    // Rendu des objets
    pushMatrix();


        computeAncillaryMatrices();

        useShader( "color" );
        GLint var_id = glGetUniformLocation( getCurrentShaderId(), "MVP" );
        transmitMVP( var_id );


            GLint var1 = glGetAttribLocation( getCurrentShaderId(), "position" );
            glEnableVertexAttribArray( var1 );
            glVertexAttribPointer( var1, 3, GL_FLOAT, GL_FALSE, 0, g_TabVertices );
            GLint var2 = glGetAttribLocation( getCurrentShaderId(), "color" );
            glEnableVertexAttribArray( var2 );
            glVertexAttribPointer( var2, 3, GL_FLOAT, GL_FALSE, 0, g_TabColors );
            glDrawArrays( GL_LINES, 0, 8 );
            glDisableVertexAttribArray( var1 );
            glDisableVertexAttribArray( var2 );
    popMatrix();
    pushMatrix();
        //drawBoard();
    popMatrix();
   /* pushMatrix();
        translate(3,38,0);
        drawEShape();
    popMatrix();*/
}

void
Canvas::drawBoard()
{
    int h=getBoard().getHeight();
    int w=getBoard().getWidth();
    int* tmp;
    for(int i=0; i < h; i++)
    {
        tmp = getBoard().DevelopFloor(i);
        for(int j=0; j < w; j++)
        {
            if(tmp[j] == 1)
            {
                glColor3f(0.0f, 0.0f, 1.0f);
                glRecti(j,h-i-1,j+1,h-i);
            }
        }
    }
}

void
Canvas::drawEShape()
{
    GLuint ebo;
    computeAncillaryMatrices();

    useShader( "color" );
    GLint var_id = glGetUniformLocation( getCurrentShaderId(), "MVP" );
    transmitMVP( var_id );

    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(EIndices),EIndices,GL_STATIC_DRAW);
    GLint var1 = glGetAttribLocation( getCurrentShaderId(), "position" );
    glEnableVertexAttribArray( var1 );
    glVertexAttribPointer( var1, 3, GL_FLOAT, GL_FALSE, 0, EShape );
    GLint var2 = glGetAttribLocation( getCurrentShaderId(), "color" );
    glEnableVertexAttribArray( var2 );
    glVertexAttribPointer( var2, 3, GL_FLOAT, GL_FALSE, 0, EColor );
    glDrawElements(GL_TRIANGLES, 27, GL_UNSIGNED_INT, 0);
    glDisableVertexAttribArray( var1 );
    glDisableVertexAttribArray( var2 );
}

    // Key Input Handling
void
Canvas::Rotate()
{
    rotate( 90, 0, 0, 1 );
}

void Canvas::MoveLeft()
{
   // pushMatrix();
        translate(-1,0,0);
   //popMatrix();
}

void Canvas::MoveRight()
{
    translate(1,0,0);
}

void
Canvas::keyPressEvent( QKeyEvent* event )
{
    switch( event->key())
    {
        case Qt::Key_Escape:
            close();
            break;

        case Qt::Key_Left:
            MoveLeft();
            break;

        case Qt::Key_Right:
            MoveRight();
            break;

        case Qt::Key_Up:
            Rotate();
            break;

        case Qt::Key_Down:

            break;

        case Qt::Key_R:

            break;
    }
}

