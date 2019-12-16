/*********************************************************************
** Program name: ThiefGame.cpp
** Author:		Doug Hughes
** Date:		December 10, 2019
** Description:	Implementation file for the ThiefGame class.
**				The class is used to play the console-based Find the
**				Thief game. The game involves the player losing their
**				wallet at a party and having to guess the identity of 
**				the thief before the party ends. The player can meet
**				people at the party, pick up clues, interact with
**				objects in the room, and use various items to help
**				identify the thief. The party room is represented 
**				as a matrix of Spaces over which the player can 
**				traverse and the game takes place over a series of 
**				turns. Each turn represents one minute of game time
**				and the player can move to any adjacent space in that
**				turn. The game is a race against the clock, as the 
**				player needs to guess the identity of the thief 
**				before the party is over (the player is informed
**				of the game end time at the beginning of the game).
**				Winning the game represents the player calling the
**				police and guessing the identity of the thief 
**				correctly. But once the player calls the police, they
**				only get a single guess.
*********************************************************************/

#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <ctime>
#include <cstdlib>
#include "ThiefGame.hpp"
#include "Backpack.hpp"
#include "Space.hpp"
#include "Floor.hpp"
#include "Person.hpp"
#include "Clue.hpp"
#include "Stereo.hpp"
#include "FireworksBox.hpp"
#include "TruthCandyBox.hpp"
#include "Launcher.hpp"
#include "intValid.hpp"

// initially indicate that the random seed for the program is 
// not set
bool ThiefGame::seedSet = false;

/*****************************************************************
Default constructor. Sets up the inital state for the game.
The room for the game is set up as a matrix of Space objects.
Guests, clues, and interactive objects are placed in the room.
Both the identity of the thief and the starting location of 
the player are also set. 
*****************************************************************/

ThiefGame::ThiefGame() 
	: m_backpack{ },
	  m_gameFinished{ false },
	  m_hour{ "11" },
	  m_min{ "00" },
	  m_isAM{ false },
	  m_endHour{ "11" },
	  m_endMin{ "30" },
	  m_endAM{ false }
{
	// set the random seed if it has not already been set in
	// the program
	if (!seedSet)
	{
		srand(time(NULL));
		seedSet = true;
	}

	// set up an empty room represented by Space pointers to
	// Floor objects
	setEmptyRoom();
	// create and place the guests in the room (along with the
	// thief)
	createGuests(NUM_GUESTS);	
	placeGuests();	
	// set all of the remaining Spaces for the room
	setClues();	
	setStereo();
	setLauncher();	
	setFireworks();	
	setTruthCandy();	
	// place the player randomly in the room on an empty floor
	// space
	placePlayer();	
}

/*****************************************************************
Helper method to the constructor. Provides the intital set up for
the room by creating a matrix of Space pointers to Floor objects.
No parameters and no return value.
*****************************************************************/

void ThiefGame::setEmptyRoom()
{
	// set up every row in the room, setting the left/right
	// pointers along the way
	for (int i = 0; i < NUM_ROWS; i++)
	{
		m_rowStart[i] = new Floor();
		Space* curSpace = m_rowStart[i];
		for (int j = 0; j < NUM_COLS - 1; j++)
		{
			Space* rightFloor = new Floor();
			curSpace->setRight(rightFloor);
			rightFloor->setLeft(curSpace);
			curSpace = rightFloor;
		}
	}

	// set the up/down pointers for every floor space
	for (int i = 0; i < NUM_ROWS - 1; i++)
	{
		Space* topRow = m_rowStart[i];
		Space* botRow = m_rowStart[i + 1];
		for (int j = 0; j < NUM_COLS; j++)
		{
			topRow->setDown(botRow);
			botRow->setUp(topRow);
			topRow = topRow->getRight();
			botRow = botRow->getRight();
		}
	}
}

/*****************************************************************
Helper method to the constructor. Creates all of the party guests
for the party. Takes as a parameter the number of guests to add
to the room. Returns true if the number of guests are created 
and false otherwise. Only the maximum number of guests will be
created if the number of guests parameter is too large (i.e. there 
are not enough names available to give the guests). The method 
randomly chooses identities of the guests. The method is 
currently designed to allow for up to 20 guests.
*****************************************************************/

