/*********************************************************************
** Program name: Backpack.cpp
** Author:		Doug Hughes
** Date:		December 10, 2019
** Description:	Implementation file for the Backpack class.
**				Used with the ThiefGame class to represent the 
**				player's backpack. The backpack can be used to 
**				store and read notes, to call the police and to
**				store and use additional items. The class, through
**				its callPolice method, handles whether or not the
**				player guesses the identity of the thief correctly.
**				The backpack can only hold one extra item at any
**				given time. 				
*********************************************************************/

#include "Backpack.hpp"
#include "Space.hpp"
#include "Menu.hpp"
#include "Floor.hpp"
#include "Person.hpp"
#include "FireworksBox.hpp"
#include "TruthCandyBox.hpp"
#include <string>
#include <vector>
#include <iostream>

/******************************************************************
Default constructor. Sets up the initial values for the member
variables.
******************************************************************/

Backpack::Backpack()
	: m_hasFireworks{ false }, 
	  m_hasTruthBar{ false },
	  m_thiefName{ "" }
{
	std::string notePadOption{ "Read your notepad" };
	std::string policeOption{ "Call the police" };
	m_optionsMenu.addOption(notePadOption);
	m_optionsMenu.addOption(policeOption);	
}

/******************************************************************
Adds a note to the notepad. The note added is taken as the single
parameter and the method has no return value. If the note is an
empty string, then it is not added.
******************************************************************/

void Backpack::addNote(std::string note)
{
	if (note != "")
	{
		m_notePad.push_back(note);
	}
}

/******************************************************************
Adds a contact for the player to have as an option when guessing
the thief. The method has no return value and has a string 
parameter representing the name of the contact.
******************************************************************/

void Backpack::addContact(std::string name)
{
	m_contacts.push_back(name);	
}

/******************************************************************
The backpack is opened and the player can read the notepad, call
the police or use the extra item (if available). The method takes
in as a parameter a pointer to the Space on which the backpack is
being used. The method returns an int value representing the 
outcome fo the action taken after opening the backpack. The return
values have the following meanings:
0 - the player called the police but guessed the identity of the 
thief incorrectly
1 - the player did not take any action (ex. just read the notepad)
2 - the player called the police and guessed the identity of the
thief correctly
3 - the player used fireworks
4 - the player used the truth candy bar
******************************************************************/

int Backpack::open(Space* curSpace)
{
	BPOption userChoice = 
		static_cast<BPOption>(m_optionsMenu.chooseOption());

	static constexpr int WRONG{ 0 };
	static constexpr int NOACTION{ 1 };
	static constexpr int CORRECT{ 2 };
	static constexpr int FWORKS{ 3 };
	static constexpr int TBAR{ 4 };

	switch (userChoice)
	{
		case NOTEPAD:
		{
			printNotes();
			return NOACTION;
			break;
		}
		case POLICE:
		{
			int policeVal = callPolice();
			if (policeVal == 0)
			{
				return NOACTION;
			}
			else if (policeVal == 1)
			{
				return CORRECT;
			}
			else
			{
				return WRONG;
			}
			break;
		}
		// the last possible option is that the player chose
		// the extra item
		default:
		{
			int usedItem = useExtraItem(curSpace);
			if (usedItem == 0)
			{
				return NOACTION;
			}
			else
			{
				// usedItem will have a value of 1 if fireworks
				// were used and 2 if truth candy was used
				return usedItem + 2;	
			}
			break;
		}
	}
}

/******************************************************************
Prints all of the notes in the player's notepad to the console. 
The method takes no parameters and has no return value.
******************************************************************/

void Backpack::printNotes() const
{
	std::cout << "\n********************************"
		<< "\nNOTEPAD\n\n";
	for (int i = 0; i < m_notePad.size(); i++)
	{
		std::cout << "> " << m_notePad[i] << "\n";
	}	
}

/******************************************************************
Uses the extra item in the backpack (i.e. not the notepad or the
phone). The single parameter is a pointer to the player's current
space. The method has an int return value. The possible return 
values are:
0 - indicates that the backpack does not currently have an extra
item or that the extra item could not be used on the current 
space.
1 - indicates that fireworks were used
2 - indicates that a truth candy bar was used 
******************************************************************/

