#include "Canvas.h"

#include <iostream>

using namespace std;


int speedSave = 0;


Canvas::Canvas()
{
    setWindowTitle(trUtf8("Tetris OpenGL"));


}


Canvas::~Canvas()
{

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

Shape
Canvas::getStock()
{
    return this->Stock;
}

Game
Canvas::getGame()
{
    return this->Tetris;
}

void
Canvas::setSolidFloor(int i, int v)
{
    this->Solid.setFloor(i,v);
}

int
Canvas::getSolidFloor(int i)
{
    return this->Solid.getFloor(i);
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
Canvas::Left()
{
    int *tmp;
    int tmp_array[4] = {0};

    bool crash = 0;

    int i=0,j=0;
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
        tmp_array[j] = this->Ghost.getFloor(i);
        if(this->Ghost.getFloor(i) != 0) { tmp_array[j] = tmp_array[j] << 1; }

        /* Check if Solid current content will collide after Left Offset */
        if( (this->Solid.getFloor(i) & tmp_array[j]) != 0 )
        {
            crash = 1;
            break;
        }
        j++;
    }

    if( !crash )
    {
        j=0;
        /* No Collision predicted movement is allowed */
        for(i=k; i<k+h; i++)
        {
            this->Ghost.setFloor(i,tmp_array[j]);
            j++;
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

    int i=0,j=0;
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
        tmp_array[j] = this->Ghost.getFloor(i);
        if(this->Ghost.getFloor(i) != 0) { tmp_array[j] = tmp_array[j] >> 1; }

        /* Check if Solid current content will collide after Left Offset */
        if( (this->Solid.getFloor(i) & tmp_array[j]) != 0 )
        {
            crash = 1;
            break;
        }
        j++;
    }

    if( !crash )
    {
        j=0;
        /* No Collision predicted movement is allowed */
        for(i=k; i<k+h; i++)
        {
            this->Ghost.setFloor(i,tmp_array[j]);
            j++;
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

    bool crash = 0;

    if(this->Ghost.getShapeH()==1) { j=j;}
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
                        if(tmp != 1) { tmp = tmp >> 1; }
                        else { crash = 1; break; }
                    }
                }
                else
                {
                    for(o=0; o > offset; o--)
                    {
                        if(tmp != 512) { tmp = tmp << 1; }
                        else { crash = 1; break; }
                    }
                }

                /* Store the rotated Shape Lines */
               tmp_array[j] = tmp;
               if( (this->Solid.getFloor(k+j) & tmp_array[j]) != 0)
               {
                   crash = 1;
                   break;
               }
            }
            break;
        }
    }

    if( !crash)
    {
        for(int k=0; k<this->Ghost.getHeight();k++)
        {
            /* Top line of the Shape found */
            if(this->Ghost.getFloor(k) != 0)
            {
                for(j=0;j<4;j++)
                {
                    /* Fill Ghost with Rotated Shape */
                   this->Ghost.setFloor(k+j, tmp_array[j]);

                    /* Update Shape Info */
                    this->Current.setLines(j,tmp_array[j]);

                    if(this->Current.getRotation() < 3) { this->Current.setRotation(rotation); }
                    else { this->Current.setRotation(-1); }
                }
                break;
            }
        }
    }

}

void
Canvas::Down()
{
   speedSave = this->Tetris.getFrequency();
   this->Tetris.setFrequency(speedSave/5);
}

void
Canvas::GameOver()
{
    this->Tetris.setOver(true);
}

void
Canvas::Store()
{
    this->Tetris.setStoring(!this->Tetris.getStoring());
}

void
Canvas::updateContext()
{
    this->Tetris.UpdateLevel();
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

    int j=i-4;
    int end = j +h;
    int* tmp;

    for(j=j;j<end;j++)
    {
       tmp = this->Ghost.DevelopFloor(j);
       for(int k=0;k<10;k++)
       {
           if(tmp[k] == 1)
           {
               this->Colors[j][k] = this->Current.getIndex();
           }
       }
    }
}

int
Canvas::getShapeHeigth()
{
    return this->Current.getHeight();
}

bool
Canvas::GenShape()
{

    this->Current.GetThisShape(this->Stock);
    this->Current.setOffSet(0);

    this->Stock.GetShape();
    this->Stock.setOffSet(0);

    bool b;
    b=Spawn(Current);

    return b;
}

void
Canvas::GenStock()
{
    this->Stock.GetShape();
    this->Stock.setOffSet(0);
}

void
Canvas::Clear(string Board)
{
    if(Board == "Ghost") { this->Ghost.ReInitBoard(40,10); }
    if(Board == "Solid") { this->Solid.ReInitBoard(40,10); }
}