bool ThiefGame::createGuests(int numGuests)
{
	std::vector<std::pair<std::string, bool>> possibleGuests{
		std::make_pair(std::string("Bill"), true),
		std::make_pair(std::string("Charles"), true),
		std::make_pair(std::string("Ethan"), true),
		std::make_pair(std::string("Sebastian"), true),
		std::make_pair(std::string("Xavier"), true),
		std::make_pair(std::string("Zachary"), true),
		std::make_pair(std::string("Reuben"), true),
		std::make_pair(std::string("Wesley"), true),
		std::make_pair(std::string("Maximus"), true),
		std::make_pair(std::string("Alec"), true),
		std::make_pair(std::string("Ophelia"), false),
		std::make_pair(std::string("Violet"), false), 
		std::make_pair(std::string("Isabella"), false),
		std::make_pair(std::string("Penelope"), false),
		std::make_pair(std::string("Nora"), false),
		std::make_pair(std::string("Hannah"), false),
		std::make_pair(std::string("Lola"), false),
		std::make_pair(std::string("Georgia"), false),
		std::make_pair(std::string("Jasmine"), false),
		std::make_pair(std::string("Diana"), false)
	};	

	while (numGuests > 0 && possibleGuests.size() > 0)
	{
		int guestIndex = getRand(0, possibleGuests.size() - 1);	
		auto guestInfo = possibleGuests[guestIndex];
		Space* nextGuest = new Person(guestInfo.first, guestInfo.second);
		m_guestList.push_back(nextGuest);
		numGuests--;

		// remove the added guest from the remaining possible guests to 
		// add 
		std::swap(possibleGuests[guestIndex], 
			possibleGuests[possibleGuests.size() - 1]);	
		possibleGuests.pop_back();	
	}

	// indicate if the total # of requested guests could not be 
	// added
	if (numGuests > 0)
	{
		return false;
	}

	return true;
}

/*****************************************************************
Helper method to the constructor. The method places the party
guests in the room. The method takes no parameters and has no
return value. Also determines which guest will be the thief.
*****************************************************************/

void ThiefGame::placeGuests()
{
	// determine the index of the thief
	int thiefInd = getRand(0, m_guestList.size() - 1);
	for (int i = 0; i < m_guestList.size(); i++)
	{		
		// place the guest in the randomly selected location
		bool isThief = (i == thiefInd);
		if (isThief)
		{
			m_thief = m_guestList[i];
		}
		place(m_guestList[i], isThief);	
	}
	// rearrange m_guestList so the thief pointer is stored at
	// the first index
	std::swap(m_guestList[thiefInd], m_guestList[0]); 
}

/*****************************************************************
Returns a random int between two values (inclusive). Takes no 
parameters. The first parameter is the minimum of the range
and the second parameter is the max. However, if the min 
parameter is greater than the max parameter, then the values
are swapped (so a random value is still returned).
*****************************************************************/

int ThiefGame::getRand(int min, int max) const
{
	if (min > max)
	{
		std::swap(min, max);
	}
	
	return (rand() % (max - min + 1)) + min;
}

/*****************************************************************
Places a Space object on a random spot in the room matrix. If the
chosen spot is not empty Floor space, then the Space object is placed 
on the next empty Floor space. The first parameter is a pointer
to the Space object, the second parameter is the row in which 
the object will be placed, the third parameter is the column 
in which the object will be placed, and the last parameter 
holds true if the space is that of the thief and false otherwise.
*****************************************************************/

void ThiefGame::place(Space* newSpace, bool isThief)
{
	Space* randFloor = getRandFloor(isThief);
	
	replace(randFloor, newSpace);	
}

/*****************************************************************
Replaces one space with another space. The first parameter is 
a pointer to the Space that will be replaced and the second
parameter is a pointer to the Space that will be the 
replacement. No return value.
*****************************************************************/

void ThiefGame::replace(Space* oldSpace, Space* newSpace)
{
	// set all of the new pointers between the new space
	// and surrounding spaces of the old space
	Space* adjacentSpace = oldSpace->getUp();
	newSpace->setUp(adjacentSpace);
	if (adjacentSpace != nullptr)
	{
		adjacentSpace->setDown(newSpace);
	}

	adjacentSpace = oldSpace->getRight();
	newSpace->setRight(adjacentSpace);
	if (adjacentSpace != nullptr)
	{
		adjacentSpace->setLeft(newSpace);
	}

	adjacentSpace = oldSpace->getDown();
	newSpace->setDown(adjacentSpace);
	if (adjacentSpace != nullptr)
	{
		adjacentSpace->setUp(newSpace);
	}

	adjacentSpace = oldSpace->getLeft();
	newSpace->setLeft(adjacentSpace);
	if (adjacentSpace != nullptr)
	{
		adjacentSpace->setRight(newSpace);
	}

	// need to check if the old space was the start of a 
	// row, in which case the rowStart needs to be modified
	bool foundRStart = false;
	int i = 0;
	while (!foundRStart && i < NUM_ROWS)
	{
		if (m_rowStart[i] == oldSpace)
		{
			m_rowStart[i] = newSpace;
			foundRStart = true;
		}
		i++;
	}

	// free memory associated with the old space
	delete oldSpace;
}

