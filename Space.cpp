/*********************************************************************
** Program name: Space.cpp
** Author:		Doug Hughes
** Date:		December 10, 2019
** Description:	Implementation file for the Space class.
**				Used with the ThiefGame to represent individual 
**				spaces in the room. This is an abstract base class.
**				Each Space holds pointer to four adjacent Spaces
**				(up, down, right, and left). All adjacent spaces
**				are initially set to nullptr. If a Space is adjacent
**				to a "wall" of the room, then the pointers in the
**				direction of the wall are meant to stay as nullptr.
**				A Space has getter and setter methods for each of
**				its adjacent pointers. Every Space has a type, a
**				console print method, an event, and information that
**				it provides.
*********************************************************************/

#include "Space.hpp"
#include <string>

/****************************************************************
Default constructor. Sets the adjacent Space pointers to 
nullptr. 
****************************************************************/

Space::Space()
	: upSpace{ nullptr },
	  rightSpace{ nullptr },
	  downSpace{ nullptr },
	  leftSpace{ nullptr }
{
}

/****************************************************************
Sets the upSpace pointer. No return value. 
****************************************************************/

void Space::setUp(Space* spc)
{
	upSpace = spc;
}

/****************************************************************
Sets the rightSpace pointer. No return value. 
****************************************************************/

void Space::setRight(Space* spc)
{
	rightSpace = spc;
}

/****************************************************************
Sets the downSpace pointer. No return value. 
****************************************************************/

void Space::setDown(Space* spc)
{
	downSpace = spc;
}

/****************************************************************
Sets the leftSpace pointer. No return value. 
****************************************************************/

void Space::setLeft(Space* spc)
{
	leftSpace = spc;
}

/****************************************************************
Getter method. Returns the value of the upSpace pointer. 
****************************************************************/

Space* Space::getUp() const
{
	return upSpace;
}

/****************************************************************
Getter method. Returns the value of the rightSpace pointer. 
****************************************************************/

Space* Space::getRight() const
{
	return rightSpace;
}

/****************************************************************
Getter method. Returns the value of the downSpace pointer. 
****************************************************************/

Space* Space::getDown() const
{
	return downSpace;
}

/****************************************************************
Getter method. Returns the value of the leftSpace pointer. 
****************************************************************/

Space* Space::getLeft() const
{
	return leftSpace;
}

/****************************************************************
Virtual destructor. The class does not make use of any 
dynamically allocated memory. But a virtual destructor is 
included so the Space pointers to derived objects can
properly deallocate memory. 
****************************************************************/

Space::~Space()
{
}
