/*********************************************************************
** Program name: TruthCandyBox.hpp
** Author:		Doug Hughes
** Date:		December 10, 2019
** Description:	Header file for the TruthCandyBox class.
**				Derived class of the Space class. Used with the
**				ThiefGame class to represent spaces from which the
**				player can pick up Truth Candy Bar items. The Truth
**				Candy Bars are meant to be items the player can use
**				to determine if a single guest is the thief.
*********************************************************************/

#ifndef TRUTHCANDYBOX_HPP 
#define TRUTHCANDYBOX_HPP 

#include "Space.hpp"
#include <string>

class TruthCandyBox : public Space {
	private:	
		static const std::string TYPE;
		static const std::string ITEM;
	public:
		// Default constructor
		TruthCandyBox();

		// Returns a string representing the TruthCandyBox
		// type. Used to distinguish TruthCandyBox spaces 
		// from other spaces when a Space pointer is
		// being used.
		virtual std::string getType() const override;

		// Returns the same value as the getType
		// method but can be used without a specific
		// object instance.
		static std::string statType();

		// Returns the ITEM string value which
		// represents the type of item held in this
		// Space.
		static std::string statItem();

		// Prints a single character to the console
		// representing the TruthCandyBox space.
		virtual void printSpace() const override;

		// Performs an event related to the TruthCandyBox
		// and returns a string representing the
		// event.
		virtual std::string event() override;

		// Returns information related to the TruthCandyBox
		// as a string. No parameters.
		virtual std::string information() override;	
};

#endif