/*****************************************************************
Helper method to the constructor.
Sets the clues in the room. The method takes no parameters and
has no return value. The locations of the clues are chosen 
randomly, but must be on an empty floor space.
*****************************************************************/

void ThiefGame::setClues()
{
	// set clue indicating the gender of the thief
	std::string gendClueStr{ "The thief is " };
	Person* thiefPtr = dynamic_cast<Person*>(m_thief);	
	if (thiefPtr->isMale())
	{
		gendClueStr += "male.";
	}
	else
	{
		gendClueStr += "female.";
	}	
	Space* genderClue = new Clue(gendClueStr);
	place(genderClue, false);

	// set clue indicating a letter in the name of the thief
	std::string nameClueStr{ "The thief's name contains the letter " };	
	std::string thiefName = thiefPtr->getName();
	int letterInd = getRand(0, thiefName.length() - 1);

	nameClueStr += "'"; 
	nameClueStr += tolower(thiefName[letterInd]); 
	nameClueStr += "'.";

	Space* nameClue = new Clue(nameClueStr);
	place(nameClue, false); 		
}

/*****************************************************************
Helper method to the constructor.
Sets one stereo in the room. The method takes no parameters and
has no return value. The location for the stereo is chosen
randomly.
*****************************************************************/

void ThiefGame::setStereo()
{
	Space* partyStereo = new Stereo();
	place(partyStereo, false);
}

/*****************************************************************
Helper method to the constructor.
Sets one launcher in the room. The method takes no parameters and
has no return value. The location for the launcher is chosen
randomly.
*****************************************************************/

void ThiefGame::setLauncher()
{
	Space* partyLauncher = new Launcher();
	place(partyLauncher, false);
}


/*****************************************************************
Helper method to the constructor.
Sets the fireworks box in the room. The method takes no
parameters and has no return value. The location for the fireworks
box is chosen randomly.
*****************************************************************/

void ThiefGame::setFireworks()
{
	Space* fworksBox = new FireworksBox();
	place(fworksBox, false);
}

/*****************************************************************
Helper method to the constructor.
Sets the truth candy box in the room. The method takes no 
parameters and has no return value. The location for the truth
candy box is chosen randomly.
*****************************************************************/

void ThiefGame::setTruthCandy()
{
	Space* tCandyBox = new TruthCandyBox();
	place(tCandyBox, false);
}

/*****************************************************************
Method that sets the space on which the player is placed. The 
space is chosen at random but must be an empty floor space. The
method takes no parameters and has no return value.
*****************************************************************/

void ThiefGame::placePlayer()
{
	m_playerSpace = getRandFloor(false);
}

/*****************************************************************
Finds a random floor space and returns a pointer to that space. 
The method takes a bool parameter. If the parameter is set to 
true that indicates this is the floor space on which the thief
will be placed. In this case the method also sets the row and 
column of the thief.
*****************************************************************/

Space* ThiefGame::getRandFloor(bool isThief) 
{
	int placeRow = getRand(0, NUM_ROWS - 1);
	int placeCol = getRand(0, NUM_COLS - 1);	

	Space* curSpace = m_rowStart[placeRow];
	for (int i = 1; i <= placeCol; i++)
	{
		curSpace = curSpace->getRight();
	}
	
	int curRow = placeRow;
	int curCol = placeCol;
	
	// move to the next space while a blank floor space hasn't yet 
	// been found
	while (curSpace->getType() != Floor::statType())
	{
		if (curCol == NUM_COLS - 1)
		{
			if (curRow == NUM_ROWS - 1)
			{
				curSpace = m_rowStart[0];
				curRow = 0;
				curCol = 0; 		
			}
			else
			{
				curRow++;
				curCol = 0;
				curSpace = m_rowStart[curRow];
			}
		}
		else
		{
			curSpace = curSpace->getRight();
			curCol++;
		}
	}

	if (isThief)
	{	
		m_thiefRow = curRow;
		m_thiefCol = curCol;
	}
	return curSpace;
}

