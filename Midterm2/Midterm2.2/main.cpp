//Created by Cynthia Nguyen
//Midterm 2.2

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cassert>
using namespace std;

using namespace std;

const int NEG_N = -3;
const int BAD_CHANGE = -2;
const int NEG_LEAD = -1;
const int INITIAL_LEAD = 30;

int interpret(const int changes[], int n, int& maxLead)
{
	const int OG_MAX_LEAD = maxLead;

	if (n < 1)
	{
		return NEG_N;
	}

	int lead = INITIAL_LEAD;

	for (int i = 0; i < n; i++)
	{
		if (changes[i] < -15 || changes[i] > 15)
		{
			maxLead = OG_MAX_LEAD;
			return BAD_CHANGE;
		}

		lead += changes[i];

		if (lead < 0)
		{
			maxLead = OG_MAX_LEAD;
			return NEG_LEAD;
		}
		else if (lead > maxLead)
		{
			maxLead = lead;
		}
	}

	return lead;
}

int main()
{
	int chg1[13] = { 5, 2, 0, -3, 6, 2, -4, 0, 0, -5, -5, 1, -8 };
	int m;
	assert(interpret(chg1, 13, m) == 21);
	assert(m == 42);

	int chg2[7] = { 0, 2, -12, -9, -13, 10, 10 };
	m = 999;
	assert(interpret(chg2, 7, m) == -1);
	assert(m == 999);

	int chg3[3] = { 10, 20, 10 };
	m = 999;
	assert(interpret(chg3, 3, m) == -2);
	assert(m == 999);

	assert(interpret(chg3, -1, m) == -3);
	assert(m == 999);

	cout << "All tests succeeded" << endl;
}