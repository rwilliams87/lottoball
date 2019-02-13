
#include "pch.h"
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <string>
#include <time.h>

using namespace std; //So I can use 'string' instread of 'std::string'. 

//Let's declare some variables.
string inputA, inputB, inputC, inputD, inputE, inputF, powerballPrint;
int a, b, c, d, e, f;
int finalA, finalB, finalC, finalD, finalE, finalF = 0;
int drawA, drawB, drawC, drawD, drawE, drawF = 0;
int numbersMatched = 0;
int powerballMatched = 0;
int numErrors, rangeErrors;
int moneySpent, moneyWon = 0;
unsigned int totalTries = 0;
unsigned int winnings = 0;
unsigned int totalWinnings = 0;

//Number Range Errors - String Text
string error1 = "You must enter a number between 1-69. ";
string error2 = "Powerball numbers must be between 1-29. ";
string error3 = "I don't think you know how to play the lottery. ";

//Duplicate number errors - String Text
string error4 = "You can't enter the same number twice. ";
string error5 = "Dude...you can't enter the same number twice. ";
string error6 = "Seriously? You can't enter the same number twice! Pick a DIFFERENT number!";

//Function to decide which error code to throw out.
void sameNumError() {
	if (numErrors < 3) { cout << error4 << endl; }
	if (numErrors >= 3 && numErrors < 10) { cout << error5 << endl; }
	if (numErrors >= 10) { cout << error6 << endl; }
}

void isRangeError() {
	if (rangeErrors < 10) { cout << error1 << endl; }
	if (rangeErrors >= 10) { cout << error3 << endl; }
}

void isRangeErrorF() {
	if (rangeErrors < 10) { cout << error2 << endl; }
	if (rangeErrors >= 10) { cout << error3 << endl; }
}

//Function to check for duplicate numbers, on entries b through e.
void isDuplicateB() { if (b == a) { sameNumError(); numErrors++; } }
void isDuplicateC() { if (c == a || c == b) { sameNumError(); numErrors++; } }
void isDuplicateD() { if (d == a || d == b || d == c) { sameNumError(); numErrors++; } }
void isDuplicateE() { if (e == a || e == b || e == c || e == d) { sameNumError(); numErrors++; } }

//Function to check for range errors, on entries a through e.
//Note: I should probably make 1 & 69 variables too that we can change, so I can use this to play mega millions, etc. 
void checkRangeError(int x) { if (x < 1 || x > 69) { isRangeError(); rangeErrors++; } }

//Function to check for range errors, on powerball entry.
void checkRangeErrorF(int x) { if (x < 1 || x > 26) { isRangeErrorF(); rangeErrors++; } }

//Function for number formatting. Adds a 0 for single digit numbers. 
void spacer(int n) {
	if (n < 10) { cout << "0" << n << " "; }
	else { cout << n << " "; }
}


