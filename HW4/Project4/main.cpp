//Created by Cynthia Nguyen
//CS31, Project 4, array.cpp

#include <iostream>
#include <string>
#include <cassert>
using namespace std;

//return number of strings in array equal to target
int enumerate(const string a[], int n, string target)
{
	if (n < 0)
	{
		return -1;
	}

	int counter = 0;

	for (int i = 0; i < n; i++)
	{
		if (a[i] == target)//count for every time target is matched
		{
			++counter;
		}
	}

	return counter;
}

//return position of a string in array equal to target
int findMatch(const string a[], int n, string target)
{
	if (n < 0)
	{
		return -1;
	}

	for (int i = 0; i < n; i++)
	{
		if (a[i] == target)
		{
			return i;//return position of target if found
		}
	}

 	return -1;//if target not found, return -1
}

//find earliest occurence in a of one or more constecutice string that are equal to the target, return false if target not found
bool findRun(const string a[], int n, string target, int& begin, int& end)
{
	if (n < 1)
	{
		return false;
	}

	for (int i = 0; i < n; i++)
	{
		if (a[i] == target)
		{
			begin = i;
			end = i;

			i++;
			while (a[i] == target)//k<n so that loop stops before we go out of bounds of array
			{
				end = i;
				i++;
			}

			return true;
		}
	}

	return false;
}

//return position of array such that string is <= every string in array
int findMin(const string a[], int n)
{
	if (n < 1)
	{
		return -1;
	}

	int minPos = 0;
	string minstring = a[0];

	for (int i = 0; i < n; i++)
	{
		if (a[i] < minstring)//reassign min to a[i] if a[i] is less than minstring, and reassign position of minimum
		{
			minstring = a[i];
			minPos = i;
		}
	}

	return minPos;
}

//moves string at pos to the end, and move all strings after string at pos over one place to the left
int moveToEnd(string a[], int n, int pos)
{
	if (n <= 0 || pos < 0 || pos > n-1)
	{
		return -1;
	}
	else if (n == 1 || pos == n - 1)//dont make changes if only one element in array or if pos is already at the end
	{
		return pos;
	}

	string temp = a[n - 1];//hold last element in temp string
	a[n - 1] = a[pos];//reassign last element with element at target position

	for (int i = pos; i < n - 1; i++)
	{
		a[i] = a[i + 1];//move all elements one place over to the left until the second to last element
	}

	a[n - 2] = temp;//assign second to last element with what was originally the last element

	return pos;
}

//moves string at pos to the end, and move all strings after string at pos over one place to the right
int moveToBeginning(string a[], int n, int pos)
{
	if (n <= 0 || pos < 0 || pos > n-1)
	{
		return -1;
	}
	else if (n == 1 || pos == 0)//dont make changes if only one element or if pos is already at the beginning
	{
		return pos;
	}

	string temp = a[0];//hold first element in temp string
	a[0] = a[pos];//reassign first element with target element

	for (int i = pos; i > 1; i--)
	{
		a[i] = a[i - 1];//move every element to the right, starting from position of target, ends before first element
	}

	a[1] = temp;//reassign second element with what was originally first element

	return pos;
}

//return pos at which two string arrays are different
int findDifference(const string a1[], int n1, const string a2[], int n2)
{
	if (n1 < 0 || n2 < 0)
	{
		return -1;
	}

	int iterations = n1;//only iterate up to last element of shortest array
	if (n1 > n2)
	{
		iterations = n2;
	}
	
	for (int i = 0; i < iterations ; i++)
	{
		if (a1[i] != a2[i])//return position of the difference
		{
			return i;
		}
	}

	return iterations;//if no difference, return length of shortest array
}

//removes duplicates in array string
int removeDups(string a[], int n)
{
	int bg;
	int en;
	int count = 0;

	if (n < 0)
	{
		return -1;
	}
	else if (n < 2)//no dupes in array of one element, prevents out of bounds
	{
		return 1;
	}

	for (int i = 0; i < n; i++)
	{
		findRun(a, n - i, a[0], bg, en);//find the run of first element for only the array of elements that has not been checked for duplicates

		if (en == n - i - 1)//if run all the way to the last element, move to element to and end loop
		{
			for (int j = 0; j <= en; j++)
			{
				moveToEnd(a, n, 0);
			}
			return ++count;
		}
		else if (bg != en)//if first element has duplicates, change all duplicates to the element after the run, move first element to the end
		{
			for (int k = 1; bg + k <= en; k++)
			{
				a[bg + k] = a[en + 1];
			}
			moveToEnd(a, n, 0);
			count++;
		}
		else//if first element has no duplicates, move element to the end
		{
			moveToEnd(a, n, 0);
			count++;
		}
	}
	return count;
}

//returns true if all elements of a2 is in a1 in the same order (not needed to be consecutive)
bool subsequence(const string a1[], int n1, const string a2[], int n2)
{
	if (n1 < 0 || n2 < 0)
	{
		return false;
	}

	int k = 0;

	for (int i = 0; i < n1 && k < n2; i++)
	{
		if (a1[i] == a2[k])
		{
			++k;//increment to next element everytime there is a match
		}
	}

	if (k >= n2 || n2 < 1)//if all a2 appear in a1 or if a2 has 0 elements, return true
	{
		return true;
	}

	return false;
}

