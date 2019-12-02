

#ifndef THIEFGAME_HPP
#define THIEFGAME_HPP

#include <vector>
#include "Backpack.hpp"
#include "Space.hpp"

class ThiefGame {
	private:
		// constants to represent the size of the room
		// and the starting # of guests
		constexpr int NUM_ROWS = 8;
		constexpr int NUM_COLS = 12;
		constexpr int NUM_GUESTS = 10;

		// holds pointers to the starting spaces for each
		// row in the room
		Space* m_rowStart[NUM_ROWS];

		// holds pointers to the spaces representing each of
		// the guests in the game
		std::vector<Space*> m_guestList;

		// pointer to the thief Space
		Space* m_thief;
		// holds the row/column of the thief
		int m_thiefRow;
		int m_thiefCol;

		// contains true once the game is finished and false
		// otherwise
		bool m_gameFinished;

		// pointer to the Space on which the player is 
		// currently located
		Space* m_playerSpace;

		// the player's backpack
		Backpack m_backpack;

		// meant to hold true once the random seed for the 
		// program has been set and false beforehand
		static bool seedSet;

		// provides the intial setup for the room. Sets up
		// a room solely composed of Floor spaces. The
		// method takes no parameters and has no return
		// value.
		void setEmptyRoom();

		// creates the guests for the game (as Person objects).
		// The method takes as a parameter the number
		// of guests to add. The method can only add up
		// to a certain # of guests. If the argument
		// passed is too high, the maximum number of guests
		// wiil be created (which is less than the argument)
		// and false will be returned. Otherwise, true will 
		// be returned.
		bool createGuests(int numGuests);

		// places the guests that have already been created
		// into the room. The guests are randomly placed
		// throughout the room. The method takes no parameters
		// and has no return value.
		void placeGuests();

		// Returns a random integer between the two
		// parmeters (inclusive).
		int getRand(int min, int max) const;

		// Places a given Space at a random location in the 
		// room. However, the random location must currently
		// be a Floor space. The first parameter is the space
		// that is being placed. The second parameter holds true
		// if the space is the thief (in which case the exact 
		// location of the thief will be saved) and false
		// otherwise. The method has no return value.
		void place(Space* newSpace, bool isThief);

		// Replaces a Space in the room matrix with another
		// Space. The first parameter is the old Space and 
		// the second parameter is the new Space. The method
		// has no return value.
		void replace(Space* oldSpace, Space* newSpace);

		// Creates the clues for the game and places them
		// in random locations in the room. The method takes
		// no parameters and has no return value.
		void setClues();
	
		// Creates the stereo for the game and places it in
		// a random location in the room. The method takes
		// no parameters and has no return value.
		void setStereo();

		// Creates the fireworks box for the game and places
		// it in a random location in the room. The method
		// takes no parameters and has no return value.
		void setFireworks();
	
		// Creates the Truth Candy box for the game and
		// places it in a random location in the room. The 
		// method takes no parameters and has no return value.
		void setTruthCandy();

		// Places the player in a random Floor space in the
		// room by setting the m_playerSpace pointer. The 
		// method takes no parameters and has no return value.
		void placePlayer();

		// Finds and returns a random Floor space in the
		// room (returned as a pointer to the Space). The
		// single parameter holds true if the space will
		// hold the thief (in which case the location of the
		// the space is saved) and false otherwise. 
		Space* getRandFloor(bool isThief);

		// Prints the current in-game time to the console. 
		// The method has no return value. The first parameter
		// represents the current hour as a string, the second
		// parameter the current minute as a string and the 
		// third parameter holds true if the time is AM and
		// false otherwise.
		void printTime(std::string hour, std::string min, 
			bool isAM) const;

		// Adds a minute to a given time. The method has
		// no return value and takes in three reference
		// parameters. The first parameter represents the
		// current hour as a string, the second parameter
		// represents the current minute as a string, and
		// the third parameter holds true if the time is AM
		// and false otherwise.
		void addMin(std::string &hour, std::string &min,
			bool &isAM) const;

		// Sets up the player's move menu for a single 
		// turn. The menu is built based on where the player
		// can move to from the current player location. The
		// method has no return value and takes a single 
		// reference parameter representing the move menu.
		void setMoveMenu(Menu &moveMenu) const;

		// Prints the current state of the room as a grid.
		// The method prints a '*' at the location of the
		// player rather than the print value of the underlying
		// Space. The method takes no parameters and has no 
		// return value.
		void printRoom() const;

		// The player interacts with the current Space on 
		// which the player is located. Any event associated
		// with the space is performed and any information
		// related to the Space is received. The method takes
		// no parameters and has no return value.
		void interact();

		// An event is performed based on the Space on which
		// the player is currently located. The method takes
		// no parameters and has no return value.
		void performEvent();

		// Deletes about half of the guests from the party,
		// simulating these guests leaving the party. The
		// guests are chosen at random but cannot include
		// the thief. The method takes no parameters and has
		// no return value.
		void randGuestsLeave();

		// The method tries to add a given item to the player's
		// backpack and prints a message accordingly. If the
		// item is successfully added, then the Space is changed
		// to a Floor space. If the player's backpack is currently
		// full then a message is printed to the console indicating
		// this (and the current Space is not changed). The method
		// takes as a parameter the type of item being added 
		// (as a string) and has no return value.
		void getItem(std::string itemType);

		// Ends the game in a loss. The method indicates to the 
		// player that the real thief has escaped and the 
		// identity of the thief. The method has no parameters
		// and no return value.
		void gameLoss();

		// Ends the game with a win. The method indicates to the
		// player that they guessed the identity of the thief 
		// correctly. The method has no parameters and no 
		// return value.
		void gameWin();

		// The player uses fireworks. The effect is that the 
		// game end time is delayed. The method has no return
		// value and takes three reference parameters. The 
		// first parameter represents the end hour as a string,
		// the second parameter represents the end minute as
		// a string, and the last parameter is a bool value that
		// holds true if the end time is currenty AM and false
		// otherwise. 
		void useFireworks(std::string &endHour, std::string &endMin,
			bool &endAM);

		// The player gives truth candy to a guest. The guest reveals
		// whether or not he/she is the thief. The method takes no 
		// parameters and has no return value.
		void useTruthCandy(); 
 
	public:
		// default constructor, sets up the initial state for
		// the game
		ThiefGame();

		// Runs a full Find the Thief game. If the game for this
		// instance has already been completed, the method does
		// nothing and returns false. Otherwise, the method
		// completes a single game and returns true. The method
		// takes no parameters.
		bool runGame();
};

#endif
