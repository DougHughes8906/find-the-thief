/*********************************************************************
** Program name: intValid.cpp
** Author:	Doug Hughes
** Date:	October 20, 2019
** Description:	Implement. file for an integer input validation function.
**		The function waits until an integer is validly entered
**		by the user and returns this integer. If a line of 
**		input starts with invalid input, the whole line will
** 		be ignored and the user will be re-prompted to enter
**		an integer. Any input after the first integer will 
** 		be cleared (i.e. for successive inputs the user will
**		need to press ENTER each time, not just space).
**		If a floating point number is entered, the user
**		will be re-prompted for input.
**		Default function returns any valid integer. The two
**		parameter function only returns integer within an 
** 		an inclusive range (the first parameter is the min
** 		and the second parameter is the max). If the min 
**		parameter is greater than the max, it is assumed that
**		the parameters were entered in the wrong order and 
**		the min parameter is treated as the max (and vice
**		versa). 
*********************************************************************/

#include "intValid.hpp"
#include <iostream>
#include <string>
#include <cctype>
#include <cstdlib>
#include <climits>

/***************************************************************************
Two parameter int validation function. The function calls the default
int validation function itself, but this function has the added capability
of ensuring that the int entered is within a specified range. The first
int parameter is treated as the minimum of the range and the second int
parameter is treated as the maximum of the range (both inclusive). However,
if the first parameter entered is greater than the second parameter, it is 
assumed that the parameters were just entered in the incorrect order and 
the first parameter is treated as the maximum (and vice versa).
***************************************************************************/

int intValid(int min, int max)
{
	// if min is greater than max it is assumed the parameters
	// were just entered in the wrong order
	if (min > max)
	{
		int temp = min;
		min = max;
		max = temp;
	}

	// use the default funtion and then check to make sure
	// return value is in range	
	int val = intValid();
	if (val >= min && val <= max)
		return val;
	else
	{
		while (!(val >= min && val <= max))
		{
			std::cout << "The entered value is not within "
			     << "the specified range of " << min
			     << " to " << max << " (inclusive).\n"
			     << "Please enter a new value in this"
			     << " range.\n";
			val = intValid();
		}
		return val;
	}

}

/***************************************************************************
Default int validation function. The function reads input from the console
and ensures that the input is an int value. It ensures this by re-prompting
the user until a valid int is entered. If the value entered is a floating
point number, the user will be re-prompted for input. 
The function can handle all possible valid int inputs (from INT_MIN
through INT_MAX). 
***************************************************************************/

int intValid()
{
	while(true)
	{
		std::string input;
		// variable will be set to true if an integral value is 
		// input but it is out of range for int
		bool outOfRange = false;
		std::getline(std::cin, input);

		// get i to index of first non-space and non-tab character

		int i = 0;
		while (i < input.length() && (input[i] == ' ' ||
					      input[i] == '\t'))
			i++;

		// see if there is an integer starting from this index

		if (input.length() > i && (isdigit(input[i])
					   || input[i] == '-'))
		{
			// make sure if there is minus sign, there is 
			// an integer following the sign		
			if (input[i] != '-' || (input.length() > i + 1 &&
						isdigit(input[i + 1])))
			{
				std::string str = "";
				str += input[i];
				i++;
				// continue adding digits while there are
				// more in input

				while (i < input.length() && isdigit(input[i]))
				{	
					str += input[i];
					i++;
				}
				// make sure the number entered is not a
				// floating point number
				if (i == input.length() || input[i] != '.')
				{
					// make sure integer is not too large.
					// copy string into c-string to allow
					// use of the strtoll function		
					char* cstr = new char[str.length() + 1];
					for (int m = 0; m < str.length(); m++)
						cstr[m] = str[m];
					cstr[str.length()] = '\0';	
					long long int val =
						     strtoll(cstr, nullptr, 10);
					delete[] cstr;
					cstr = nullptr;

					if (val <= INT_MAX && val >= INT_MIN)
						return val;
					else
						outOfRange = true;
				}			
			}	
		}
		if (outOfRange)
			std::cout << "The value entered is out of range. "
				  << "Please input a new value. " << std::endl;
		else
			std::cout << "An integer value was not entered. "
				  << "Please type an integer value and "
				  << "press ENTER." << std::endl;
	}
}