/*****************************************************************
Runs a full find the thief game. If the game for this instance
has already been completed, the method does nothing and returns
false. Otherwise, the method completes a single game and returns
true.
*****************************************************************/

bool ThiefGame::runGame() 
{
	if (m_gameFinished)
	{
		return false;
	}

	// game information strings
	const std::string welcomeMsg{ "\nWelcome to the Find the "
		"Thief Game!\n" };
	const std::string gameInfo{ "\nYou are at a party and realize"
		" that someone has stolen your wallet.\nYou need to figure"
		" out who the thief is and call the police before\nthe party"
		" is over. You need to guess the identity of the thief "
		"correctly\nthe first time because the thief will leave if "
		"the police arrive to\nquestion someone else. The party "
		"ends at 11:30PM, so you must\ncall the police before the "
		"party is over. Meet the guests of\nthe party, pick up clues,"
		" and use items in the room to help find\nthe thief.\n"};

	const std::string mapInfo{ "\nFor each turn of the game you"
		" will be shown a map of the room. The symbols on\nthe map "
		"have the following meanings:\n"
	};

	const std::string starInfo{ "* - your location in the room" };
	const std::string PInfo{ "P - a person that you have not yet"
		" met"};
	const std::string FInfo{ "F - a box of fireworks. You can move to "
		"this box to pick up fireworks" };
	const std::string CInfo{ "C - a clue. This will give you a hint "
		"regarding the identity of the thief" };
	const std::string TInfo { "T - a box of truth candy bars. You can "
		"move to this box to pick up a truth\ncandy bar" };
	const std::string SInfo { "S - a stereo. You can play songs on the"
		" stereo that have different effects on\nthe party" };
	const std::string LInfo{ "L - a launcher. Can be used to quickly "
		"launch yourself to other parts of the\nroom" };	
	const std::string lCaseInfo{ "a, b, c, ... - lower case letters"
		" represent the first letters of the names of\npeople that"
		" you have already met" };

	const std::string noteInfo{ "\nAll of this information is also"
		" written in your notepad for reference.\n" };	

	const std::vector<std::string> symbolsInfo{ starInfo, PInfo,
		FInfo, CInfo, TInfo, SInfo, LInfo, lCaseInfo }; 

	// present player with information about the game
	std::cout << welcomeMsg
			  << gameInfo;

	std::cout << "\nEnter '1' to continue:\n";
	intValid(1, 1);

	std::cout << mapInfo;
	for (std::string info : symbolsInfo)
	{
		std::cout << info << "\n";
		m_backpack.addNote(info);
	}
	std::cout << noteInfo;

	std::cout << "\nEnter '1' to start the game:\n";
	intValid(1, 1);

	const std::string moveChoice{ "Make move for the turn" };
	const std::string backpackChoice{ "Open your backpack" };
	Menu mainMenu;
	mainMenu.addOption(moveChoice);
	mainMenu.addOption(backpackChoice);

	enum MainChoice {
		MOVE = 1,
		BACKPACK
	};

	// represents the possible return values of opening the
	// backpack
	enum BPResult {
		WRONG_GUESS = 0,
		NO_ACTION,
		CORRECT_GUESS,
		FIREWORKS,
		TRUTH_CANDY			
	};
	
	while(!m_gameFinished)
	{
		std::cout << "\nCurrent time: ";
		printTime();
		printRoom();

		// interact with the current space. Nothing happens if on
		// a Floor space
		interact();	

		// create move menu for the turn based on where the player
		// can currently move
		Menu moveMenu;
		std::vector<Space*> moveChoices;
		setMoveMenu(moveMenu, moveChoices);

		std::cout << "\n";		
		MainChoice playerChoice = 
			static_cast<MainChoice>(mainMenu.chooseOption());

		while (playerChoice != MOVE && !m_gameFinished)
		{
			// player opens backpack, return value indicates the game state
			BPResult gameState = 
				static_cast<BPResult>(m_backpack.open(m_playerSpace));

			switch (gameState) {
				case WRONG_GUESS:
				{
					gameLoss();
					break;
				}
				case CORRECT_GUESS:
				{
					gameWin();
					break;
				}
				case FIREWORKS:
				{
					useFireworks();
					break;
				}
				case TRUTH_CANDY:
				{
					useTruthCandy();
					break;
				}
				default:
				{
					break;
				}
			}			
	
			if (!m_gameFinished)	
			{
				std::cout << "\n";
				playerChoice = 
					static_cast<MainChoice>(mainMenu.chooseOption());
			}
		}	

		if (!m_gameFinished)
		{
			// perform movement
			movePlayer(moveMenu, moveChoices);	
			// increment the time by a minute
			addMin();
		}

		// check to see if this is the end time, if so, force the player
		// to call the police now
		if (!m_gameFinished && m_hour == m_endHour && m_min == m_endMin
			&& m_isAM == m_endAM) 
		{
			std::cout << "\nThe party is ending, so you call the police "
				<< "at the last minute!\n";
			int endVal = m_backpack.callPolice();
			if (endVal == 0)
			{
				std::cout << "\nYou decided against calling the police"
					<< " as you have no clue as to who stole your wallet!\n"
					<< "The thief leaves along with the rest of the guests "
					<< "as the party ends.\n";
			}
			else if (endVal == -1)
			{
				gameLoss();
			}
			else
			{
				gameWin();
			}	
		}
	}
	
	return true;
}

