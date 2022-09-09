//Created by Cynthia Nguyen
//Project 2, bill.cpp, CS31

#include <iostream>
#include <string>

using namespace std;

int main()
{
	//initial meter reading final meter reading, usage, month number
	int IMR, FMR, month, usage;
	
	string name;
	const double tier_1_rate = 5.41;//both high and low
	const double tier_2_rate_high = 9.79;
	const double tier_2_rate_low = 7.77;
	double amount;

	cout << "Initial meter reading: ";
	cin >> IMR;

	cout << "Final meter reading: ";
	cin >> FMR;
	cin.ignore(10000, '\n');//cant read numbers before getline strings, solves issue
	
	usage = FMR - IMR;

	cout << "Customer name: ";
	getline(cin, name);

	cout << "Month number (1=Jan, 2=Feb, etc.): ";
	cin >> month;

	//calculates the bill in a high sesaon
	if (month >= 4 && month <= 10)
	{
		//calculates the bill depending on if the usage is more or less than 23
		if (usage > 23.0)
		{
			amount = tier_1_rate * 23.0 + tier_2_rate_high * (usage - 23.0);
		}
		else
		{
			amount = tier_1_rate * usage;
		}
	}
	
	//calculates the bill in a low season
	else
	{
		//calculates the bill depending on if the usage is more or less than 15
		if (usage > 15.0)
		{
			amount = tier_1_rate * 15.0 + tier_2_rate_low * (usage - 15.0);
		}
		else
		{
			amount = tier_1_rate * usage;
		}
	}

	cout << "---" << endl;

	if (IMR < 0)//initial meter reading is negative
	{
		cout << "The initial meter reading must not be negative." << endl;
	}
	else if (FMR < IMR)//final meter reading is less than inital meter reading
	{
		cout << "The final meter reading must be at least as large as the initial reading." << endl;
	}
	else if (name == "")//name is an empty string
	{
		cout << "You must enter a customer name." << endl;
	}
	else if (month < 1 || month > 12)//month is not within 1-12 range
	{
		cout << "The month number must be in the range 1 through 12." << endl;
	}
	else//no errors are encountered
	{
		cout.setf(ios::fixed);
		cout.precision(2);

		cout << "The bill for " << name << " is $" << amount << endl;
	}
	
	return 0;
}
