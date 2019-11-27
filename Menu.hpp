/*********************************************************************
** Program name: Menu.hpp
** Author:		Doug Hughes
** Date:		November, 20 2019
** Description:	Header file for the Menu class.
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
*********************************************************************/

#ifndef MENU_HPP
#define MENU_HPP

#include <vector>
#include <string>

class Menu {
	private:
		// holds the options in the menu
		std::vector<std::string> options;
	public:
		// default constructor
		Menu();

		// one parameter constructor. Takes in a vector of 
		// strings to include as menu options
		Menu(std::vector<std::string> m_ops);

		// returns number of options
		int getNumOptions() const;

		// adds a single option to the menu
		void addOption(std::string op);

		// adds all options in the vector to the menu
		void addOption(std::vector<std::string> ops);	

		// changes a single option in the menu with the 
		// argument passed. Returns true if the option 
		// being changed existed in the menu (and therefore is 
		// changed) and false otherwise
		bool changeOption(int opVal, std::string op);

		// deletes all options from the menu
		void clearMenu();

		// prompts the user to select an option from the menu
		// and returns the numeric value of the option selected
		int chooseOption() const;	
};

#endif