/*****************************************************************
Prints the current game time to the console. The method takes
no paramters and has no return value.
*****************************************************************/

void ThiefGame::printTime() const
{	
	std::cout << m_hour << ":" << m_min;
	if (m_isAM)
	{
		std::cout << "AM\n";
	}
	else
	{
		std::cout << "PM\n";
	}
}


/*****************************************************************
Prints a given time to the console. Takes three
parameters. The first parameter represents the hour as a string, 
the second parameter represents the minute as a string and the 
last parameter is a bool value that holds true if the time is in 
the AM and false if the time is in the PM. The method returns as
a string the same information that is printed to the console.
*****************************************************************/

std::string ThiefGame::printTime(std::string hour, std::string min, 
	bool isAM) const
{
	std::string timeInfo = hour + ":" + min;	
	if (isAM)
	{
		timeInfo += "AM";	
	}
	else
	{
		timeInfo += "PM";	
	}
	std::cout << timeInfo << "\n";
	return timeInfo;
}

/*****************************************************************
Adds a minute to the current game time. The method takes no 
parameters and has no return value.
*****************************************************************/

void ThiefGame::addMin() 
{
	addMin(m_hour, m_min, m_isAM);
}

/*****************************************************************
Adds a minute to a given time for by modifying the 
variables representing the time. The method has no return value
and has three reference parameters (representing the hour, 
the minute, and a bool value that is set to true if the time is
currently in the AM).
*****************************************************************/

void ThiefGame::addMin(std::string &hour, std::string &min,
	bool &isAM) 
{
	// special handling if the time is about to enter new hour
	if(min == "59")
	{
		if (hour == "12")
		{
			hour = "01";
		}
		else if (hour == "11")
		{
			hour = "12";
			isAM = !isAM;
		}
		else
		{
			int hourInt = std::stoi(hour);
			hourInt++;
			std::string newHourStr = "";
			if (hourInt < 10)
			{
				newHourStr += "0";
			}
			newHourStr += std::to_string(hourInt);
			hour = newHourStr;
		}
		min = "00";
	}

	// normal case where minute is added, but it is not a new hour
	else
	{
		int minInt = std::stoi(min);
		minInt++;
		std::string newMinStr = "";
		if (minInt < 10)
		{
			newMinStr += "0";
		}
		newMinStr += std::to_string(minInt);	
		min = newMinStr;	
	}		
}

/*****************************************************************
Method that builds the move menu for the player based upon the
players current location. The method takes as reference parameters
the Menu that will be built and a vector of space pointers in 
which the possible move choices will be stored.
*****************************************************************/

void ThiefGame::setMoveMenu(Menu &moveMenu, 
	std::vector<Space*> &moveChoices) const
{
	if (m_playerSpace->getUp() != nullptr)
	{
		moveMenu.addOption("Move up");
		moveChoices.push_back(m_playerSpace->getUp());
	}
	if (m_playerSpace->getRight() != nullptr)
	{
		moveMenu.addOption("Move right");
		moveChoices.push_back(m_playerSpace->getRight());
	}
	if (m_playerSpace->getDown() != nullptr)
	{
		moveMenu.addOption("Move down");
		moveChoices.push_back(m_playerSpace->getDown());
	}
	if (m_playerSpace->getLeft() != nullptr)
	{
		moveMenu.addOption("Move left");
		moveChoices.push_back(m_playerSpace->getLeft());
	}
}

