/*********************************************************************
** Program name: Space.hpp
** Author:		Doug Hughes
** Date:		December 10, 2019
** Description:	Header file for the Space class.
**				Used with the ThiefGame to represent individual 
**				spaces in the room. This is an abstract base class.
**				Each Space holds pointer to four adjacent Spaces
**				(up, down, right, and left). All adjacent spaces
**				are initially set to nullptr. If a Space is adjacent
**				to a "wall" of the room, then the pointers in the
**				direction of the wall are meant to stay as nullptr.
**				A Space has getter and setter methods for each of
**				its adjacent pointers. Every Space has a type, a
**				console print method, an event, and information that
**				it provides.
*********************************************************************/

#ifndef SPACE_HPP
#define SPACE_HPP

#include <string>

class Space {
	private:
		// pointers for each of the adjacent Spaces
		Space* upSpace;
		Space* rightSpace;
		Space* downSpace;
		Space* leftSpace;
	public:
		// default constructor
		Space();

		// setter and getter methods for the adjacent Spaces
		void setUp(Space* spc);
		void setRight(Space* spc);
		void setDown(Space* spc);
		void setLeft(Space* spc);
		Space* getUp() const;
		Space* getRight() const;
		Space* getDown() const;
		Space* getLeft() const;

		// pure virtual method that is meant to return the derived
		// type of the Space as a string
		virtual std::string getType() const = 0;

		// pure virtual method that is meant to print a single
		// character to the console representing the derived Space
		virtual void printSpace() const = 0;

		// pure virtual method that is meant to perform an event
		// related to the derived Space and returns a string
		// related to the event
		virtual std::string event() = 0; 

		// pure virtual method that is meant to return 
		// information relating to the derived Space as 
		// a string.
		virtual std::string information() = 0;

		// Virtual destructor. The class does not make use of
		// any dynamically allocated memory. But a virtual 
		// destructor is included so the Space pointers to 
		// derived objects can properly deallocate memory.
		virtual ~Space();
			
};

#endif