//places all elements of a1 and a2 in result in nondecreasing order, return number of elements placed
int makeMerger(const string a1[], int n1, const string a2[], int n2, string result[], int max)
{
	if (n1 < 0 || n2 < 0 || max < 0 || n1 + n2 > max)//n1 + n2 has to be less than max
	{
		return -1;
	}

	for (int i = 0; i < n1 - 1; i++)//checks a1 is in nondecreaseing order
	{
		if (a1[i] > a1[i + 1])
		{
			return -1;
		}
	}

	for (int i = 0; i < n2 - 1; i++)//checks a2 is in nondecreasing order
	{
		if (a2[i] > a2[i + 1])
		{
			return -1;
		}
	}

	int j = 0;
	int k = 0;
	int iteration = n1 + n2;
	
	for (int i = 0; i < iteration; i++)
	{
		if (k == n2)//last element of a2, only append a1
		{
			result[i] = a1[j];
				j++;
		}
		else if (j == n1)//last element of a1, only append a2
		{
			result[i] = a2[k];
				k++;
		}
		else if (a1[j] <= a2[k])//a1 <= a2, append a1
		{
			result[i] = a1[j];
				j++;
		}
		else if (a1[j] > a2[k])//a1 > a2, append a2
		{
			result[i] = a2[k];
				k++;
		}
	}

	return iteration;
}

// rearraneg so that all elements < divide comes before divider, and > divider comes after divider
int divide(string a[], int n, string divider)
{
	if (n < 0)
	{
		return -1;
	}
	for (int i = 0; i < n; i++)
	{
		if (a[i] > divider)
		{
			moveToEnd(a, n, i);//move strings greater than divider to end, loop for position i again, decrease n to prevent looping for the same element again
			i--;
			n--;
		}
		else if (a[i] < divider)
		{
			moveToBeginning(a, n, i);//move to beginning strings less than divider
		}
	}//divider does not move, thus ends up in the middle

	for (int i = 0; i < n; i++)
	{
		if (a[i] >= divider)//return position of first element not < divider
		{
			return i;
		}
	}

	return n;//return length of array if nothing is greater than divider
}

//prints array for debugging purposes
void printArray(const string a[], int n)
{
	for (int i = 0; i < n; i++)
	{
		cerr << a[i] << ' ';
	}
	cerr << endl;
}