/*****************************************************************
Prompts the player with a menu to move and performs the movement
based on the player's choice. The method takes as a parameter the
move menu with which to prompt the player as a reference and as
a second parameter a vector of Spaces representing the possible
Spaces the player can move (in the same order as presented in 
the menu). The method has no return value.
*****************************************************************/

void ThiefGame::movePlayer(const Menu &moveMenu, 
	const std::vector<Space*> &moveChoices)
{
	std::cout << "\nChoose which direction to move.\n";
	int choice = moveMenu.chooseOption();
	// have to subtract one from the choice because the choice
	// return values start at 1 rather than 0
	m_playerSpace = moveChoices[choice - 1];
}

/*****************************************************************
Prints the current state of the room as a grid. The method prints
a '*' at the location of the player rather than the print value
of the underlying space. The method takes no parameters and has 
no return value.
*****************************************************************/

void ThiefGame::printRoom() const
{
	// string for the top and bottom walls of the room
	static const std::string HORIZ_WALL(NUM_COLS + 2, '-'); 

	std::cout << "\n" << HORIZ_WALL << "\n";
	for (int i = 0; i < NUM_ROWS; i++)
	{
		std::cout << "|";

		Space* curSpace = m_rowStart[i]; 
		for (int j = 0; j < NUM_COLS; j++)
		{
			if (curSpace == m_playerSpace)
			{
				std::cout << "*";
			}
			else
			{
				curSpace->printSpace();
			}
			curSpace = curSpace->getRight();
		}		
		
		std::cout << "|\n";
	}
	std::cout << HORIZ_WALL << "\n";
}

/*****************************************************************
The player interacts with the current Space on which the player
is located. Any event associated with the space is performed and
any information related to the Space is received. 
*****************************************************************/

void ThiefGame::interact()
{
	performEvent();
	getInfo();
}

/*****************************************************************
An event is performed based on the space on which the player is
currently standing. The method takes no parameters and has no
return value. 
*****************************************************************/

void ThiefGame::performEvent()
{	
	std::string eventType = m_playerSpace->event();
	// make sure backpack has info on who thief is (to check when police
	// are called if player guess is correct)
	if (m_playerSpace == m_thief)
	{
		Person* thiefPtr = dynamic_cast<Person*>(m_thief);
		m_backpack.setThief(thiefPtr->getName());
	}

	if (eventType == Person::statType())
	{
		Person* guestPtr = dynamic_cast<Person*>(m_playerSpace);
		m_backpack.addContact(guestPtr->getName());
	}

	else if (eventType == Stereo::statType())
	{
		static constexpr int STEREO_OFF{ 0 };
		static constexpr int BAD_MUSIC{ 1 };
		static constexpr int GOOD_MUSIC{ 2 };
		// try to play the stereo
		Stereo* sterPtr = dynamic_cast<Stereo*>(m_playerSpace);
		int stereoVal = sterPtr->playStereo();
		if (stereoVal == BAD_MUSIC)
		{	
			// about half of the party leaves, the exact guests are chosen
			// at random but cannot include the thief
			randGuestsLeave();
			std::cout << "Enter '1' to continue:\n";
			intValid(1, 1);
			std::cout << "\nNew map of the room following the exodus:\n";
			printRoom();
		}
		else if (stereoVal == GOOD_MUSIC)
		{
			// extend the game time by 15 minutes
			static constexpr int addedMins{ 15 };
			std::cout << "The excitement of the guests causes the "
				<< "party to last longer!\n";
			extendGame(addedMins);
		}
	}

	else if (eventType == Launcher::statType())
	{
		Launcher* launchPtr = dynamic_cast<Launcher*>(m_playerSpace);
		// use the launcher
		useLauncher(launchPtr->chooseDirection());
	}

	else if (eventType == FireworksBox::statType())
	{
		getItem(FireworksBox::statItem());
	}

	else if (eventType == TruthCandyBox::statType())
	{
		getItem(TruthCandyBox::statItem());
	} 
}

/*****************************************************************
Information is received from the player's current space and 
added to the player's notepad (within the backpack). The method
takes no parameters and has no return value.
*****************************************************************/

