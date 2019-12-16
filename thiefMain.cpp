/*********************************************************************
** Program name: thiefMain.cpp
** Author:		Doug Hughes
** Date:		December 10, 2019
** Description:	Main file used to run Find the Thief games.
**				The program simply allows the console user to either
**				start and play Find the Thief games (in which case
**				all of the game flow / functionality is handled by
**				the ThiefGame class) or to exit the program.
*********************************************************************/

#include <iostream>
#include "ThiefGame.hpp"
#include "Menu.hpp"

int main()
{	
	// set up the menu for starting the game / exiting the program
	const std::string startGame{ "Start a game of Find the Thief" };
	const std::string exit{ "Exit the program" };

	Menu startMenu;
	startMenu.addOption(startGame);
	startMenu.addOption(exit);

	enum MenuChoice {
		START = 1,
		EXIT
	};

	MenuChoice curChoice = static_cast<MenuChoice>(startMenu.chooseOption());

	// continue to create and play find-the-thief games while the user
	// doesn't want to exit
	while (curChoice != EXIT)
	{
		ThiefGame newGame;
		newGame.runGame();
		
		std::cout << "\n";		
		curChoice = static_cast<MenuChoice>(startMenu.chooseOption());
	}
		
	return 0;
}
