/*********************************************************************
** Program name: Stereo.cpp
** Author:		Doug Hughes
** Date:		December 10, 2019
** Description:	Implementation file for the Stereo class.
**				Derived class of the Space class. Used with the 
**				ThiefGame class to represent the stereo in the room.
**				The stereo is meant to be used by the player and to
**				have different effects on the state of the game 
**				depending on which song the player chooses to play.
**				The stereo can only be played when it has power
**				(i.e. the m_power member variable is set to true).
**				The stereo is meant to be played at most once per
**				game.
*********************************************************************/

#include "Stereo.hpp"
#include "Menu.hpp"
#include <iostream>
#include <string>

// intitialize the TYPE static constant
const std::string Stereo::TYPE{ "Stereo" };

/****************************************************************
Default constructor. Sets the m_power variable to true
because the stereo starts out with its power on.
****************************************************************/

Stereo::Stereo()
	: m_power{ true }	
{
}

/****************************************************************
Returns the TYPE string which represents the Stereo type.
No parameters.
****************************************************************/

std::string Stereo::getType() const
{
	return TYPE;
}

/****************************************************************
Returns the TYPE string which represents the Stereo type.
No parameters. Static method so can be used without an object
instance.
****************************************************************/

std::string Stereo::statType()
{
	return TYPE;
}

/****************************************************************
Prints a single character to the console representing the
Stereo space. The method takes no parameters and has no return 
value.
****************************************************************/

void Stereo::printSpace() const
{
	std::cout << "S"; 
}

/****************************************************************
Simply returns the type of the Stereo to indicate that the 
player can attempt to play the stereo. The method has a string
return value and no parameters.
****************************************************************/

std::string Stereo::event()
{
	return TYPE;	
}

/****************************************************************
Attempts to play the stereo. If the stereo has no power, then it
cannot be played and 0 is returned. Otherwise, the player can
choose to either play music that shocks/angers the guest (in 
which case a value of 1 is returned) or music that excites the
guests (in which case a value of 2 is returned). The method
has no parameters and an int return value.
****************************************************************/

int Stereo::playStereo() 
{
	// check to see if the stereo does not have power
	if (!m_power)
	{
		std::cout << "The power cord to the stereo is torn to "
			<< "shreds and is no longer functional.\n";	
		return 0;
	}

	// switch the power to off so that the stereo can't be
	// used again
	m_power = false;

	Menu playMenu;
	playMenu.addOption("Your favorite Lizzo song");
	playMenu.addOption("Baha Men - Who Let the Dogs Out");

	std::cout << "\nThere are two song options on the stereo; "
		<< "make your pick!\n";	

	const int LIZZO = 1;
	const int DOGS = 2;

	int songChoice = playMenu.chooseOption();

	if (songChoice == LIZZO)
	{
		std::cout << "You play your favorite Lizzo song. You raise "
			<< "the volume to a deafening blare!\nA number of guests "
			<< "are alarmed and rapidly flee from the party.\n"
			<< "A particularly affected guest lets out a howl of "
			<< "existential terror.\nThe thief has a poor taste in "
			<< "music and stays despite the cacophony.\nOne of the " 
			<< "traumatized guests tears apart the power cord to the "
			<< "stereo in a fit\nof hysteria before exiting the event.\n";
		return LIZZO;
	}

	else
	{
		std::cout << "You play Who Let the Dogs Out by Baha Men.\n"
			<< "The guests are at once stunned and overjoyed to hear a "
			<< "musical composition of\nsuch artistic genius. "
			<< "The party quickly erupts into a chaotic frenzy of primal"
			<< "\necstasy. "
			<< "As the song ends, a guest rabidly tears apart the power"
			<< " cord to the\nstereo exclaiming that it would be "
			<< "disrespectful to play any other music\nfollowing such a "
			<< "phenomenal display of unmatched artistry.\nThe party "
			<< "applauds in unanimous agreement.\n";
		return DOGS;
	}
}

/****************************************************************
Returns information related to the Stereo as a string. Given that
Stereo spaces do not contain any information, the method returns
an empty string.
****************************************************************/

std::string Stereo::information() 
{
	return "";	
}

/****************************************************************
Getter method for the m_power variable.
****************************************************************/

bool Stereo::powerOn() const
{
	return m_power;
}

