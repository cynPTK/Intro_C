#include <iostream>
#include <string>
#include <cassert>
using namespace std;

// SUBMIT AS YOUR ANSWER ONLY THE CODE BETWEEN THIS COMMENT AND THE
// COMMENT AT THE END OF THE biggie FUNCTION

string* biggie(string* first, string* last, int* numEmpty)
{
    int maxlength = last->length();
    string* ptr = last;
    int empty;

    if (numEmpty != nullptr)
    {
        empty = 0;
    }

    if (first == last)
    {
        if (first->length() == 0)
        {
            *numEmpty = 1;
            return first;
        }
        else
        {
            *numEmpty = 0;
            return first;
        }
    }

    while (first != last + 1)
    {
        if (numEmpty != nullptr && first->length() == 0)
        {
            empty++;
        }

        if (first->length() >= maxlength)
        {
            ptr = first - 1;
        }

        first++;
    }

    if (numEmpty != nullptr)
    {
        *numEmpty = empty;
    }

    return ptr;
}

// SUBMIT AS YOUR ANSWER ONLY THE CODE BETWEEN THIS COMMENT AND THE
// COMMENT AT THE START OF THE biggie FUNCTION

int main()
{
    string a[9] = { "cat", "", "mouse", "", "", "fish", "dog", "bunny", "bird" };
    int empties = 999;
    assert(biggie(a, a + 4, &empties) == a + 2 && empties == 2);
    assert(biggie(a + 5, a + 8, &empties) == a + 7 && empties == 0);
    empties = 888;
    assert(biggie(a, a + 3, nullptr) == a + 2 && empties == 888);
    assert(biggie(a, a + 7, &empties) == a + 7 && empties == 3);
    assert(biggie(a + 1, a + 1, &empties) == a + 1 && empties == 1);
    assert(biggie(a, a, &empties) == a && empties == 0);

    cout << "All tests succeeded" << endl;
}