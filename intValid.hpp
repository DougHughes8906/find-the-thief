/*********************************************************************
** Program name: intValid.hpp
** Author:	Doug Hughes
** Date:	November 30, 2019
** Description:	Header file for an integer input validation function.
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

#ifndef INTVALID_HPP
#define INTVALID_HPP

// default int validation function. It simply ensures that a valid integer
// value is input by re-prompting until such a value is entered. That value
// is then returned by the function.
int intValid();
// two parameter int validation function. It works exactly the same as the
// default function except that it also checks to make sure the int is 
// within a specified range. The first parameter is the minimum of the range
// (inclusive) and the second parameter is the maximum of the range (inclusive)
int intValid(int min, int max);

#endif
