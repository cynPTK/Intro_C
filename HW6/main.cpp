//Created by Cynthia Nguyen
//Project 6

#include <iostream>
#include <cmath>
using namespace std;

//1

//int main()
//{
//    int arr[3] = { 5, 10, 15 };
//    int* ptr = arr;
//
//    *ptr = 10;          // set arr[0] to 10
//    *(ptr + 1) = 20;      // set arr[1] to 20
//    ptr += 2;
//    ptr[0] = 30;        // set arr[2] to 30
//
//    while (ptr >= arr)
//    {
//        cout << ' ' << *ptr;    // print values
//        ptr--;
//    }
//    cout << endl;
//}

//void finddisorder(int arr[], int n, int*& p)
//{
//    for (int k = 1; k < n; k++)
//    {
//        if (arr[k] < arr[k - 1])
//        {
//            p = arr + k;
//            return;
//        }
//    }
//    p = nullptr;
//}
//
//int main()
//{
//    int nums[6] = { 10, 20, 20, 40, 30, 50 };
//    int* ptr = &nums[0];
//
//    finddisorder(nums, 6, ptr);
//    if (ptr == nullptr)
//        cout << "the array is ordered" << endl;
//    else
//    {
//        cout << "the disorder is at address " << ptr << endl;
//        cout << "it's at position " << ptr - nums << endl;
//        cout << "the item's value is " << *ptr << endl;
//    }
//}

//void hypotenuse(double leg1, double leg2, double* resultPtr)
//{
//    *resultPtr = sqrt(leg1 * leg1 + leg2 * leg2);
//}
//
//int main()
//{
//    double x;
//    double* p = &x;
//    hypotenuse(1.5, 2.0, p);
//    cout << "The hypotenuse is " << *p << endl;
//}

//      // return true if two c strings are equal
//bool match(const char str1[], const char str2[])
//{
//    while (*str1 != 0 && *str2 != 0)  // zero bytes at ends
//    {
//        if (*str1 != *str2)  // compare corresponding characters
//            return false;
//        str1++;            // advance to the next character
//        str2++;
//    }
//    return *str1 == *str2;   // both ended at same time?
//}
//
//int main()
//{
//    char a[10] = "cynthia";
//    char b[10] = "cynthia";
//
//    if (match(a, b))
//        cout << "they're the same!\n";
//    else
//        cout << "not the same!\n";
//}

//int* computeSquares(int& n)
//{
//    static int arr[10];
//    n = 10;
//    for (int k = 0; k < n; k++)
//    {
//        arr[k] = (k + 1) * (k + 1);
//    }
//    return arr;
//}
//
//void f()
//{
//    int junk[100];
//    for (int k = 0; k < 100; k++)
//    {
//        junk[k] = 123400000 + k;
//    }
//}
//
//int main()
//{
//    int m;
//    int* ptr = computeSquares(m);
//    f();
//    for (int i = 0; i < m; i++)
//        cout << ptr[i] << ' ';
//}

//2

//int main()
//{
//	string* fp;
//	string fish[5] = {"smelt", "test", "test", "test", "test"};
//	fp = &fish[4];
//	*fp = "yellowtail";
//	 *(fish + 3) = "salmon";
//	fp -= 3;
//	fp[1] = "carp";
//	fp[0] = "smelt";
//
//	bool d;
//	if (fp == &fish[0])
//	{
//		d = true;
//	}
//	else
//	{
//		d = false;
//	}
//
//	bool b;
//	if (*fp == *(fp + 1))
//	{
//		b = true;
//	}
//	else
//	{
//		b = false;
//	}
//}

//3

//double computeaverage(const double* scores, int nscores)
//{
//    const double* ptr = scores;
//    double tot = 0;
//    while (ptr != scores + nscores)
//    {
//        tot += *ptr;
//        ptr++;
//    }
//    return tot / nscores;
//}
//
//double newcomputeaverage(const double* scores, int nscores)
//{
//    double tot = 0;
//    int i = 0;
//    while (i < nscores)
//    {
//        tot += *scores;
//        *scores++;
//        i++;
//    }
//    return tot / nscores;
//}
//
//int main()
//{
//    double scores[5] = { 3, 2, 642, 4, 552387 };
//    cout << computeaverage(scores, 5) << " " << newcomputeaverage(scores, 5);
//
//}

//    // This function searches through str for the character chr.
//    // If the chr is found, it returns a pointer into str where
//    // the character was first found, otherwise nullptr (not found).
//
//const char* findTheChar(const char str[], char chr)
//{
//    for (int k = 0; str[k] != 0; k++)
//        if (str[k] == chr)
//            return &str[k];
//
//    return nullptr;
//}
//
//const char* newfindTheChar(const char* str, char chr)
//{
//    for (int k = 0; *(str + k) != 0; k++)
//        if (*(str + k) == chr)
//            return (str + k);
//
//    return nullptr;
//}
//
//const char* newerfindTheChar(const char* str, char chr)
//{
//    while (*str != 0)
//    {
//        if (*str == chr)
//        {
//            return (str);
//        }
//        str++;
//    }
//    return nullptr;
//}
//
//int main()
//{
//    cout << findTheChar("Cynthia is the coolest person ever in the world", 'p') << endl
//        << newfindTheChar("Cynthia is the coolest person ever in the world", 'p') << endl
//        << newerfindTheChar("Cynthia is the coolest person ever in the world", 'p');
//
//}

//4

//#include <iostream>
//
//using namespace std;
//
int* minimart(int* a, int* b)
{
    if (*a < *b)
        return a;
    else
        return b;
}

void swap1(int* a, int* b)
{
    int* temp = a;
    a = b;
    b = temp;
}

void swap2(int* a, int* b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int main()
{
    int array[6] = { 5, 3, 4, 17, 22, 19 };

    int* ptr = minimart(array, &array[2]);
    ptr[1] = 9;
    ptr += 2;
    *ptr = -1;
    *(array + 1) = 79;

    cout << "diff=" << &array[5] - ptr << endl;

    cout << &array[0] << " " << &array[1] << endl;
    cout << array[0] << " " << array[1] << endl;
    swap1(&array[0], &array[1]);
    cout << &array[0] << " " << &array[1] << endl;
    cout << array[0] << " " << array[1] << endl;
    swap2(array, &array[2]);

    for (int i = 0; i < 6; i++)
        cout << array[i] << endl;
}

//5

//void deleteG(char* str)
//{
//	char* p = str;
//	while (*str != 0)
//	{
//		if (tolower(*p) == 'g')
//		{
//			p++;
//		}
//		*str = *p;
//		str++;
//		p++;
//	}
//	str++;
//	*str = 0;
//}
//
//int main()
//{
//	char msg[100] = "I recall the glass gate next to Gus in Lagos, near the gold bridge.";
//	deleteG(msg);
//	cout << msg;  // prints   I recall the lass ate next to us in Laos, near the old bride.
//}