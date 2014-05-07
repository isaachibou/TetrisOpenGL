#include "Canvas.h"


#include "Shapes/Basis.h"

#include <iostream>

using namespace std;


GLfloat angle1 = 30.0f;
GLfloat angle2 = 20.0f;

const GLfloat g_AngleSpeed = 10.0f;


Basis* g_Basis;


Canvas::Canvas()
{
    setWindowTitle(trUtf8("IN55-Canvas"));

    g_Basis = new Basis( 10.0 );

}


Canvas::~Canvas()
{
    delete g_Basis;
}

    /* Access */
Board
Canvas::getSolid()
{
    return this->Solid;
}

Board
Canvas::getGhost()
{
    return this->Ghost;
}

void
Canvas::setSolidFloor(int i, int v)
{
    this->Solid.setFloor(i,v);
}

int
Canvas::getSolidFloor(int i)
{
    this->Solid.getFloor(i);
}

    /* Actions */
bool
Canvas::Spawn(Shape s)
{
    return this->Ghost.SpawnShape(getSolid(),s);
}

void
Canvas::Drop(int i)
{
   this->Ghost.DropShape(i);
}

void
Canvas::Fall()
{
    int h = this->Current.getHeight();
    for(int i=4;i<44;i++)
    {
        if( !getSolid().DetectCollision(getGhost(),h,i) )
        {
            Drop(i);
            system("cls");
            getGhost().DrawConsoleBoard();
        }
    }
}

void
Canvas::Left()
{
    int *tmp;
    bool end = 0;
    for(int i=0; i< this->Current.getHeight(); i++)
    {
        tmp = this->Ghost.DevelopFloor(i);
        if( tmp[0] != 0 )
        {
            system("cls");
            end = 1;
        }
    }
    if( !end )
    {
        for(int i=0; i< this->Current.getHeight(); i++)
        {
            tmp = this->Ghost.DevelopFloor(i);
            if(this->Ghost.getFloor(i) != 0)
            {
                this->Ghost.setFloor(i,this->Ghost.getFloor(i) << 1);
            }
        }
    }
        system("cls");
        getGhost().DrawConsoleBoard();
}

void
Canvas::Right()
{
    int *tmp;
    bool end = 0;
    for(int i=0; i< this->Current.getHeight(); i++)
    {
        tmp = this->Ghost.DevelopFloor(i);
        if( tmp[9] != 0 )
        {
            system("cls");
            end = 1;
        }
    }
    if( !end )
    {
        for(int i=0; i< this->Current.getHeight(); i++)
        {
            tmp = this->Ghost.DevelopFloor(i);
            if(this->Ghost.getFloor(i) != 0)
            {
                this->Ghost.setFloor(i,this->Ghost.getFloor(i) >> 1);
            }
        }
    }
        system("cls");
        getGhost().DrawConsoleBoard();
}

void
Canvas::Rotate()
{
    int i = this->Current.getIndex();
    int tmp;
    i++;

    for(int k=0; k< this->Current.getHeight(); k++)
    {
        // top line of the shape found
        if(this->Ghost.getFloor(k) != 0)
        {
            for(int j=0; j<this->Current.getHeight();j++)
            {
                // Replace line with rotated shape line
                tmp = this->Current.getLineRotation(this->Current.getIndex(),i,j);
                this->Ghost.setFloor(i,tmp);
            }
            break;
        }
    }
}

int
Canvas::getShapeHeigth()
{
    return this->Current.getHeight();
}

void
Canvas::GenShape()
{
    this->Current.GetShape();
    this->Current.setIndex(0);
}

    /* Drawing */
bool
Canvas::initializeObjects()
{
    // Fond gris
    glClearColor( 0.2f, 0.2f, 0.2f, 1.0f );
    glEnable( GL_DEPTH_TEST );

    // Chargement des shaders
    createShader( "Shaders/color" );

    cout << "Shader color: ";
    if (useShader( "color" ))
    {
        cout << "Loaded!" << endl;
    }
    else
    {
        cout << "NOT Loaded!" << endl;
    }

    glScalef(0.04f, 0.04f, 0.1f);
    glTranslatef(-22,-22,0);

    /** Spawn the Shape **/
    GenShape();
    bool b;
    b=Spawn(Current);
//    getGhost().DrawConsoleBoard();



    return true;
}

void
Canvas::render()
{
    // Rendu des objets
    pushMatrix();
        drawFrame();
    popMatrix();
    pushMatrix();
        drawBoard();
    popMatrix();
    pushMatrix();
        drawGhost();
    popMatrix();

}

void
Canvas::drawFrame()
{
    glBegin(GL_LINE_STRIP);
        glColor3f(0.0f, 1.0f, 0.0f);
        glVertex3f(0.0f, 40.0f, 0.0f);
        glVertex3f(0.0f, 0.0f, 0.0f);
        glVertex3f(10.0f, 0.0f, 0.0f);
        glVertex3f(10.0f, 40.0f, 0.0f);
    glEnd();
}

void
Canvas::drawBoard()
{
    int h=getSolid().getHeight();
    int w=getSolid().getWidth();
    int* tmp;
    for(int i=0; i < h; i++)
    {
        tmp = getSolid().DevelopFloor(i);
        for(int j=0; j < w; j++)
        {
            if(tmp[j] == 1)
            {
                glBegin(GL_LINE_LOOP);
                    glColor3f(1.0f, 1.0f, 1.0f);
                    glVertex3f(j,h-i-1,0.0f);
                    glVertex3f(j,h-i,0.0f);
                    glVertex3f(j+1,h-i,0.0f);
                    glVertex3f(j+1,h-i-1,0.0f);
                glEnd();
                glColor3f(0.0f, 0.0f, 1.0f);
                glRecti(j,h-i-1,j+1,h-i);
            }
        }
    }
}

void
Canvas::drawGhost()
{
    int h=getSolid().getHeight();
    int w=getSolid().getWidth();
    int* tmp;
    for(int i=0; i < h; i++)
    {
        tmp = getGhost().DevelopFloor(i);
        for(int j=0; j < w; j++)
        {
            if(tmp[j] == 1)
            {
                glBegin(GL_LINE_LOOP);
                    glColor3f(1.0f, 1.0f, 1.0f);
                    glVertex3f(j,h-i-1,0.0f);
                    glVertex3f(j,h-i,0.0f);
                    glVertex3f(j+1,h-i,0.0f);
                    glVertex3f(j+1,h-i-1,0.0f);
                glEnd();
                glColor3f(0.0f, 0.0f, 1.0f);
                glRecti(j,h-i-1,j+1,h-i);
            }
        }
    }
}


    /* Key Handling */
void
Canvas::keyPressEvent( QKeyEvent* event )
{
    switch( event->key())
    {
        case Qt::Key_Escape:
            close();
            break;

        case Qt::Key_Left:
            Left();
            break;

        case Qt::Key_Right:
            Right();
            break;

        case Qt::Key_Up:
            Rotate();
            break;

        case Qt::Key_Down:
            Drop(4);
            break;

        case Qt::Key_R:
            angle1 = angle2 = 0.0f;
            break;
    }
}
