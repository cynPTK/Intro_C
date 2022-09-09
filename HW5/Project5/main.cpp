//Created by Cynthia Nguyen
//CS31, Project 5, jitter.cpp

#pragma warning(disable : 6262)
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cassert>
#include <cstring>
using namespace std;

const int MAX_WORD_LENGTH = 20;
const int MAX_JEET_LENGTH = 280;

//moves Standard to the end
int MoveStandardsToEnd(char a[][MAX_WORD_LENGTH + 1],
    char b[][MAX_WORD_LENGTH + 1],
    int c[],
    int pos,
    const int size)
{
    if (pos == size - 1)
    {
        return pos;
    }

    int tempC = c[size - 1];//hold last element in temp string
    c[size - 1] = c[pos];//reassign last element with element at target position

    for (int i = pos; i < size - 1; i++)
    {
        c[i] = c[i + 1];//move all elements one place over to the left until the second to last element
    }

    c[size - 2] = tempC;//assign second to last element with what was originally the last element
    

    char tempA[MAX_WORD_LENGTH+1];//moves Cstring at pos to the end
    strcpy(tempA, a[size - 1]);
    strcpy(a[size - 1], a[pos]);
    if (strlen(a[size - 1]) < 19)
    {
        strcat(a[size - 1], "RM");//personal debug to easily see which standards got removed
    }
    else
    {
        strcpy(a[size - 1], "20RM");
    }

    for (int i = pos; i < size - 1; i++)
    {
            strcpy(a[i], a[i + 1]);
    }
        strcpy(a[size - 2], tempA);


    char tempB[MAX_WORD_LENGTH+1];//moves Cstring at pos to the end
    strcpy(tempB, b[size - 1]);
    strcpy(b[size - 1], b[pos]);
    if (strlen(a[size - 1]) < 19)
    {
        strcat(b[size - 1], "RM");//personal debeg to easily see which standards got removed
    }
    else
    {
        strcpy(b[size - 1], "20RM");
    }

    for (int i = pos; i < size - 1; i++)
    {
            strcpy(b[i], b[i + 1]);
    }
        strcpy(b[size - 2], tempB);

    return pos;
}

//returns number of standards in standard form
int editStandards(int distance[],
    char word1[][MAX_WORD_LENGTH + 1],
    char word2[][MAX_WORD_LENGTH + 1],
    int nStandards)
{
    if (nStandards < 1)
    {
        return 0;
    }

    //remove all instances where distance < 0, non letter characters in standard, and make all letters lowercase
    for (int i = 0; i < nStandards; i++)
    {
        int flag = 0;//prevent removing i multiple times
        if (distance[i] < 1 || strlen(word1[i]) < 1 || strlen(word2[i]) < 1)
        {
            MoveStandardsToEnd(word1, word2, distance, i, nStandards);
            nStandards--;
            i--;
            flag = 1;
        }

        if (flag == 0)
        {
            for (int j = 0; word1[i][j] != '\0'; j++)
            {
                if (!isalpha(word1[i][j]))
                {
                    MoveStandardsToEnd(word1, word2, distance, i, nStandards);
                    nStandards--;
                    i--;
                    flag = 1;
                    break;
                }
                else
                {
                    word1[i][j] = tolower(word1[i][j]);
                }
            }
        }

        if (flag == 0)
        {
            for (int j = 0; word2[i][j] != '\0'; j++)
            {
                if (!isalpha(word2[i][j]))
                {
                    MoveStandardsToEnd(word1, word2, distance, i, nStandards);
                    nStandards--;
                    i--;
                    break;
                }
                else
                {
                    word2[i][j] = tolower(word2[i][j]);
                }
            }
        }
    }

    //remove all instances were there is already a standard that matches word1 and word2
    for (int i = 0; i < nStandards; i++)
    {
        for (int j = i+1; j < nStandards; j++)
        {
            if (strcmp(word1[i], word1[j]) == 0 && strcmp(word2[i], word2[j]) == 0)
            {
                if (distance[i] < distance[j])
                {
                    MoveStandardsToEnd(word1, word2, distance, i, nStandards);
                    nStandards--;
                    i--;
                }
                else
                {
                    MoveStandardsToEnd(word1, word2, distance, j, nStandards);
                    nStandards--;
                }
            }
        }
    }

    return nStandards;
}

//removes non-alphabetic characters and make all letters lowercase
void Convert(char a[])
{
    char temp[MAX_JEET_LENGTH + 1];
    int j = 0;
    for (int i = 0; a[i] != '\0'; i++)
    {
        if (isalpha(a[i]) || a[i] == ' ')
        {
            temp[j] = tolower(a[i]);
            j++;
        }
    }

    temp[j] = '\0';//append null character
    strcpy(a, temp);

}

