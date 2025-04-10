#include <iostream>
#include "../Array2D.h"
using namespace std;

int main()
{
    Array2D<int> arr(2, 2);
    int data[4] {1, 2, 3, 4};

    // filling array with data
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
            arr.assign(i, j, &data[2*i+j]);
    }

    // printing data in array
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
            cout << *arr.at(i, j) << endl;
    }

    // throwing out of range exception
    cout << arr.at(20, 20) << endl;
}