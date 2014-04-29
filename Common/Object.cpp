#include "Object.h"


AbstractFramework* Object::m_Framework = NULL;


void
Object::setFramework( AbstractFramework* fw )
{
	m_Framework = fw;
}


void
Object::draw()
{
	m_Framework->computeAncillaryMatrices();
	drawShape();
}
