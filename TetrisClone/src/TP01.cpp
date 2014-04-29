#include "TP01.h"


GLfloat angle1 = 30.0f;
GLfloat angle2 = 20.0f;

const GLfloat g_AngleSpeed = 10.0f;


#include <iostream>

using namespace std;


GLfloat g_TabVertices[]=
{
	0,0,0,
	0,0,10,
	0,0,0,
	0,10,0,
	0,0,0,
	10,0,0
};

GLfloat g_TabColors[]=
{
	1,0,0,
	1,0,0,
	0,1,0,
	0,1,0,
	0,0,1,
	0,0,1
};


TP01::TP01()
{
	setWindowTitle(trUtf8("IN55-TP01"));
}


bool
TP01::initializeObjects()
{
	// Fond gris
	glClearColor( 0.2f, 0.2f, 0.2f, 1.0f );
	glEnable( GL_DEPTH_TEST );

	// Chargement des shaders
	createShader( "Shaders/color" );

	return true;
}


void
TP01::render()
{
	// Initialisation de la caméra
	lookAt( 0, 5, 30, 0, 0, 0 );


	// Rendu des objets
	pushMatrix();
		rotate( angle1, 0, 1, 0 );
		rotate( angle2, 1, 0, 0 );

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
		glDrawArrays( GL_LINES, 0, 6 );
		glDisableVertexAttribArray( var1 );
		glDisableVertexAttribArray( var2 );
	popMatrix();
}


void
TP01::keyPressEvent( QKeyEvent* event )
{
	switch( event->key())
	{
		case Qt::Key_Escape:
			close();
			break;

		case Qt::Key_Left:
			angle1 -= g_AngleSpeed;
			break;

		case Qt::Key_Right:
			angle1 += g_AngleSpeed;
			break;

		case Qt::Key_Up:
			angle2 -= g_AngleSpeed;
			break;

		case Qt::Key_Down:
			angle2 += g_AngleSpeed;
			break;

		case Qt::Key_R:
			angle1 = angle2 = 0.0f;
			break;
	}
}
