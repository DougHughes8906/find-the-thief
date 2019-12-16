/*********************************************************************
** Program name: FireworksBox.cpp
** Author:		Doug Hughes
** Date:		December 10, 2019
** Description:	Implementation file for the FireworksBox class.
**				Derived class of the Space class. Used to represent
**				spaces that hold fireworks items that can be picked
**				up by the player and stored in the backpack. 
*********************************************************************/

#include "FireworksBox.hpp"
#include <iostream>
#include <string>

// intitialize the TYPE static constant which represents the
// type of the Space
const std::string FireworksBox::TYPE{ "FireworksBox" };
// initialize the ITEM static constant which repesents the type
// of item held in the Space
const std::string FireworksBox::ITEM{ "Fireworks" };

/****************************************************************
Default constructor. 
****************************************************************/

FireworksBox::FireworksBox()	
{
}

/****************************************************************
Returns the TYPE string which represents the FireworksBox type.
No parameters.
****************************************************************/

std::string FireworksBox::getType() const
{
	return TYPE;
}

/****************************************************************
Returns the TYPE string which represents the FireworksBox type.
No parameters. Static method so can be used without an object
instance.
****************************************************************/

std::string FireworksBox::statType()
{
	return TYPE;
}

/****************************************************************
Returns the ITEM string. No parameters. Static method so can be 
used without an object instance.
****************************************************************/

std::string FireworksBox::statItem()
{
	return ITEM;
}

/****************************************************************
Prints a single character to the console representing the
FireworksBox space. The method takes no parameters and has no return 
value.
****************************************************************/

void FireworksBox::printSpace() const
{
	std::cout << "F"; 
}

/****************************************************************
Prints a message to the console indicating that the player
picks up fireworks from the box. The method returns a string
holding the TYPE value.
****************************************************************/

std::string FireworksBox::event()
{
	std::cout << "\nYou open up a box on the ground and pull out"
		<< " fireworks.\n"; 
	return TYPE;
}

/****************************************************************
Returns information related to the FireworksBox as a string. 
Given that FireworksBox spaces do not contain any information, 
the method returns an empty string.
****************************************************************/

std::string FireworksBox::information() 
{
	return "";	
}
