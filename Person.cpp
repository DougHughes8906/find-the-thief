/*********************************************************************
** Program name: Person.cpp
** Author:		Doug Hughes
** Date:		December 10, 2019
** Description:	Implementation file for the Person class.
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

#include "Person.hpp"
#include <string>
#include <cctype>
#include <iostream>
#include <vector>
#include <cstdlib>

// intitialize the TYPE static constant
const std::string Person::TYPE{ "Person" };

/****************************************************************
Constructor. The first parameter sets the name of the person.
The second parameter is set to true if the person is a male 
and false if the person is a female.
****************************************************************/

Person::Person(std::string name, bool male)
	: m_name{ name }, m_met{ false }, m_male{ male }
{
}

/****************************************************************
Returns the TYPE string which represents the Person type.
No parameters.
****************************************************************/

std::string Person::getType() const
{
	return TYPE;
}

/****************************************************************
Returns the TYPE string which represents the Person type.
No parameters. Static method so can be used without an object
instance.
****************************************************************/

std::string Person::statType()
{
	return TYPE;
}

/****************************************************************
Prints a single character to the console representing the
Person space. The character value changes based on whether the
Person has been met or not. The method takes no parameters and
has no return value.
****************************************************************/

void Person::printSpace() const
{
	char letter;
	if (m_met)
	{
		letter = tolower(m_name[0]);
	}
	else
	{
		letter = 'P';
	}
	std::cout << letter; 
}

/****************************************************************
Performs an event related to the Person. The event performed 
depends on whether or not the person has been met yet. The method
takes no parameters. The string return value is the TYPE if the
person is being met for the first time and an empty string 
otherwise.
****************************************************************/

std::string Person::event()
{
	std::cout << m_name;
	if (m_met)
	{
		static std::vector<std::string> returnMsgs{
			": Nice to see you again.\n",
			": Gosh, leave me alone.\n",
			": Woaaah, you look familiar..\n",
			": Long time no see!\n"
		};
		int returnInd = rand() % returnMsgs.size();
		std::cout << returnMsgs[returnInd];
		return "";
	}
	else
	{	
		static std::vector<std::string> introMsgs{
			": Nice to meet you!\n",
			": Hey, how's it going?\n",
			": Fun party, huh? Pleasure to meet you.\n",
			": What's up? Want to be friends?\n"	
		};
		int introInd = rand() % introMsgs.size();
		std::cout << introMsgs[introInd];
		return TYPE;
	}
}

/****************************************************************
Returns information related to the person as a string. The 
method takes no parameters.
****************************************************************/

std::string Person::information() 
{
	if (m_met)
	{
		// No further information is sent if the person is 
		// already met
		return "";
	}

	else
	{
		m_met = true;
		std::string meeting = "I met " + m_name + ". " + m_name
			+ " is ";
		if (m_male)
		{
			meeting += "male.";
		}
		else
		{
			meeting += "female.";
		}
		return meeting;	
	}
}

/****************************************************************
Getter method for the m_male variable. 
****************************************************************/

bool Person::isMale() const
{
	return m_male;
}

/****************************************************************
Getter method for the m_name variable.
****************************************************************/

std::string Person::getName() const
{
	return m_name;
}

/****************************************************************
Getter method for the m_met variable.
****************************************************************/

bool Person::isMet() const
{
	return m_met;
}


