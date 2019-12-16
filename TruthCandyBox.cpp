/*********************************************************************
** Program name: TruthCandyBox.cpp
** Author:		Doug Hughes
** Date:		December 10, 2019
** Description:	Implementation file for the TruthCandyBox class.
**				Derived class of the Space class. Used with the
**				ThiefGame class to represent spaces from which the
**				player can pick up Truth Candy Bar items. The Truth
**				Candy Bars are meant to be items the player can use
**				to determine if a single guest is the thief.
*********************************************************************/

#include "TruthCandyBox.hpp"
#include <iostream>
#include <string>

// intitialize the TYPE static constant which represents the
// type of this Space
const std::string TruthCandyBox::TYPE{ "TruthCandyBox" };
// initialize the ITEM static constant which represents the
// type of item held in this Space
const std::string TruthCandyBox::ITEM{ "Truth Candy Bar" };

/****************************************************************
Default constructor. 
****************************************************************/

TruthCandyBox::TruthCandyBox()	
{
}

/****************************************************************
Returns the TYPE string which represents the TruthCandyBox type.
No parameters.
****************************************************************/

std::string TruthCandyBox::getType() const
{
	return TYPE;
}

/****************************************************************
Returns the TYPE string which represents the TruthCandyBox type.
No parameters. Static method so can be used without an object
instance.
****************************************************************/

std::string TruthCandyBox::statType()
{
	return TYPE;
}

/****************************************************************
Returns the ITEM string. No parameters. Static method so can be 
used without an object instance.
****************************************************************/

std::string TruthCandyBox::statItem()
{
	return ITEM;
}

/****************************************************************
Prints a single character to the console representing the
TruthCandyBox space. The method takes no parameters and has no return 
value.
****************************************************************/

void TruthCandyBox::printSpace() const
{
	std::cout << "T"; 
}

/****************************************************************
Prints a message to the console indicating that the player
picks up a truth candy bar from the box. The method returns a string
holding the TYPE value.
****************************************************************/

std::string TruthCandyBox::event()
{
	std::cout << "\nYou open up a box on the ground and pull out"
		<< " a Truth Candy Bar.\nYou read the label on the back:\n"
		<< "WARNING: This candy bar will cause the consumer to be "
		<< "completely honest for up\nto an hour. Politicians "
		<< "should only consume in private settings.\n";
	return TYPE;
}

/****************************************************************
Returns information related to the TruthCandyBox as a string. 
Given that TruthCandyBox spaces do not contain any information, 
the method returns an empty string.
****************************************************************/

std::string TruthCandyBox::information() 
{
	return "";	
}