void ThiefGame::getInfo()
{
	std::string info = m_playerSpace->information();
	m_backpack.addNote(info);

	// if the info received is from a clue, remove the clue from
	// the ground after taking a note
	if (m_playerSpace->getType() == Clue::statType())
	{	
		Space* emptyFloor = new Floor();
		replace(m_playerSpace, emptyFloor);
		m_playerSpace = emptyFloor;
	}	
}

/*****************************************************************
Deletes about half of the guests from the party, simulating 
these guests leaving the party. The guests are chosen at random
but cannot include the thief.
The method takes no parameters and has no return value.
*****************************************************************/

void ThiefGame::randGuestsLeave()
{
	int numGuestsLeave = m_guestList.size() / 2;

	std::cout << "\n";
	// the thief is held at index 0, so only choose indices from
	// 1 and above
	for (int i = 0; i < numGuestsLeave; i++)
	{
		int randInd = getRand(1, m_guestList.size() - 1);
		Person* guest = dynamic_cast<Person*>(m_guestList[randInd]);
		std::string leaveMsg = "";
		if (guest->isMet())
		{
			leaveMsg += guest->getName();
		}
		else
		{
			leaveMsg += "A guest you did not meet";
		}
		leaveMsg += " has left the party.";
		
		std::cout << leaveMsg << "\n";
		m_backpack.addNote(leaveMsg);

		Space* emptyFloor = new Floor();
		replace(m_guestList[randInd], emptyFloor);
		std::swap(m_guestList[randInd], m_guestList[m_guestList.size() - 1]);
		m_guestList.pop_back();
	} 
}

/*****************************************************************
Method tries to add an item to the player's backpack and prints
a message to the console accordingly. If the item is taken then
the player's current space is changed to a Floor space (to 
indicate that the item has been taken). If the player's backpack
is currently full, then a message is printed to the console
indicating this. The method takes as a parameter the type of
item being added and has no return value.
*****************************************************************/

void ThiefGame::getItem(std::string itemType)
{
	// the backpack add method will print the relevant message
	// to the console
	bool added = m_backpack.add(itemType);

	if (added)
	{
		Space* emptyFloor = new Floor();
		replace(m_playerSpace, emptyFloor);
		m_playerSpace = emptyFloor;
	}
}

/*****************************************************************
Ends the game in a loss. The method indicates to the player
that the real thief escaped and the identity of the thief. The
method has no parameters and no return value.
*****************************************************************/

void ThiefGame::gameLoss()
{
	Person* thiefPtr = dynamic_cast<Person*>(m_thief);
	std::cout << "\nThe real thief was " << thiefPtr->getName()
		<< "! ";
	if (thiefPtr->isMale())
	{
		std::cout << "He ";
	}
	else 
	{
		std::cout << "She ";
	}
	std::cout << "escapes as the police are busy talking with\nthe"
		<< " wrong person!\n";
	
	m_gameFinished = true;
}

/*****************************************************************
Ends the game with a win. The method indicates to the player
that they guessed the thief correctly. The method has no 
parameters and no return value.
*****************************************************************/

void ThiefGame::gameWin()
{
	Person* thiefPtr = dynamic_cast<Person*>(m_thief);
	std::cout << "\nThe police interrogate " << thiefPtr->getName()
		<< " and discover that ";

	if (thiefPtr->isMale())
	{
		std::cout << "he ";
	}
	else
	{
		std::cout << "she ";
	}

	std::cout << "is the thief!\nCongratulations, you correctly "
		<< "identified the thief and your wallet is returned to you!\n";

	m_gameFinished = true;
}

/*****************************************************************
Extends the end game time by a specified number of minutes. The 
method takes no parameters and has no return value.
*****************************************************************/

void ThiefGame::extendGame(int addedMins)
{	
	for (int i = 0; i < addedMins; i++)
	{
		addMin(m_endHour, m_endMin, m_endAM);
	}
	std::string newEnd = "The new party end time is: ";
	std::cout << newEnd;	
	newEnd += printTime(m_endHour, m_endMin, m_endAM);
	m_backpack.addNote(newEnd);
}


/*****************************************************************
The player uses fireworks. The effect on the game state is that
the game end time is prolonged by 10 minutes. The method takes
no parameters and has no return value. 
*****************************************************************/

void ThiefGame::useFireworks()
{
	constexpr int addedMin{ 10 };

	extendGame(addedMin);
	
	std::cout << "\nThe fireworks excite the guests and the party will "
		<< "last longer!\n";	
}

