/*********************************************************************
** Program name: Clue.hpp
** Author:		Doug Hughes
** Date:		December 10, 2019
** Description:	Header file for the Clue class.
**				Derived class of the Space class. The class is used
**				to represent Spaces that hold clues regarding the
**				identity of the thief (in the context of the 
**				ThiefGame class). A clue has a text member variable
**				that holds the content of the clue.
*********************************************************************/

#ifndef CLUE_HPP
#define CLUE_HPP

#include "Space.hpp"
#include <string>

class Clue : public Space {
	private:
		// string holding the text of the clue
		std::string m_text;	
		static const std::string TYPE;
	public:
		// Constructor. Sets the clue text based
		// on the single parameter
		Clue(std::string clueStr);

		// Returns a string representing the Clue
		// type. Used to distinguish Clue spaces 
		// from other spaces when a Space pointer is
		// being used.
		virtual std::string getType() const override;

		// Returns the same value as the getType
		// method but can be used without a specific
		// object instance.
		static std::string statType();

		// Prints a single character to the console
		// representing the Clue space.
		virtual void printSpace() const override;

		// Performs an event related to the Clue
		// and returns a string representing the
		// event.
		virtual std::string event() override;

		// Returns information related to the Clue
		// as a string. No parameters.
		virtual std::string information() override;	
};

#endif