bool
Canvas::CleanFullLine()
{
    int currentLines = this->Tetris.getLines();
    int Score = this->Tetris.getScore();



    int Lines = this->Solid.ClearFullLines();

    switch(Lines)
    {
        case 1:
            Score += 40;
            break;
        case 2:
            Score += 100;
            break;
        case 3:
            Score += 200;
            break;
        case 4:
            Score += 400;
            break;
    }

    this->Tetris.setLines(Lines + currentLines);

    this->Tetris.setScore(Score);

    return true;
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
    /* Game */
void
Canvas::Pause()
{
    this->Tetris.setPaused(!this->Tetris.getPaused());
}

void
Canvas::NewGame()
{
    this->Tetris.setNew(!this->Tetris.getNew());
}

void
Canvas::ResetGame()
{
    this->Tetris.setLines(0);
    this->Tetris.setScore(0);
    this->Tetris.setLevel(1);
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




    return true;
}

void
Canvas::render()
{
    // Rendu des objets

    if(this->Tetris.isOver())
    {
        pushMatrix();
            drawGameOver();
        popMatrix();
        pushMatrix();
            drawBoard();
        popMatrix();
    }
    else
    {
        pushMatrix();
            drawBoard();
        popMatrix();
        pushMatrix();
            drawGhost();
        popMatrix();
        pushMatrix();
            drawFrame();
        popMatrix();
        pushMatrix();
            drawStock();
        popMatrix();
        pushMatrix();
            drawContext();
        popMatrix();
    }


}

void
Canvas::drawFrame()
{
    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);

    glBegin(GL_LINE_STRIP);
        glColor3f(0.0f, 1.0f, 0.0f);
        glVertex3f(0.0f, 40.0f, 0.0f);
        glVertex3f(0.0f, 0.0f, 0.0f);
        glVertex3f(10.0f, 0.0f, 0.0f);
        glVertex3f(10.0f, 40.0f, 0.0f);
    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f);
    glRecti(12.0f, 34.0f, 20.0f, 39.0f);

    glColor3f(0.0f, 0.0f, 0.0f);
    glRecti(12.0f, 28.0f, 20.0f, 33.0f);

    glColor3f(0.0f, 0.0f, 0.0f);
    glRecti(12.0f, 22.0f, 20.0f, 27.0f);

    glColor3f(0.0f, 0.0f, 0.0f);
    glRecti(13.0f, 16.0f, 20.0f, 20.0f);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
}

void
Canvas::drawBoard()
{
    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    float opacity = 1.0f;
    int h=getSolid().getHeight();
    int w=getSolid().getWidth();
    int* tmp;
    int red,green,blue;

    for(int i=0; i < h; i++)
    {
        tmp = getSolid().DevelopFloor(i);
        for(int j=0; j < w; j++)
        {
            if(tmp[j] == 1)
            {
                switch(this->Colors[i][j])
                {
                    case 0:
                        red = 0; green = 0; blue = 1;
                        break;

                    case 1:
                        red = 0; green = 1; blue = 1;
                        break;

                    case 2:
                        red = 1; green = 0; blue = 1;
                        break;

                    case 3:
                        red = 1; green = 0; blue = 0;
                        break;

                    case 4:
                        red = 0; green = 1; blue = 0;
                        break;

                    case 5:
                        red = 1; green = 1; blue = 0;
                        break;

                    case 6:
                        red = 1; green = 1; blue = 1;
                        break;
                }
                glColor4f(red,green,blue,opacity);
                glRecti(j,h-i-1,j+1,h-i);
            }
        }
    }

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
}

void
Canvas::drawGhost()
{
    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);

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
                glColor3f(this->Current.getRed(),this->Current.getGreen(),this->Current.getBlue());
                glRecti(j,h-i-1,j+1,h-i);
            }
        }
    }

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
}

void
Canvas::drawStock()
{
    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);

    int* tmp;
    int h = getStock().getHeight();
    for(int i=0; i<4; i++)
    {
        tmp = getStock().DevelopFloor(i);
        for(int j=0; j<10; j++)
        {
            if(tmp[j] == 1)
            {
                glColor3f(this->Stock.getRed(), this->Stock.getGreen(), this->Stock.getBlue());
                glRecti(j+12,h-i-1+17,j+13,h-i+17);
            }
        }
    }

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
}

void
Canvas::drawContext()
{
    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);

    qglColor(Qt::white);
    QString level = QString("Level");
    QString levelN = QString::number(this->Tetris.getLevel());
    QString score = QString("Scores");
    QString scoreN = QString::number(this->Tetris.getScore());
    QString lines = QString("Lines");
    QString linesN = QString::number(this->Tetris.getLines());
    QString spare = QString("Spare");

    renderText(14, 37, 0, level, QFont("Arial", 12, QFont::Bold, false) );
    renderText(17, 35, 0, levelN, QFont("Arial", 12, QFont::Bold, false) );
    renderText(14, 31, 0, score, QFont("Arial", 12, QFont::Bold, false) );
    renderText(17, 29, 0, scoreN, QFont("Arial", 12, QFont::Bold, false) );
    renderText(14, 25, 0, lines, QFont("Arial", 12, QFont::Bold, false) );
    renderText(17, 23, 0, linesN, QFont("Arial", 12, QFont::Bold, false) );

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
}

void
Canvas::drawGameOver()
{
    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);

    qglColor(Qt::white);
    QString gameOver = QString("GAME OVER");
    QString game = QString("press N for a new game");
    QString exit = QString("press Escape for exit");

    renderText(10, 25, 0, gameOver, QFont("Arial", 45, QFont::Bold, false) );
    renderText(14, 19, 0, game, QFont("Arial", 20, QFont::Bold, false) );
    renderText(14, 15, 0, exit, QFont("Arial", 20, QFont::Bold, false) );
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
}

void
Canvas::drawPause()
{

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
            Down();
            break;

        case Qt::Key_P:
            Pause();
            break;

        case Qt::Key_N:
        if(this->Tetris.isOver())
        {
            NewGame();
            GameOver();
        }
        else { NewGame(); }
            break;

    }
}

void
Canvas::keyReleaseEvent(QKeyEvent * event)
{    
    if(event->key() == Qt::Key_Down)
    {
      this->Tetris.setFrequency(speedSave);
    }
}