/*****************************************************************
The player gives truth candy to a guest. The guest reveals 
whether or not he/she is the thief. The method takes no parameters
and has no return value.
*****************************************************************/

void ThiefGame::useTruthCandy()
{
	Person* guestPtr = dynamic_cast<Person*>(m_playerSpace);
	std::string guestName = guestPtr->getName();
	// build up string that will be added to the notepad
	std::string noteStr = guestName + " revealed that ";
	if (guestPtr->isMale())
	{
		noteStr += "he ";
	}
	else
	{
		noteStr += "she ";
	}

	std::cout << "\nYou: Here, try out this candy bar, it's "
		<< "really good!\n"
		<< guestName << ": Thanks! ... Mmmm this is tasty.. But it is"
		<< " strange that you're carrying\ncandy around at a party. "
		<< "And you've got a poor sense of style, a weird\nlooking haircut"
		<< ", and a..\n"
		<< "You: OKAY, thanks.. Appreciate the honesty. I have a "
		<< "question, did you steal my\nwallet tonight?\n"
		<< guestName << ": ";

	if (m_playerSpace == m_thief)
	{
		std::cout << "Yes, I did ";
		noteStr += "stole your wallet.";
	}
	else
	{
		std::cout << "No, I did not ";
		noteStr += "did not steal your wallet.";
	}
	std::cout << "steal your wallet!\n";
	m_backpack.addNote(noteStr);	
}

/*****************************************************************
Allows the player to use the launcher. Launches the player in 
the direction of their choice (or no launch at all if they so
choose). The method has no return value and the int value of
the parameter represents the direciton of the launch. The 
argument values represent:
1 - no launch
2 - launch up
3 - launch right
4 - launch down 
5 - launch left
If an argument is passed that does not hold one of these values,
then the player is not launched.
*****************************************************************/

void ThiefGame::useLauncher(int direction)
{
	static constexpr int NOLAUNCH{ 1 };
	static constexpr int UP{ 2 };
	static constexpr int RIGHT{ 3 };
	static constexpr int DOWN{ 4 };
	static constexpr int LEFT{ 5 };

	static const std::string crashMsg{ "\nYou fly across the room "
		"and slam into the wall!\n" };
	static const std::string mapMsg{ "\nAn updated map of the room:\n" };

	// pointer that is used for determining new player location
	Space* nextSpace = m_playerSpace;
	// old space which will be used to determine if the player
	// actually moved from the launch location
	Space* oldSpace = m_playerSpace;

	// move the player to the far edge of the room in the
	// direction which they choose
	switch (direction)
	{
		case UP:
		{
			nextSpace = nextSpace->getUp();
			while (nextSpace != nullptr)
			{	
				m_playerSpace = nextSpace;
				nextSpace = nextSpace->getUp();
			} 
			std::cout << crashMsg << mapMsg;
			printRoom();
			break;
		}

		case RIGHT:
		{
			nextSpace = nextSpace->getRight();
			while (nextSpace != nullptr)
			{
				m_playerSpace = nextSpace;
				nextSpace = nextSpace->getRight();
			}
			std::cout << crashMsg << mapMsg;
			printRoom();	
			break;
		}

		case DOWN:
		{
			nextSpace = nextSpace->getDown();
			while (nextSpace != nullptr)
			{
				m_playerSpace = nextSpace;
				nextSpace = nextSpace->getDown();
			}
			std::cout << crashMsg << mapMsg;
			printRoom();				
			break;
		}

		case LEFT:
		{
			nextSpace = nextSpace->getLeft();
			while (nextSpace != nullptr)
			{
				m_playerSpace = nextSpace;
				nextSpace = nextSpace->getLeft();
			}
			std::cout << crashMsg << mapMsg;
			printRoom();	
			break;
		}

		// do nothing if player chooses or invalid argument value
		default:
		{
			break;
		}
	}

	// if player launched to a new Space, need to interact with
	// the new Space
	if (m_playerSpace != oldSpace)
	{
		interact();
	} 
}

/*****************************************************************
Destructor. Frees the memory associated with each of the 
dynamically allocated Spaces in the room matrix.
*****************************************************************/

ThiefGame::~ThiefGame()
{
	for (int i = 0; i < NUM_ROWS; i++)
	{
		Space* curSpace = m_rowStart[i];
		while (curSpace != nullptr)
		{
			Space* nextSpace = curSpace->getRight();
			delete curSpace;
			curSpace = nextSpace;
		}
	}
}

