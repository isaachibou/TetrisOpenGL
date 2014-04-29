#ifndef TP01_h
#define TP01_h


#include "GlWindow.h"


class TP01 : public GlWindow
{
	public:
		TP01();

		/*!
		*\brief Initialization des objets.
		*/
		bool initializeObjects();

		/*!
		*\brief Rendu de la sc�ne.
		*/
		void render();

		void keyPressEvent(QKeyEvent *);
};


#endif
