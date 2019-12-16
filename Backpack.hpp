/*********************************************************************
** Program name: Backpack.hpp
** Author:		Doug Hughes
** Date:		December 10, 2019
** Description:	Header file for the Backpack class.
**				Used with the ThiefGame class to represent the 
**				player's backpack. The backpack can be used to 
**				store and read notes, to call the police and to
**				store and use additional items. The class, through
**				its callPolice method, handles whether or not the
**				player guesses the identity of the thief correctly.
**				The backpack can only hold one extra item at any
**				given time. 				
*********************************************************************/

#ifndef BACKPACK_HPP
#define BACKPACK_HPP

#include <string>
#include <vector>
#include "Space.hpp"
#include "Menu.hpp"

class Backpack {
	private:	
		// holds true if the player has fireworks in the 
		// backpack and false if not
		bool m_hasFireworks;
		// holds true if the player has a truth candy bar
		// in the backpack and false if not
		bool m_hasTruthBar;
		// holds the name of the thief
		std::string m_thiefName;
		// holds the player's notepad as a vector of strings
		std::vector<std::string> m_notePad;
		// hold the player's contacts (i.e. guests met thus
		// far) as a vector of strings
		std::vector<std::string> m_contacts;
		// holds the Menu of available options when the
		// backpack is opened
		Menu m_optionsMenu;
		// enum that is used to determine backpack option
		// selected
		enum BPOption { NOTEPAD = 1, POLICE, EXTRA };

		// prints all of the notes in the notepad to the 
		// console. The method takes no parameters and 
		// has no return value.
		void printNotes() const;

		// Uses the extra item in the backpack (i.e. not 
		// the notepad or the phone). The method takes as
		// a parameter a pointer to the player's current
		// Space. The method returns 0 if the extra item
		// could not be used, 1 if fireworks were used, and
		// 2 if a truth candy bar was used. 
		int useExtraItem(Space* curSpace);
	public:
		// default constructor
		Backpack();

		// adds a note the notepad in the backpack. The note
		// added is taken as the parameter and the method
		// has no return value.
		void addNote(std::string note);

		// adds a contact for the player to have as an 
		// option when guessing the thief. The method
		// has no return value and has a string parameter
		// representing the name of the contact.
		void addContact(std::string name);

		// The backpack is opened. The method takes in as
		// a parameter a pointer to the Space on which 
		// the backpack is being used. The method returns
		// an int value representing the outcome of the
		// action taken after opening the backpack.
		int open(Space* curSpace);

		// Calls the police. This presents the player
		// with the option to guess who the thief is.
		// The player can only guess the names of guests
		// that the player has met. The method has no paramters
		// and has an int return value. A return value of 0 
		// indicates that the thief was guessed incorrectly and
		// a return value of 1 indicates a correct guess.
		int callPolice() const;

		// Setter method for the m_thiefName variable.
		void setThief(std::string thiefName);

		// Attempts to add an item to the backpack. If
		// the backpack has extra space, the item is added
		// and if the backpack does not have extra space,
		// then the item is not added. A message is output
		// to the console indicating whether or not the item
		// was added. The method returns true if the item
		// is added and false otherwise.
		bool add(std::string itemType);	
};

#endif
