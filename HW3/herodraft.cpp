//Created by Cynthia Nguyen
//CS31, Project 3, hero.cpp

#include <iostream>
#include <string>
#include <cctype>
#include <cassert>
using namespace std;

const int twodigits = 2;
const int onedigit = 1;
const int onechar = 1;

//takes in a string and returns true or false if the string has the proper syntax
bool hasProperSyntax(string tune)
{
	if (tune == "")//empty string has proper syntax
	{
		return true;
	}
	else if (isdigit(tune.at(0)))//first char cant be digit
	{
		return false;
	}
	else if (tune.at(tune.size() - onechar) != '/')//last char has to be '/'
	{
		return false;
	}

	for (int i = 0; i < tune.size(); i++)
	{
		if (tune.at(i) != '/')//all '/' passes
		{
			if (isalpha(tune.at(i)))//checks if alphabet char is a note and follows with either a digit or a '/'
			{
				if (tolower(tune.at(i)) != 'g' &&
					tolower(tune.at(i)) != 'r' &&
					tolower(tune.at(i)) != 'y' &&
					tolower(tune.at(i)) != 'b' &&
					tolower(tune.at(i)) != 'o' ||
					(tune.at(i + 1) != '/' && !isdigit(tune.at(i + onechar)))
					)
				{
					return false;
				}
			}
			else if (isdigit(tune.at(i)))
			{
				if (tune.at(i - onechar) == '/')//checks if digit is after a note or digit
				{
					return false;
				}
				else if (isdigit(tune.at(i + onechar)))//checks that there is at most two digits after a note
				{
					if (tune.at(i + onedigit + onechar) != '/')
					{
						return false;
					}
				}
			}
			else//return false if char is not '/', alphabet, or digit
			{
				return false;
			}
		}
	}
	return true;
}

//takes in two digit characters as paramaters and converts them into their integer equivalent
int CharToInt(char digit1, char digit2)
{
	int tens = (digit1 - '0') * 10;
	int ones = digit2 - '0';
	int integer = tens + ones;
	return integer;
}

/*function appends uppercase note as sustained beat to the converted tune, or returns for badBeats
*param @ tunesubtr: substring of tune containing beats of sustained note
* param @ note: color of sustained note
* param @ Shold: number of beats of sustained note
* param @ Sconvertedtune: string on instructions that have been made
* param @ Sbear: int of how many beats have already been counted
* param @ sbadBeat: int of beat that does not successfully convert
*/
int SustainedNote(string tunesubstr, char note, int Shold, string& Sconvertedtune, int& Sbeat, int& SbadBeat)
{
	int holdcounter = 0;

	for (int j = 0; j < Shold; j++)
	{
		if (tunesubstr.at(j) == '/')
		{
			Sconvertedtune += toupper(note);
			Sbeat++;
			holdcounter++;
		}
		else
		{
			SbadBeat = ++Sbeat;
			return 2;
		}

		if ((j+1) == tunesubstr.size() && holdcounter < Shold)
		{
			SbadBeat = ++Sbeat;
			return 4;
		}
	}
	return 0;
}

//takes in a tune of proper syntax and converts it to a different syntax, or returns the beat at which the tune is not convertable
int convertTune(string tune, string& instructions, int& badBeat)
{
	if (!hasProperSyntax(tune))
	{
		return 1;
	}
	else
	{
		int beat = 0;
		string convertedtune;

		for (int i = 0; i < tune.size(); i++)//loop through every char in string
		{
			if (isalpha(tune.at(i)))//char at i is a note
			{
				if (!isdigit(tune.at(i + onedigit)))//runs as a regular note
				{
					convertedtune += tolower(tune.at(i));
					beat++;
					i++;//skip beat after the note
				}
				else//runs as a sustained note
				{
					int digits;
					int hold;
					string Sustained;

					if (isdigit(tune.at(i + twodigits)))//check if its a sustained note of two digits
					{
						hold = CharToInt(tune.at(i + onedigit) , tune.at(i + twodigits));//length of sustained note
						Sustained = tune.substr(i + twodigits + onechar, hold);//substring of beats after two digits
						digits = 2;

					}
					else//runs if sustained note only has one digit similarly to with two digits
					{
						hold = CharToInt('0', tune.at(i + onedigit ));
						Sustained = tune.substr(i + onedigit + onechar, hold);//substring of beats after one digit
						digits = 1;
					}

					if (hold < 2)//return 3 if hold is less than 2
					{
						badBeat = ++beat;
						return 3;
					}

					//checks if there is an accurate number of beats for each sustained note
					int returnSN = SustainedNote(Sustained, tune.at(i), hold, convertedtune, beat, badBeat);

					if (returnSN == 2)
					{
						return 2;//returns 2 if beat not consisting of only a slash is present
					}
					else if (returnSN == 4)
					{
						return 4;//if tune ends prematurely
					}

					i = i + digits + hold;//skip to after the sustained note
				}
			}
			else if (tune.at(i) == '/')//beat with no note
			{
				beat++;
				convertedtune += 'x';
			}
		}

		instructions = convertedtune;//if tuns properly, set instructions
		return 0;
	}
}