int determineMatchLevel(const int distance[],
                        const char word1[][MAX_WORD_LENGTH + 1],
                        const char word2[][MAX_WORD_LENGTH + 1],
                        int nStandards,
                        const char jeet[])
{
    int matchlevel = 0;

    if (nStandards < 1)//negative or 0 standards has 0 matches
    {
        return matchlevel;
    }

    //remove all nonalpha char from jeet, and make all alpha lowercase
    char convertjeet[MAX_JEET_LENGTH+1];
    strcpy(convertjeet, jeet);
    Convert(convertjeet);

    //create an array of the words of the jeet
    char seperated_jeet[MAX_JEET_LENGTH + 1][MAX_JEET_LENGTH + 1];
    int Cindex = 0;
    int numWords = 0;
    int SJindex = 0;

    while (convertjeet[Cindex] != '\0')
    {
        if (convertjeet[Cindex] == ' ')//iterates past spaces
        { 
            Cindex++;
        }

        while (isalpha(convertjeet[Cindex]) && convertjeet[Cindex] != '\0')//fills in array with words from jeet
        {
            seperated_jeet[numWords][SJindex] = convertjeet[Cindex];
            Cindex++;
            SJindex++;
        }
        seperated_jeet[numWords][SJindex] = '\0';//end each word with NULL
        numWords++;
        SJindex = 0;
    }

    //find match in jeet
    for (int i = 0; i < nStandards; i++)
    {
        int flag = 0;//break out of nested-loops when one match is found

        for (int j = 0; j < numWords-1; j++)//dont check last word for matches
        {
            if (strcmp(word1[i], seperated_jeet[j]) == 0)//find word1 in jeet
            {
                for (int k = 0; k <= distance[i] && j < numWords; k++)//within distance, find word2
                {
                    j++;

                    if (strcmp(word2[i], seperated_jeet[j]) == 0)
                    {
                        matchlevel++;
                        flag = 1;
                        break;
                    }
                }
            }

            if (flag == 1)//maintains one match per standard
            {
                break;
            }
        }
    }

    return matchlevel;
}

//for debugging purpose, print list of standards
void printStandards(int dist[], char word1[][MAX_WORD_LENGTH + 1], char word2[][MAX_WORD_LENGTH + 1], int nStandards)
{
    for (int i = 0; i < nStandards; i++)
    {
        cerr << dist[i] << " ";
        printf("%s", word1[i]);
        cerr << " ";
        printf("%s", word2[i]);
        cerr << endl;
    }
    cerr << endl;
}

