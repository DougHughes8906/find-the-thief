

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
		
		curChoice = static_cast<MenuChoice>(startMenu.chooseOption());
	}
		
	return 0;
}
