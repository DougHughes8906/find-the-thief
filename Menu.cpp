/*********************************************************************
** Program name: Menu.cpp
** Author:		Doug Hughes
** Date:		December 2, 2019
** Description:	Implementation file for the Menu class.
**		The class allows for the creation, storage, and use
**		of a dynamic menu. The sole member variable is a 
**		vector of strings which holds all of the current
**		options in the menu. There is both a method to
**		add a single option and another method (actually
**		same method name but overloaded) to add a list
**		(represented as vector) of options. Additionally,
**		there is a method to clear all options from the menu.
**		Lastly, there is a method to prompt the user to select
**		an option. The method will continue re-prompting the 
**		user until a valid option is selected and then will
**		return the value of the option (represented as an
**		integer).
**		* Added November 20, 2019 - the changeOption method which
**		allows individual options in the menu to be changed.
**		* Added December 2, 2019 - the deleteLast method which
**		deletes the last option in the menu. 
*********************************************************************/

#include "Menu.hpp"
#include "intValid.hpp"
#include <vector>
#include <string>
#include <iostream>

/***********************************************************************
Default constructor for a Menu object. The constructor does not take 
any action. Simply serves to initialize a Menu object. 
***********************************************************************/
Menu::Menu() {}

/***********************************************************************
Constructor with a vector of strings parameter. All options in the 
parameter are added to the menu.
***********************************************************************/

Menu::Menu(std::vector<std::string> ops)
{
	options = ops;
}

/***********************************************************************
Returns the number of options currently in the menu.
***********************************************************************/

int Menu::getNumOptions() const
{
	return options.size();
}

/***********************************************************************
Adds the value of the string parameter as an option to the menu. The 
option will be added to the end of the menu (i.e. it will now be the 
last option).
***********************************************************************/

void Menu::addOption(std::string op)
{
	options.push_back(op);
}

/***********************************************************************
Adds all strings in the vector parameter as options to the menu. The 
options are added to the end of the menu in the order of the their
index in the parameter (from lowest to highest).
***********************************************************************/

void Menu::addOption(std::vector<std::string> ops)
{
	for (std::string op : ops)
		options.push_back(op);
}

/***********************************************************************
Changes a single option in the menu with the argument passed. The 
first parameter is the option value to change (the option values start
at 1 and are the same as the menu output) and the second parameter
is the new text of the option. The method returns false and does 
nothing if the option value passed does not exist for the menu, and
returns true otherwise.
***********************************************************************/

bool Menu::changeOption(int opVal, std::string op)
{
	if (opVal < 1 || opVal > options.size())
	{
		return false;
	}
	else
	{
		options[opVal - 1] = op;
		return true;
	}	
}

/***********************************************************************
Deletes all options from the menu (i.e. after a call to this function
the size of the vector member variable options will be 0).
***********************************************************************/

void Menu::clearMenu()
{
	options.clear();
}

/***********************************************************************
Prompts the user to select an option from the menu and returns the 
number of the option selected. The numbers start at 1 and end at the 
number of options available (the number selected by the user is the 
number returned by this function, so the return value for the first 
option being selected will be 1 rather than 0). The function returns
-1 if there are no options currently in the menu (and there are no 
prompts to the user).
***********************************************************************/

int Menu::chooseOption() const
{
	// return -1 if no options in menu
	if (options.size() == 0)
		return -1;
	std::cout << "Please select one of the options below.\n"
		  << "To select an option, type the number next to the "
		  << "option and press ENTER.\n";
	int opNum = 1;
	while (opNum <= options.size())
	{
		std::cout << "(" << opNum << ") " << options[opNum - 1]
			  << "\n";
		opNum++;
	}

	return intValid(1, options.size());
}

/***********************************************************************
Deletes the last option in the menu. The method takes no parameters 
and has no return value.
***********************************************************************/

void Menu::deleteLast()
{
	options.pop_back();
}