int main()
{

	srand(time(0));

	//Introduction Text.
	cout << "Ryan's Lottery Simulator!" << endl;
	cout << "This is where some cool subtext would go, like in Minecraft." << endl;
	cout << endl;
	cout << "You will need to enter 5 lottery numbers between 1-69, then a final powerball number between 1-26." << endl;
	cout << endl;


	//There are 5 lottery numbers (a, b, c, d, e) and one powerball number (f).
	//(a, b, c, d, e) must be between 1-69, and be unique numbers. (f) must be between 1-26.
	//This collects the input as a STRING, using stringstream, then >>'s that to an int. Why? Because checking INTs are fucking impossible in this language.

	//First Lottery Number (a). Makes sure it's in range (1-69).
	do {
		cout << "Please enter your first lottery number: ";
		cin >> inputA;
		stringstream getA(inputA);
		getA >> a;
		checkRangeError(a);
	} while (a > 69 || a < 1);

	//Second Lottery Number (b). This one checks to see if it's the same value as a. Makes sure it's in range (1-69).
	do {
		cout << "Please enter your second lottery number: ";
		cin >> inputB;
		stringstream getB(inputB);
		getB >> b;
		checkRangeError(b);
		isDuplicateB();
	} while (b > 69 || b < 1 || b == a);

	//Third Lottery Number (c). Checks if it's the same value as a or b. Makes sure it's in range (1-69).
	do {
		cout << "Please enter your third lottery number: ";
		cin >> inputC;
		stringstream getC(inputC);
		getC >> c;
		checkRangeError(c);
		isDuplicateC();
	} while (c > 69 || c < 1 || c == a || c == b);

	//Fourth Lottery Number (d). Checks to see if it's the same value as a, b, or c. Makes sure it's in range (1-69).
	do {
		cout << "Please enter your fourth lottery number: ";
		cin >> inputD;
		stringstream getD(inputD);
		getD >> d;
		checkRangeError(d);
		isDuplicateD();
	} while (d > 69 || d < 1 || d == a || d == b || d == c);

	//Fifth Lottery Number (e). Checks to see if it's the same value as a, b, c, or d. Makes sure it's in range (1-69).
	do {
		cout << "Please enter your fifth lottery number: ";
		cin >> inputE;
		stringstream getE(inputE);
		getE >> e;
		checkRangeError(e);
		isDuplicateE();
	} while (e > 69 || e < 1 || e == a || e == b || e == c || e == d);

	//Powerball number. We don't need to check if it's a duplicate of a b c d or e, powerball is it's own thing. Checks for range.
	do {
		cout << "Please enter your powerball number: ";
		cin >> inputF;
		stringstream getF(inputF);
		getF >> f;
		checkRangeErrorF(f);
	} while (f > 26 || f < 1);

	//After picking your numbers...
	cout << endl;
	cout << endl;
	cout << "You picked: ";
	spacer(a);
	spacer(b);
	spacer(c);
	spacer(d);
	spacer(e);
	spacer(f);
	cout << endl;
	cout << endl;
	system("pause"); //This works in Windows only...

	//Draw random numbers. Putting this in a 'do' loop, so after all numbers are drawn, if any number does NOT equal your entered numbers, it redraws them forever.
	//Individual numbers are also in a 'do' loop, so if a is drawn to be 17, then b is drawn to be 17, b re-draws until it is not 17.
	//The if / else sets the 'draw' flag to 1 or 0. 1 if the number matches one of your numbers, 0 if it doesn't. Protip: It probably doesn't.


	do {

		//Let's make it acutally random this time. 

		


		finalA = rand() % 69 + 1;
		if (finalA == a || finalA == b || finalA == c || finalA == d || finalA == e) {
			drawA = 1;
		}
		else { drawA = 0; }
		do {
			finalB = rand() % 69 + 1;
			if (finalB == a || finalB == b || finalB == c || finalB == d || finalB == e) {
				drawB = 1;
			}
			else { drawB = 0; }
		} while (finalB == finalA);

		do {
			finalC = rand() % 69 + 1;
			if (finalC == a || finalC == b || finalC == c || finalC == d || finalC == e) {
				drawC = 1;
			}
			else { drawC = 0; }
		} while (finalC == finalA || finalC == finalB);

		do {
			finalD = rand() % 69 + 1;
			if (finalD == a || finalD == b || finalD == c || finalD == d || finalD == e) {
				drawD = 1;
			}
			else { drawD = 0; }
		} while (finalD == finalA || finalD == finalB || finalD == finalC);

		do {
			finalE = rand() % 69 + 1;
			if (finalE == a || finalE == b || finalE == c || finalE == d || finalE == e) {
				drawE = 1;
			}
			else { drawE = 0; }
		} while (finalE == finalA || finalE == finalB || finalE == finalC || finalE == finalD);

		//Powerball!
		finalF = rand() % 26 + 1;
		if (finalF == f) {
			drawF = 1;
		}
		else { drawF = 0; }






		//Get the amount of correct numbers matched, a - e. Just the first 5 numbers.
		numbersMatched = drawA + drawB + drawC + drawD + drawE;

		//Calculate how many draws we've done, and how much money you spent:
		totalTries++;
		moneySpent = totalTries * 2;


		//Let's display some output.

		//Display what draw # this is. Format spaces after draws, so columns do not move when digits are added to the draw number.
		//The formatting here is a goddamned waste of memory, there's totally a better way to do this by like...counting the size of 'totalTries' or some shit.
		cout << "Draw #: " << totalTries;
		if (totalTries < 10) { cout << "          "; }
		if (totalTries >= 10 && totalTries < 100) { cout << "         "; }
		if (totalTries >= 100 && totalTries < 1000) { cout << "        "; }
		if (totalTries >= 1000 && totalTries < 10000) { cout << "       "; }
		if (totalTries >= 10000 && totalTries < 100000) { cout << "      "; }
		if (totalTries >= 100000 && totalTries < 1000000) { cout << "     "; }
		if (totalTries >= 1000000 && totalTries < 10000000) { cout << "    "; }
		if (totalTries >= 10000000 && totalTries < 100000000) { cout << "   "; }
		if (totalTries >= 100000000 && totalTries < 1000000000) { cout << "  "; }
		if (totalTries >= 1000000000 && totalTries < 10000000000) { cout << " "; }

		//Space
		cout << "   ";

		//Display the numbers picked randomly.
		spacer(finalA);
		spacer(finalB);
		spacer(finalC);
		spacer(finalD);
		spacer(finalE);
		spacer(finalF);

		//Space
		cout << "  ";

		//Display which numbers were matched:
		if (drawA == 1) { cout << "[x]"; }
		else { cout << "[ ]"; }



		if (drawB == 1) { cout << "[x]"; }
		else { cout << "[ ]"; }



		if (drawC == 1) { cout << "[x]"; }
		else { cout << "[ ]"; }



		if (drawD == 1) { cout << "[x]"; }
		else { cout << "[ ]"; }



		if (drawE == 1) { cout << "[x]"; }
		else { cout << "[ ]"; }



		if (drawF == 1) { cout << "[x]"; }
		else { cout << "[ ]"; }

		//Space
		cout << "   ";

		//Print the amount of white balls picked. Add a +P! if the powerball is also picked. 
		if (drawF == 1) { cout << "Matched: " << numbersMatched << "+P!"; }
		else { cout << "Matched: " << numbersMatched << "   "; }

		//Space
		cout << "   ";

		//Display Money Spent
		cout << "Spent: $" << moneySpent;

		//Space
		cout << "   ";

		//Calculate Winnings!
		//Non-Powerball Winnings:
		if (drawF == 0) {
			if (numbersMatched == 0) { winnings = 0; }
			if (numbersMatched == 1) { winnings = 0; }
			if (numbersMatched == 2) { winnings = 0; }
			if (numbersMatched == 3) { winnings = 4; }
			if (numbersMatched == 4) { winnings = 100; }
			if (numbersMatched == 5) { winnings = 1000000; }
		}
		//Powerball Winnings:
		if (drawF == 1) {
			if (numbersMatched == 0) { winnings = 4; }
			if (numbersMatched == 1) { winnings = 4; }
			if (numbersMatched == 2) { winnings = 7; }
			if (numbersMatched == 3) { winnings = 100; }
			if (numbersMatched == 4) { winnings = 50000; }
			//Omit Match5 + Powerball, as the loop stops when that happens.
		}

		//Display Winnings
		cout << "Won: $" << winnings;

		//Space
		cout << "   ";

		//Calculate Total Winnings
		totalWinnings = totalWinnings + winnings;

		//Display Total Winnings
		cout << "Total Win: $" << totalWinnings;

		//End the line, reset matched numbers.
		cout << endl;
		numbersMatched = 0;







		//This here 'while' makes it keep drawing until you win. Good luck...
	} while (drawA != 1 || drawB != 1 || drawC != 1 || drawD != 1 || drawE != 1 || drawF != 1);

	//What to do when you won:

	totalWinnings = totalWinnings + 100000000;
	cout << endl;
	cout << endl;
	cout << endl;
	cout << "You won the lottery! You're a millionaire! Congratulations on your 100 MILLION dollar jackpot! Too bad it's not real!";
	cout << endl;
	cout << endl;
	cout << "Total Tries: " << totalTries << "     " << "Total Spent: " << moneySpent << "     " << "Money Won: $" << totalWinnings;
	system("pause");


	//End of Program.
	return 0;
}