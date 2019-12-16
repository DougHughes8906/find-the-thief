/*********************************************************************
** Program name: Floor.cpp
** Author:		Doug Hughes
** Date:		December 10, 2019
** Description:	Implementation file for the Floor class.
**				Derived class of the Space class. The class is used 
**				in conjunction with the ThiefGame class to represent
**				empty floor spaces in the game. There is no 
**				special interaction or information associated with
**				these empty floor spaces.
*********************************************************************/

#include "Floor.hpp"
#include <iostream>
#include <string>

// intitialize the TYPE static constant
const std::string Floor::TYPE{ "Floor" };

/****************************************************************
Default constructor. 
****************************************************************/

Floor::Floor()	
{
}

/****************************************************************
Returns the TYPE string which represents the Floor type.
No parameters.
****************************************************************/

std::string Floor::getType() const
{
	return TYPE;
}

/****************************************************************
Returns the TYPE string which represents the Floor type.
No parameters. Static method so can be used without an object
instance.
****************************************************************/

std::string Floor::statType()
{
	return TYPE;
}

/****************************************************************
Prints a single character to the console representing the
Floor space. The method takes no parameters and has no return 
value.
****************************************************************/

void Floor::printSpace() const
{
	std::cout << " "; 
}

/****************************************************************
The method simply returns the Floor TYPE string as no action
occurs on a Floor space.
****************************************************************/

std::string Floor::event()
{
	return TYPE;
}

/****************************************************************
Returns information related to the Floor as a string. Given that
Floor spaces do not contain any information, the method returns
an empty string.
****************************************************************/

std::string Floor::information() 
{
	return "";	
}
