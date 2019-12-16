/*********************************************************************
** Program name: Clue.cpp
** Author:		Doug Hughes
** Date:		December 10, 2019
** Description:	Implementation file for the Clue class.
**				Derived class of the Space class. The class is used
**				to represent Spaces that hold clues regarding the
**				identity of the thief (in the context of the 
**				ThiefGame class). A clue has a text member variable
**				that holds the content of the clue.
*********************************************************************/

#include "Clue.hpp"
#include <string>
#include <iostream>

// intitialize the TYPE static constant
const std::string Clue::TYPE{ "Clue" };

/****************************************************************
Constructor. Sets the clue text based on the single parameter.
****************************************************************/

Clue::Clue(std::string clueStr)
	: m_text{ clueStr }	
{
}

/****************************************************************
Returns the TYPE string which represents the Clue type.
No parameters.
****************************************************************/

std::string Clue::getType() const
{
	return TYPE;
}

/****************************************************************
Returns the TYPE string which represents the Clue type.
No parameters. Static method so can be used without an object
instance.
****************************************************************/

std::string Clue::statType()
{
	return TYPE;
}

/****************************************************************
Prints a single character to the console representing the
Clue space. The method takes no parameters and has no return 
value.
****************************************************************/

void Clue::printSpace() const
{
	std::cout << "C"; 
}

/****************************************************************
Prints the clue text to the console. The method takes no 
parameters and returns as a string the Clue TYPE.
****************************************************************/

std::string Clue::event()
{
	std::cout << "You pick up a slip of paper that contains "
		<< "the following note...\n"
		<< m_text << "\n";
	return TYPE;
}

/****************************************************************
Returns information related to the Clue as a string.
The information includes the text of the clue. 
****************************************************************/

std::string Clue::information() 
{
	std::string infoStr = "Clue: " + m_text;
	return infoStr;	
}