int main()
{
    //basic test for all lowercase and no standard has both same w1 word and same w2 word
    const int Test0 = 7;
    int test0dist[Test0] = {
        2,             4,     1,           3,              2,       1,           13
    };
    char test0w1[Test0][MAX_WORD_LENGTH+1] = {
        "eccentric", "space", "ELECTRIC", "tunnel-boring", "space", "Electric", "were"
    };
    char test0w2[Test0][MAX_WORD_LENGTH+1] = {
        "billionare", "capsule", "CAR", "equipment", "capsule", "car", "eccentric"
    };

    assert(editStandards(test0dist, test0w1, test0w2, Test0) == 4);
    printStandards(test0dist, test0w1, test0w2, Test0);

    //tests negative distance is not standard form
    
    //testneg1
    int testneg1dist[Test0] = { -2, 4, 1, 3, 2, 1 ,13 };
    char testneg1w1[Test0][MAX_WORD_LENGTH + 1] = {
        "eccentric", "space", "ELECTRIC", "tunnel-boring", "space", "Electric", "were"
    };
    char testneg1w2[Test0][MAX_WORD_LENGTH + 1] = {
    "billionare", "capsule", "CAR", "equipment", "capsule", "car", "eccentric"
    };
    assert(editStandards(testneg1dist, testneg1w1, testneg1w2, Test0) == 3);
    printStandards(testneg1dist, testneg1w1, testneg1w2, Test0);

    //testneg2
    int testneg2dist[Test0] = { 2, 4, 1, 3, -2, 1, 13 };
    char testneg2w1[Test0][MAX_WORD_LENGTH + 1] = {
        "eccentric", "space", "ELECTRIC", "tunnel-boring", "space", "Electric", "were"
    };
    char testneg2w2[Test0][MAX_WORD_LENGTH + 1] = {
    "billionare", "capsule", "CAR", "equipment", "capsule", "car", "eccentric"
    };
    assert(editStandards(testneg2dist, testneg2w1, testneg2w2, Test0) == 4);
    printStandards(testneg2dist, testneg2w1, testneg2w2, Test0);

    //testneg3
    int testneg3dist[Test0] = { 2, 4, 1, 3, 2, 1, -13 };
    char testneg3w1[Test0][MAX_WORD_LENGTH + 1] = {
        "eccentric", "space", "ELECTRIC", "tunnel-boring", "space", "Electric", "were"
    };
    char testneg3w2[Test0][MAX_WORD_LENGTH + 1] = {
    "billionare", "capsule", "CAR", "equipment", "capsule", "car", "eccentric"
    };

    assert(editStandards(testneg3dist, testneg3w1, testneg3w2, Test0) == 3);
    printStandards(testneg3dist, testneg3w1, testneg3w2, Test0);
    
    //tests for words that are 20char long
    // and
    //test move first standard to end
    const int Test2 = 7;
    int test2dist[Test2] = {
        2,             4,     1,           3,              2,       1,           13
    };
    char test2w1[Test2][MAX_WORD_LENGTH + 1] = {
        "eccentric1", "spaceaaaaaaaaaaaaaa1", "ELECTRIC", "tunnel-boring", "space", "Electricaaaaaaaaaaaa", "were"
    };
    char test2w2[Test2][MAX_WORD_LENGTH + 1] = {
        "billionare", "capsule", "CAR", "equipment", "capsule", "car", "eccentric"
    };

    assert(editStandards(test2dist, test2w1, test2w2, Test2) == 4);// failed, out of boudns error, added flagsand break statements to solve
    printStandards(test2dist, test2w1, test2w2, Test2);
    
    //tests every word is at least one letter long
    const int Test3 = 7;
    int test3dist[Test3] = {
        2,             4,     1,           3,              2,       1,           13
    };
    char test3w1[Test3][MAX_WORD_LENGTH + 1] = {
        "eccentric", "", "ELECTRIC", "tunnel-boring", "space", "Electric", "were"
    };
    char test3w2[Test3][MAX_WORD_LENGTH + 1] = {
        "billionare", "capsule", "CAR", "equipment", "capsule", "car", "eccentric"
    };
    assert(editStandards(test3dist, test3w1, test3w2, Test3) == 4);// failed, did not remove the standard with no character; added if statement to solve
    printStandards(test3dist, test3w1, test3w2, Test3);

    //tests Convert function to remove all non apha chars
    char testA[MAX_JEET_LENGTH] = "I'm upset that on Apr. 29th, 2022, my 2 brand-new BMW i7s were stolen!!";
    Convert(testA);
    assert(strcmp(testA, "im upset that on apr th  my  brandnew bmw is were stolen") == 0);

    const int TEST1_NSTANDARDS = 4;
    int test1dist[TEST1_NSTANDARDS] = {
        2,             4,         1,         13
    };
    char test1w1[TEST1_NSTANDARDS][MAX_WORD_LENGTH + 1] = {
        "eccentric",   "space",  "electric", "were"
    };
    char test1w2[TEST1_NSTANDARDS][MAX_WORD_LENGTH + 1] = {
        "billionaire", "capsule", "car",     "eccentric"
    };

    assert(determineMatchLevel(test1dist, test1w1, test1w2, TEST1_NSTANDARDS,
        "The eccentric outspoken billionaire launched a space station cargo capsule.") == 2);//tests basic
    assert(determineMatchLevel(test1dist, test1w1, test1w2, TEST1_NSTANDARDS,
        "The eccentric outspoken billionaire launched    a space capsule.") == 2);//tests for multiple spaces
    assert(determineMatchLevel(test1dist, test1w1, test1w2, TEST1_NSTANDARDS,
        "**** 2022 ****") == 0);//tests for no letters
    assert(determineMatchLevel(test1dist, test1w1, test1w2, TEST1_NSTANDARDS,
        "  It's an ELECTRIC car!") == 1);//tests for uppercases
    assert(determineMatchLevel(test1dist, test1w1, test1w2, TEST1_NSTANDARDS,
        "space space capsule space capsule capsule") == 1);//test for multiple matches for one standard
    assert(determineMatchLevel(test1dist, test1w1, test1w2, TEST1_NSTANDARDS,
        "Two eccentric billionaires were space-capsule riders.") == 0);//tests words are broken up by spaces
    assert(determineMatchLevel(test1dist, test1w1, test1w2, TEST1_NSTANDARDS,
        "  i love space capsule and being eccentric  ") == 1); //tests for out of bounds if last word of jeet matches word1, and spaces at the beginning and end
    assert(determineMatchLevel(test1dist, test1w1, test1w2, TEST1_NSTANDARDS,
        " aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa") == 0);//tests 280 char
    assert(determineMatchLevel(test1dist, test1w1, test1w2, TEST1_NSTANDARDS,
        " aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa11111111111111111111111111111111111!!!!!!!!!!!!!!!!!!!!!!! two eccentric billionares were space-capsule riders It's am ELECTRIC car space space capsule space capsule capsule The eccentric outspoken billionare launced a space capsule") == 3);//tests for multiple standards in long jeet

    cerr << "All tests succeeded" << endl;
}