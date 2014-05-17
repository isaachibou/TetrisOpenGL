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

    this->Solid.setFloor(0,512+256+1+2);
    this->Solid.setFloor(2,64+32+16+8);



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

Shape
Canvas::getCurrent()
{
    return this->Current;
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
    for(int i=4;i<43;i++)
    {
//        if(this->Ghost.getFloor(i) != 0)
//        {
            if( !getSolid().DetectCollision(getGhost(),h,i) )
            {
                usleep(10000);
                Drop(i);
                system("cls");
                getGhost().DrawConsoleBoard();

            }
//        }
    }
}

void
Canvas::Left()
{
    int *tmp;
    int tmp_array[4] = {0};

    bool crash = 0;

    int i=0;
    int h = this->Current.getHeight();
    int k = LocateShapeY();
    int o = this->Current.getOffSet();

    for(i=k; i<k+h; i++)
    {
        tmp = this->Ghost.DevelopFloor(i);
        /* Check if the Shape is not already against the Left border */
        if( tmp[0] != 0 )
        {
            crash = 1;
            break;
        }

        /* If no Collision are predicted for this line save its value and Left Offset it */
        tmp_array[i] = this->Ghost.getFloor(i);
        if(this->Ghost.getFloor(i) != 0) { tmp_array[i] = tmp_array[i] << 1; }

        /* Check if Solid current content will collide after Left Offset */
        if( (this->Solid.getFloor(i) & tmp_array[i]) != 0 )
        {
            crash = 1;
            break;
        }
    }

    if( !crash )
    {
        /* No Collision predicted movement is allowed */
        for(i=k; i<k+h; i++)
        {
            this->Ghost.setFloor(i,tmp_array[i]);
        }

        /* Update Shape Info */
        o--;
        this->Current.setOffSet(o);
    }

}

void
Canvas::Right()
{
    int *tmp;
    int tmp_array[4] = {0};

    bool crash = 0;

    int i=0;
    int h = this->Current.getHeight();
    int k = LocateShapeY();
    int o = this->Current.getOffSet();

    for(i=k; i<k+h; i++)
    {
        tmp = this->Ghost.DevelopFloor(i);
        /* Check if the Shape is not already against the Left border */
        if( tmp[9] != 0 )
        {
            crash = 1;
            break;
        }

        /* If no Collision are predicted for this line save its value and Left Offset it */
        tmp_array[i] = this->Ghost.getFloor(i);
        if(this->Ghost.getFloor(i) != 0) { tmp_array[i] = tmp_array[i] >> 1; }

        /* Check if Solid current content will collide after Left Offset */
        if( (this->Solid.getFloor(i) & tmp_array[i]) != 0 )
        {
            crash = 1;
            break;
        }
    }

    if( !crash )
    {
        /* No Collision predicted movement is allowed */
        for(i=k; i<k+h; i++)
        {
            this->Ghost.setFloor(i,tmp_array[i]);
        }

        /* Update Shape Info */
        o++;
        this->Current.setOffSet(o);
    }

}

void
Canvas::Rotate()
{
    int tmp_array[4] = {0};
    int rotation = this->Current.getRotation();
    int index = this->Current.getIndex();
    int offset = this->Current.getOffSet();
    int tmp,o,j;

    rotation++;

    for(int k=0; k<this->Ghost.getHeight();k++)
    {
        /* Top line of the Shape found */
        if(this->Ghost.getFloor(k) != 0)
        {

            for(j=0;j<4;j++)
            {
                tmp = this->Current.getLineRotation(rotation,index,j);

                /* Offset Line on Left or Right following the position of the Shape prior to the rotation */
                if(offset >= 0)
                {
                    for(o=0; o<offset; o++)
                    {
                        tmp = tmp >> 1;
                    }
                }
                else
                {
                    for(o=0; o > offset; o--)
                    {
                        tmp = tmp << 1;
                    }
                }

                /* Store the rotated Shape Lines */
               tmp_array[j] = tmp;
            }
            break;
        }
    }

}

bool
Canvas::Detect(int i)
{
    int h = this->Ghost.getShapeH();
    return this->Solid.DetectCollision(this->Ghost,h,i);
}

void
Canvas::Land(int i)
{
    int h = this->Ghost.getShapeH();
    this->Solid.LandShape(this->Ghost,h,i);
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
    bool b;
    b=Spawn(Current);
}

void
Canvas::Clear(string Board)
{
    if(Board == "Ghost") { this->Ghost.ReInitBoard(40,10); }
    if(Board == "Solid") { this->Solid.ReInitBoard(40,10); }
}

    /* Calculation */


int
Canvas::LocateShapeY()
{
    for(int i=0;i < this->Ghost.getHeight();i++)
    {
        if(this->Ghost.getFloor(i) != 0)
        {
            return i;
            break;
        }
    }

}
    /* Drawing */

void
Canvas::timerEvent(QTimerEvent *)
{
    update();
}

void
Canvas::paintGL()
{
    // Nettoyage du Color Buffer et du Depth Buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    render();

}

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

    //    /** Spawn the Shape **/
    //    GenShape();




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
                glColor3f(1.0f, 0.0f, 0.0f);
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
            Clear("Ghost");
            GenShape();
            break;

        case Qt::Key_U:
            update();
        break;

        case Qt::Key_E:
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clean the screen and the depth buffer
            glLoadIdentity();
        break;

    }
}