int Backpack::useExtraItem(Space* curSpace)
{
	static constexpr int CANTUSE = 0;
	static constexpr int FWORKS = 1;
	static constexpr int TBAR = 2;

	if (m_hasFireworks)
	{
		// the fireworks can only be used on Floor spaces
		if (curSpace->getType() != Floor::statType())
		{
			std::cout << "\nYou could not set off the fireworks. The"
				<< " fireworks need to be set off on empty\nfloor "
			  	<< "space.\n";
			return CANTUSE;
		} 			
		
		std::cout << "\nYou set off the fireworks. There is a "
			<< "beautiful display of vibrant colors.\nMiraculously,"
			<< " nothing in the room sets on fire.\n";
		m_hasFireworks = false;
		m_optionsMenu.deleteLast();
		return FWORKS;
	}
	
	else if (m_hasTruthBar)
	{
		// truth bars can only be used on Person spaces
		if (curSpace->getType() != Person::statType())
		{
			std::cout << "\nYou must be on a space with a guest to"
				<< " feed them a truth bar.\n";
			return CANTUSE;
		}

		m_hasTruthBar = false;
		m_optionsMenu.deleteLast();
		return TBAR;
	}	

	// the backpack does not have any extra item
	else
	{
		return CANTUSE;
	}	
}

/******************************************************************
Calls the police. This presents the player with the option to
guess who the thief is. The player can only guess the names of
guests that the player has met. The method has no parameters
and has an int return value. A return value of -1 indicates that 
the thief was guessed incorrectly and a return value of 1 
indicates a correct guess. If the player hasn't met anyone yet,
then the call is not made and the method returns 0.
******************************************************************/

int Backpack::callPolice() const
{
	static constexpr int INCORRECT{ -1 };
	static constexpr int NOTHING{ 0 };
	static constexpr int CORRECT{ 1 };

	// do nothing if the player hasn't met anyone yet
	if (m_contacts.size() == 0)
	{
		std::cout << "\nYou put your phone back in your backpack as "
			<< "you realize you haven't met anyone\nat the party yet"
			<< " (and therefore won't have any guess for the identity of"
			<< " the\nthief).\n";
		return NOTHING;
	}

	std::cout << "\nDialing 9-1-1....\n"
		<< "Operator: 9-1-1 operator. What is your emergency?\n"
		<< "You: I am at a party and someone has stolen my "
		<< 	"wallet.\n"
		<< "Operator: Do you know who stole the wallet?\n";
	std::cout << "\nYou must guess who at the party stole your"
		<< " wallet. Choose from one of the guests below.\n";
	Menu guestMenu;
	int thiefOpVal = -1;
	for (int i = 0; i < m_contacts.size(); i++)
	{
		// store the option value of the thief (if the 
		// thief has been met by the player
		if (m_contacts[i] == m_thiefName)
		{
			thiefOpVal = i + 1;
		}
		guestMenu.addOption(m_contacts[i]);
	}

	int playerGuess = guestMenu.chooseOption();

	std::cout << "\nYou: I think that " << m_contacts[playerGuess - 1]
		<< " stole my wallet!\n"
		<< "Operator: Okay, we will have a unit there shortly.\n"
		<< "\nMinutes later, the police arrive at the party.\n";
	
	if (playerGuess == thiefOpVal)
	{			
		return CORRECT;		
	}

	else
	{	
		return INCORRECT;
	}		
}

/******************************************************************
Setter method for the m_thiefName variable.
******************************************************************/

void Backpack::setThief(std::string thiefName)
{
	m_thiefName = thiefName;
}

/******************************************************************
Attempts to add an item to the backpack. If the backpack has 
extra space, the item is added, otherwise the item is not added.
A message is output to the console in either scenario. The single
parameter represents as a string the type of item being added.
The method returns true if the item was added and false if it was
not added.
******************************************************************/

bool Backpack::add(std::string itemType)
{
	// constants to add as menu options
	static const std::string fworksOption{ "Use fireworks" };
	static const std::string tbarOption{ "Use Truth Candy Bar" };

	if (m_hasFireworks || m_hasTruthBar)
	{
		std::cout << "\nYour backpack is full and you are not"
			<< " able to add the " << itemType << ".\n";
		return false;
	}
	
	else
	{
		if (itemType == FireworksBox::statItem())
		{
			m_hasFireworks = true;
			m_optionsMenu.addOption(fworksOption);
			std::cout << "\nYou place the fireworks into your "
				<< "backpack.\n";	
		}
		else
		{
			m_hasTruthBar = true;
			m_optionsMenu.addOption(tbarOption);
			std::cout << "\nYou place the Truth Candy Bar into "
				<< "your backpack.\n";
		}
		return true;
	}
}

