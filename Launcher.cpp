/*********************************************************************
** Program name: Launcher.cpp
** Author:		Doug Hughes
** Date:		December 10, 2019
** Description:	Implementation file for the Launcher class.
**				Derived class of the Space class. Used with the 
**				ThiefGame class to represent spaces from which the
**				player can launch in each of the four directions in
**				the room. Meant to allow the player to quickly move
**				to other parts of the room.
*********************************************************************/

#include "Launcher.hpp"
#include "Menu.hpp"
#include <iostream>
#include <string>
#include <vector>

// intitialize the TYPE static constant
const std::string Launcher::TYPE{ "Launcher" };

/****************************************************************
Default constructor. 
****************************************************************/

Launcher::Launcher()	
{
}

/****************************************************************
Returns the TYPE string which represents the Launcher type.
No parameters.
****************************************************************/

std::string Launcher::getType() const
{
	return TYPE;
}

/****************************************************************
Returns the TYPE string which represents the Launcher type.
No parameters. Static method so can be used without an object
instance.
****************************************************************/

std::string Launcher::statType()
{
	return TYPE;
}

/****************************************************************
Prints a single character to the console representing the
Stereo space. The method takes no parameters and has no return 
value.
****************************************************************/

void Launcher::printSpace() const
{
	std::cout << "L"; 
}

/****************************************************************
Simply returns the type of the Launcher to indicate that the 
player perform a launch on this space. The method has a string
return value and no parameters.
****************************************************************/

std::string Launcher::event()
{
	return TYPE;	
}

/****************************************************************
Allows the player to choose a launch direction. The method
has no parameters. The int return value represents the 
direction chosen. Possible return values:
1 - the player has chosen not to launch
2 - launch up
3 - launch right
4 - launch down
5 - launch left
****************************************************************/

int Launcher::chooseDirection() const 
{
	static const std::vector<std::string> dirChoices{
		"No launch",
		"Launch up",
		"Launch right",
		"Launch down",
		"Launch left"
	};
	static const Menu directionMenu(dirChoices);

	std::cout << "\nYou are standing on the launcher. Please "
		<< "choose the direction for your launch.\n";

	return directionMenu.chooseOption();	
}

/****************************************************************
Returns information related to the Launcher as a string. Given that
Launcher spaces do not contain any information, the method returns
an empty string.
****************************************************************/

std::string Launcher::information() 
{
	return "";	
}

