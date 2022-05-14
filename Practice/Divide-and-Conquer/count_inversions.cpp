// [3,2,4,6,8,7]
// [3,2,7,4,6,8]
// [2,3,4,6,7,8] --> 5
// [5,2,3,4,1,6]
// [1,2,3,4,5,6]
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
typedef vector<int> VectorInt;

void printVector(VectorInt &arr)
{
}

int approach1(VectorInt &array)
{
    int countInversions = 0;
    VectorInt tempV(array);
    sort(tempV.begin(), tempV.end());
    for (int i = 0; i < array.size(); ++i)
    {
        if (tempV[i] != array[i])
        {
            countInversions++;
        }
    }
    return countInversions;
}

int approach2(VectorInt &array)
{
    int countInversions = 0;

    for (int i = 0; i < array.size(); ++i)
    {
        for (int j = i + 1; j < array.size(); ++j)
        {
            if (array[i] > array[j])
            {
                countInversions++;
            }
        }
    }

    return countInversions;
}

int main()
{
    VectorInt arr{3, 2, 7, 4, 6, 8};
    cout << approach1(arr) << endl;
    cout << approach2(arr) << endl;
}