int main()
{
	//checks that returns true for proper syntax
	assert(hasProperSyntax("g/b//"));

	//checks for non note letters
	assert(!hasProperSyntax("g/z//"));

	//checks that every note is followed by a beat
	assert(hasProperSyntax("r/"));
	assert(!hasProperSyntax("r"));//cant check whats after the last char, solved by requiring last char == '/'

	//checks empty strings
	assert(hasProperSyntax(""));

	//checks digits needs to follow notes
	assert(hasProperSyntax("O3///b/"));
	assert(!hasProperSyntax("g/b/3/"));
	assert(hasProperSyntax("g/b3///"));
	assert(!hasProperSyntax("03///b/"));//cant check whats before first char, solved by requiring first char cant be digit

	//checks that max is two digits
	assert(!hasProperSyntax("g/b/b300/"));

	//checks that tune can consist of only '/'
	assert(hasProperSyntax("/"));

	//checks that both uppercase and lowercase are considered proper syntax
	assert(hasProperSyntax("G/b//O/y2//"));

	string instrs;
	int badb;
	badb = -999;  // so we can detect whether this gets changed
	instrs = "WOW";  // so we can detect whether this gets changed

	//checks if ChartoInt function succesfully converts digit characters of a string into integers
	string s = "g3///";
	assert(CharToInt('0', s.at(1)) == 3);
	assert(CharToInt('1', '0') == 10);

	//tests function SustainedNote to print out uppercase notes for number of beats its sustained
	string test;
	int beat = 0;
	assert(SustainedNote("///", 'g', 3, test, beat, badb) == 0 && test == "GGG" && beat == 3 && badb == -999);

	//tests that function returns 1 when propersyntax is false and instrs and badb remains the same
	instrs = "WOW";
	assert(convertTune("r", instrs, badb) == 1 && instrs == "WOW" && badb == -999);

	//checks badbeat outputs properly
	assert(convertTune("r/y3//g/r/", instrs, badb) == 2 && instrs == "WOW" && badb == 4);

	//checks for proper conversions to instructions
	badb = -999;
	assert(convertTune("r/o/g/y/", instrs, badb) == 0 && instrs == "rogy" && badb == -999);
	assert(convertTune("r//g/", instrs, badb) == 0 && instrs == "rxg" && badb == -999);
	assert(convertTune("g3///", instrs, badb) == 0 && instrs == "GGG" && badb == -999);
	assert(convertTune("g/G/g/B/", instrs, badb) == 0 && instrs == "gggb" && badb == -999);
	assert(convertTune("r//y/g3///o/", instrs, badb) == 0  && instrs == "rxyGGGo" && badb == -999);
	assert(convertTune("g3///B/", instrs, badb) == 0 && instrs == "GGGb" && badb == -999);//instrs == GGG/x; GGG/b changed i iteration -1;added else statement to 134, removed previous change, solved
	assert(convertTune("r/o/y10//////////g/r5/////", instrs, badb) == 0 && instrs == "roYYYYYYYYYYgRRRRR" && badb == -999);
	assert(convertTune("r/O/y10//////////g/r5/////", instrs, badb) == 0 && instrs == "roYYYYYYYYYYgRRRRR" && badb == -999);
	assert(convertTune("r/", instrs, badb) == 0 && instrs == "r" && badb == -999);
	assert(convertTune("r//", instrs, badb) == 0 && instrs == "rx" && badb == -999);
	assert(convertTune("//", instrs, badb) == 0 && instrs == "xx" && badb == -999);
	assert(convertTune("/", instrs, badb) == 0 && instrs == "x" && badb == -999);
	assert(convertTune("", instrs, badb) == 0 && instrs == "" && badb == -999);

	//tests for return 4 if beat ends prematurly
	badb = -999;
	instrs = "WOW";
	assert(convertTune("g3//", instrs, badb) == 4 && instrs == "WOW");//compile error, badbeat and the end of the tune leads to overflow; add if statement saying if last character and not reached number of beats in hold, return 4 and badbeat
		cerr << "All tests succeeded" << endl;
}