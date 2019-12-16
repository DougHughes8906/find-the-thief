/*********************************************************************
** Program name: Floor.hpp
** Author:		Doug Hughes
** Date:		December 10, 2019
** Description:	Header file for the Floor class.
**				Derived class of the Space class. The class is used 
**				in conjunction with the ThiefGame class to represent
**				empty floor spaces in the game. There is no 
**				special interaction or information associated with
**				these empty floor spaces.
*********************************************************************/

#ifndef FLOOR_HPP
#define FLOOR_HPP

#include "Space.hpp"
#include <string>

class Floor : public Space {
	private:	
		static const std::string TYPE;
	public:
		// Default constructor
		Floor();

		// Returns a string representing the Floor
		// type. Used to distinguish Floor spaces 
		// from other spaces when a Space pointer is
		// being used.
		virtual std::string getType() const override;

		// Returns the same value as the getType
		// method but can be used without a specific
		// object instance.
		static std::string statType();

		// Prints a single character to the console
		// representing the Floor space.
		virtual void printSpace() const override;

		// Performs an event related to the Floor
		// and returns a string representing the
		// event.
		virtual std::string event() override;

		// Returns information related to the Floor
		// as a string. No parameters.
		virtual std::string information() override;	
};

#endif


