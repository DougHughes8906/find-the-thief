/*********************************************************************
** Program name: FireworksBox.hpp
** Author:		Doug Hughes
** Date:		December 10, 2019
** Description:	Header file for the FireworksBox class.
**				Derived class of the Space class. Used to represent
**				spaces that hold fireworks items that can be picked
**				up by the player and stored in the backpack. 
*********************************************************************/

#ifndef FIREWORKSBOX_HPP
#define FIREWORKSBOX_HPP

#include "Space.hpp"
#include <string>

class FireworksBox : public Space {
	private:	
		static const std::string TYPE;
		static const std::string ITEM;
	public:
		// Default constructor
		FireworksBox();

		// Returns a string representing the FireworksBox
		// type. Used to distinguish FireworksBox spaces 
		// from other spaces when a Space pointer is
		// being used.
		virtual std::string getType() const override;

		// Returns the same value as the getType
		// method but can be used without a specific
		// object instance.
		static std::string statType();

		// Returns the ITEM static constant string.
		static std::string statItem();

		// Prints a single character to the console
		// representing the FireworksBox space.
		virtual void printSpace() const override;

		// Performs an event related to the FireworksBox
		// and returns a string representing the
		// event.
		virtual std::string event() override;

		// Returns information related to the FireworksBox
		// as a string. No parameters.
		virtual std::string information() override;	
};

#endif



