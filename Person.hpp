/*********************************************************************
** Program name: Person.hpp
** Author:		Doug Hughes
** Date:		December 10, 2019
** Description:	Header file for the Person class.
**				Derived class of the Space class. Used with the 
**				ThiefGame class to represents party guests in the 
**				game. Each person object holds various information
**				including:
**				- name
**				- gender
**				- whether they have been met yet or not by the player
**				The player is meant to "meet" the guests when the 
**				player steps on a Person space, or has a new 
**				interaction with the Person if that Person is already
**				met.
*********************************************************************/

#ifndef PERSON_HPP
#define PERSON_HPP

#include "Space.hpp"
#include <string>

class Person : public Space {
	private:
		// holds the name of the person
		std::string m_name;
		// holds true if the person has been met and
		// false otherwise
		bool m_met;
		// holds true if the person is male and false
		// otherwise.
		bool m_male;
		// constant representing the type of Person
		// spaces
		static const std::string TYPE;
	public:
		// Constructor. The first parameter sets the
		// name of the person and the second parameter
		// is true if the person is male and false if female.
		Person(std::string name, bool male);

		// Returns a string representing the Person
		// type. Used to distinguish Person spaces 
		// from other spaces when a Space pointer is
		// being used.
		virtual std::string getType() const override;

		// Returns the same value as the getType
		// method but can be used without a specific
		// object instance.
		static std::string statType();

		// Prints a single character to the console
		// representing the Person space.
		virtual void printSpace() const override;

		// Performs an event related to the Person
		// and returns a string representing the
		// event.
		virtual std::string event() override;

		// Returns information related to the Person
		// as a string. No parameters.
		virtual std::string information() override;

		// Getter method for the m_male variable. 
		bool isMale() const;
	
		// Getter method for the m_name variable.
		std::string getName() const;

		// Getter method for the m_met variable.
		bool isMet() const;
};

#endif


