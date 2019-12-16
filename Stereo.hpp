/*********************************************************************
** Program name: Stereo.hpp
** Author:		Doug Hughes
** Date:		December 10, 2019
** Description:	Header file for the Stereo class.
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

#ifndef STEREO_HPP
#define STEREO_HPP

#include "Space.hpp"
#include <string>

class Stereo : public Space {
	private:
		// bool value holds true if the stereo has power
		bool m_power;	
		static const std::string TYPE;
	public:
		// Default constructor 
		Stereo();

		// Returns a string representing the Stereo
		// type. Used to distinguish Stereo spaces 
		// from other spaces when a Space pointer is
		// being used.
		virtual std::string getType() const override;

		// Returns the same value as the getType
		// method but can be used without a specific
		// object instance.
		static std::string statType();

		// Prints a single character to the console
		// representing the Stereo space.
		virtual void printSpace() const override;

		// Performs an event related to the Stereo
		// and returns a string representing the
		// event.
		virtual std::string event() override;

		// Attempts to play the stereo. Returns 0 if
		// the stereo can't be played, 1 if the player
		// chose bad music and 2 if the player chose
		// good music.
		int playStereo();

		// Returns information related to the Stereo
		// as a string. No parameters.
		virtual std::string information() override;

		// Getter method for the m_power variable
		bool powerOn() const;	
};

#endif


