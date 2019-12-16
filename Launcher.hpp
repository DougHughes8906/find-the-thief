/*********************************************************************
** Program name: Launcher.hpp
** Author:		Doug Hughes
** Date:		December 10, 2019
** Description:	Header file for the Launcher class.
**				Derived class of the Space class. Used with the 
**				ThiefGame class to represent spaces from which the
**				player can launch in each of the four directions in
**				the room. Meant to allow the player to quickly move
**				to other parts of the room.
*********************************************************************/

#ifndef LAUNCHER_HPP
#define LAUNCHER_HPP

#include "Space.hpp"
#include <string>

class Launcher : public Space {
	private:	
		static const std::string TYPE;
	public:
		// Default constructor 
		Launcher();

		// Returns a string representing the Launcher
		// type. Used to distinguish Launcher spaces 
		// from other spaces when a Space pointer is
		// being used.
		virtual std::string getType() const override;

		// Returns the same value as the getType
		// method but can be used without a specific
		// object instance.
		static std::string statType();

		// Prints a single character to the console
		// representing the Launcher space.
		virtual void printSpace() const override;

		// Performs an event related to the Launcher
		// and returns a string representing the
		// event.
		virtual std::string event() override;	

		// Allows the player to choose a launch direction.
		// The method has no parameters. The int return value
		// represents the direction chosen. A value of 1 indicates
		// that the player chooses not to launch, 2 indicates a 
		// launch up, 3 indicates a launch right, 4 indicates a 
		// launch down and 5 represents a launch left.
		int chooseDirection() const;

		// Returns information related to the Stereo
		// as a string. No parameters.
		virtual std::string information() override;	
};

#endif


