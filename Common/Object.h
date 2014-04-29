#ifndef Object_h
#define Object_h


#include "AbstractFramework.h"
#include "Shapes/Shape.h"


class Object
{
	public:
		static void setFramework( AbstractFramework* );

	public:
		void draw();

	protected:
		virtual void drawShape() = 0;


	protected:
		static AbstractFramework* m_Framework;
};


#endif
