#include <iostream>		//general IO goodness :)
#include <string>		//Love strings
#include <ctype.h>		//For the isdigit() function to test user input
#include <climits>		//For INT_MAX to test potential overflow
using namespace std;

/**********************************************
* NAME: 		Jonny Olswang
* DATE:			April 17, 2023
* CLASS:		CECS 325-01, MW 6:00p-7:15p
* PROGRAM 6: 	3n + 1
*
* I certify that this program is my own original work. I did not copy any part of this program from
* any other source. I further certify that I typed each and every line of code in this program.
* ---------------------------------------------
* This program takes in positive integers from
* the command line to test the Collatz conjecture.
* If there is overflow, an exception is thrown
* and caught in main(), and the program continues
* onto the next number. 
***********************************************/

/****************************************************
* STRUCT Statistics
*
* This struct keeps track of a given number's stats
* as we perform the Collatz conjecture, and will 
* output after each number reaches the base case of 1. 
*****************************************************/
struct Statistics
{
	int start = 0;		//Starting number
	int steps = 0;		//Number of steps to base case
	int max = 0;		//Highest number in sequence
	int oddCount = 0;	//Number of odd numbers in sequence
	int evenCount = 0;	//Number of even numbers in sequence
};

/**********************************************
* PROTOTYPES - SEE BELOW MAIN()
***********************************************/
bool isPositiveInteger(string in);
bool isEven(int n);
void threeN(int n, Statistics& stats);
void printStats(const Statistics stats);

int main(int argc, char* argv[])
{
	int i = 0;	//Loop variable to traverse all args, even if catch block interrupts

	while(i < argc)	
	{	
		try
		{
			if(argc > 1)	//If user included parameters in program call
			{
				for(i = i + 1; i < argc; i++)	//Loop through args list
				{
					Statistics stats;	//Declare a new Statistics object for each loop
					if(isPositiveInteger(argv[i]))	//If argument is a positive integer
					{
						cout << "Solving 3n+1 - starting value: " << argv[i] << endl;
						stats.start = stoi(argv[i]);	//Set starting stat
						stats.max = stoi(argv[i]);		//Set max stat
						threeN(stoi(argv[i]), stats);	//Call recursive function on argument
						cout << endl;
						printStats(stats);				//Call function to print stats
					}
					else	//If argument is not a positive integer
					{
						cout << argv[i] << " is not a positive integer!\n\n";
					}
				}
			}
			else if(argc <= 1)	//If user did not included parameters in program call
			{
				string userInput;	//String to take in user input
				Statistics stats;	//Stat tracker object
				do	//Loop to error check user input until good input is detected (positive int)
				{
					cout << "Enter a 3n+1 candidate number: ";
					cin >> userInput;
					stats.start = stoi(userInput);
					if(isPositiveInteger(userInput))	//If user inputs a positive int
					{
						threeN(stoi(userInput), stats);	//Call recursive function
						cout << endl;
						printStats(stats);				//Call function to print stats
					}
					else	//If user input is bad
					{
						cout << "Please input a positive integer!\n\n";
					}
				}while(!isPositiveInteger(userInput));	//Loop until good input is received
				break;	//Break out of while loop and end program
			}
		}
		catch(int overflow)		//Oopsie whoopsie! Overflow was detected. 
		{
			cout << "->(###overflow###)\n\n"
				 << "overflow detected for n: " << overflow << endl
				 << "3n + 1: " << 3 * overflow + 1 << endl
				 << "something broke, dude\n"
				 << "overflow\n\n";
		}
	}

	return 0;
}

/****************************************************
* isPositiveInteger(string)
* return: bool
*
* Recieves a string from the user and returns true if
* string is a positive integer, false otherwise.
*****************************************************/
bool isPositiveInteger(string in)
{
	for(int i = 0; i < (int)in.length(); i++)	//Check each character in string
	{
		if(!isdigit(in[i]))
		{
			return false;
		}
	}
	return true;
}

/****************************************************
* isEven(int)
* return: bool
*
* Recieves an int and returns true if the int is even,
* false if it is odd.
*****************************************************/
bool isEven(int n)
{
	return n % 2 == 0;
}

/****************************************************
* threeN(int, Statistics&)
* return: void
*
* Recieves an int and a reference to a Statistics object,
* and uses recursion to test the Collatz conjecture.
* The statistics of the sequence are recorded in the
* Statistics object to be output later. The recursion
* ends when the function is passed an int value of 1.
*****************************************************/
void threeN(int n, Statistics& stats)
{
	cout << "->(" << n << ")";
	if(n > stats.max)	//If current n is larger than the max recorded in the Statistics object
	{
		stats.max = n;	//Set max to n
	}
	if(n != 1)	//If base case is not reached
	{
		stats.steps++;	//Increment steps stat
		if(isEven(n))	//If n is even
		{
			stats.evenCount += 1;	//Increment the number of evens stat
			threeN(n / 2, stats);	//Recursively call threeN, passing in (n / 2) as the next n
		}
		else	//If n is odd
		{	
			if(n > (INT_MAX / 3))	//If overflow is detected by checking that n is larger than (INT_MAX / 3)
			{
				throw n;	//Throw the int n to be caught in main
			}
			stats.oddCount += 1;		//Increment the number of odds stat if overflow is not detected 
			threeN(3 * n + 1, stats);	//Recursively call threeN, passing (3 * n + 1) as the next n
		}
	}	
}

/****************************************************
* outputStats(const Statistics)
* return: void
*
* Recieves a const Statistics object and prints its
* data members.
*****************************************************/
void printStats(const Statistics stats)
{
	cout << "start: " << stats.start << endl
		 << "steps: " << stats.steps << endl
		 << "max: "   << stats.max   << endl
		 << "odds: "  << stats.oddCount  << endl
		 << "evens: " << stats.evenCount << endl << endl; 
}