int main()
{
	//test enumarate function
	string h[7] = { "neil", "sonia", "john", "amy", "", "elena", "john" };
	assert(enumerate(h, 7, "john") == 2);
	assert(enumerate(h, 7, "") == 1);
	assert(enumerate(h, 7, "brett") == 0);//test for if name does not show up in array
	assert(enumerate(h, 0, "john") == 0);//test for empty array
	assert(enumerate(h, 3, "john") == 1);//test for segment of array

	//test findMatch
	assert(findMatch(h, 7, "john") == 2);
	assert(findMatch(h, 2, "john") == -1);//test for segment of array

	//test find Run
	int bg;
	int en;
	findRun(h, 7, "amy", bg, en);
	assert(findRun(h, 7, "amy", bg, en) && bg == 3 && en == 3);//test for single run

	string test1[9] = { "neil", "sonia", "john", "amy", "amy" , "amy" , "" , "elena", "john" };
	assert(findRun(test1, 9, "amy", bg, en) == 1 && bg == 3 && en == 5);//test for longer run
	assert(findRun(test1, 9, "cynthia", bg, en) == 0);//test for if target is not found, return false
	assert(findRun(test1, 1, "neil", bg, en) == 1);//test no out of bounds error
	assert(findRun(test1, 1, "cynthia", bg, en) == 0);//test no out of bounds error

	//test findMin
	string g[4] = { "neil", "sonia", "amy", "elena" };
	assert(findMin(g, 4) == 2);//tests basic functionality
	//return 3 instead of 2, forgot to reassign minstring to a[i]

	//test findDifference
	assert(findDifference(h, 4, g, 4) == 2);//checks basic funcitonality
	string people[5] = { "john", "sonia", "samuel", "elena", "neil" };
	string bench[6] = { "john", "sonia", "clarence", "elena", "neil", "samuel" };
	assert(findDifference(people, 5, bench, 6) == 2);//checks basic functionality
	assert(findDifference(people, 2, bench, 1) == 1);//checks if no difference, different length
	assert(findDifference(people, 2, bench, 2) == 2);//checks for no difference, same length

	//test subsequence
	assert(subsequence(h, 7, g, 4) == 1);//checks return true

	string big[10] = { "elena", "john", "amy", "ketanji", "neil", "amy" };
	string little1[10] = { "john", "ketanji", "neil" };
	assert(subsequence(big, 6, little1, 3) == 1);//checks return true
	string little2[10] = { "amy", "john" };
	assert(subsequence(big, 6, little2, 2) == 0);//checks return false if out of order
	string little3[10] = { "john", "amy", "amy" };
	assert(subsequence(big, 6, little3, 3) == 1); //checks return true for multiple of same string
	string little4[10] = { "john", "john", "amy" };
	assert(subsequence(big, 6, little4, 3) == 0); //checks return false for two of same string
	assert(subsequence(big, 6, little4, 0) == 1);//output true for empty array
	string little5[10] = { "john", "amy" };
	assert(subsequence(big, 6, little5, 2) == 1);//checks that multiple of the same name does not cause issues

	//test moveToEnd
	cerr << "move to end" << endl;

	assert(moveToEnd(g, 4, 1) == 1 && g[1] == "amy" && g[3] == "sonia");//checks basic functionality
	printArray(g, 4);

	cerr << endl;

	//test moveToBeginning
	cerr << "move to beginning" << endl;
	string f[4] = { "elena", "amy", "sonia", "john" };
	assert(moveToBeginning(f, 4, 2) == 2 && f[0] == "sonia" && f[2] == "amy");//tests for basic functionality; failed, was moving strings to the right starting from 0 result in same string copied over and over; solved, move to the right starting from pos
	printArray(f, 4);
	cerr << endl;

	//test removeDups
	cerr << "remove dupes" << endl;

	string e[5] = { "elena", "elena", "elena", "sonia", "sonia" };
	assert(removeDups(e, 5) == 2 && e[1] == "sonia");//tests for basic functionality
	printArray(e, 5);

	string d[9] = { "clarence", "neil", "amy", "amy", "ketanji", "ketanji", "ketanji", "amy", "amy" };//test for basic functionality; failed having two amy's cause issues cause findRun locates the first amy, not the second run of amy, solved by using moveToEnd function and findRun for segment of array

	assert(removeDups(d, 9) == 5 && d[3] == "ketanji");
	printArray(d, 9);

	string test2[11] = { "clarence", "neil", "amy", "amy", "ketanji", "ketanji", "ketanji", "amy", "amy", "ketanji", "ketanji" };//test for multiple dupes of same string
	assert(removeDups(test2, 11) == 6 && d[3] == "ketanji");
	printArray(test2, 11);

	string test4[2] = { "sonia", "amy" };//tests 2 elements that arent dupes if go out of bounds of array
	assert(removeDups(test4, 2) == 2);
	printArray(test4, 2);
	string test5[2] = { "sonia", "sonia" };//tests 2 elements that are dupes if go out of bounds
	assert(removeDups(test5, 2) == 1);
	printArray(test5, 2);

	cerr << endl;

	//test for makeMerger
	cerr << "make merger" << endl;

	string x[4] = { "john", "john", "samuel", "sonia" };
	string y[4] = { "amy", "elena", "john", "ketanji" };
	string z[10];

	assert(makeMerger(x, 4, y, 4, z, 10) == 8 && z[5] == "ketanji");//test basic functionality
	printArray(z, 10);

	string x1[5] = { "amy", "elena", "elena", "ketanji", "samuel" };
	string y1[4] = { "clarence", "elena", "john", "sonia" };
	string z1[20];
	assert(makeMerger(x1, 5, y1, 4, z1, 20) == 9);//test basic functionality
	printArray(z1, 9);
	cerr << endl;

	//test for divide
	cerr << "divide" << endl;
	string test3[7] = { "niel", "sonia", "john", "amy", "", "elena", "john" };
	moveToEnd(test3, 7, 6);//testing moveToEnd for use in divide function
	cout << "test3" << " ";
	printArray(test3, 7);

	assert(divide(h, 7, "john") == 3);//tests basic functionality, failed, when moving a character to the end, we skip the check for the character next to it, solved by adding i--; and n--; to if statement for >divider
	printArray(h, 7);

	string sc2[4] = { "john", "sonia", "amy", "neil" };
	assert(divide(sc2, 4, "neil") == 2);//tests basic functionality
	printArray(sc2, 4);

	string sc[6] = { "john", "amy", "samuel", "elena", "sonia", "neil" };
	assert(divide(sc, 6, "ketanji") == 3);//tests basic functionality
	printArray(sc, 6);
	cerr << endl;

	//test for negative n values
	assert(enumerate(h, -1, "john") == -1);
	assert(findMatch(h, -1, "john") == -1);
	assert(findRun(h, -1, "john", bg, en) == 0);
	assert(findMin(h, -1) == -1);
	assert(moveToEnd(h, -1, 0) == -1);
	assert(moveToEnd(h, 0, -1) == -1);
	assert(moveToBeginning(h, -1, 0) == -1);
	assert(moveToBeginning(h, 0, -1) == -1);
	assert(findDifference(h, -1, g, 0) == -1);
	assert(findDifference(h, 0, g, -1) == -1);
	assert(removeDups(h, -1) == -1);
	assert(subsequence(h, -1, g, 0) == 0);
	assert(subsequence(h, 0, g, -1) == 0);
	assert(makeMerger(h, -1, g, 0, f, 0) == -1);
	assert(makeMerger(h, 0, g, -1, f, 0) == -1);
	assert(makeMerger(h, 0, g, 0, f, -1) == -1);
	assert(divide(h, -1, "john") == -1);

	cerr << "All tests succeeded" << endl;
}