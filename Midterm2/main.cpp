//Created by Cynthia Nguyen
//Midterm2

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <cctype>
#include <cassert>
using namespace std;

using namespace std;

int obscure(char s[], char ch)
{
	int count = 0;
	for (int i = 0; s[i] != '\0'; i++)
	{
		if (!islower(s[i]) && !isdigit(s[i]))
		{
			s[i] = ch;
			count++;
		}
	}
    return count;
}


int main()
{
    char text[100] = "I'm UPSET that on Apr. 29th, 2022, my 2 brand-new BMW i7s were stolen!!";
    assert(obscure(text, '*') == 30);
    assert(strcmp(text, "**m*******that*on**pr**29th**2022**my*2*brand*new*****i7s*were*stolen**") == 0);

    strcpy(text, "#%@!");
    assert(obscure(text, 'x') == 4);
    assert(strcmp(text, "xxxx") == 0);

    strcpy(text, "73kg");
    assert(obscure(text, '?') == 0);
    assert(strcmp(text, "73kg") == 0);

    strcpy(text, "");
    assert(obscure(text, '-') == 0);
    assert(strcmp(text, "") == 0);

    cout << "All tests succeeded" << endl;
}