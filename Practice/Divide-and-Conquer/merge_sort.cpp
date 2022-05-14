#include <vector>
#include <iostream>

using namespace std;

typedef int *IntPtr;

void printVector(IntPtr arr, int size)
{
    cout << "Vector is : ";
    for (auto itr = arr; itr != arr + size; itr++)
    {
        cout << *itr << ",";
    }
    cout << endl;
}

IntPtr merge(IntPtr arr1, int size1, IntPtr arr2, int size2)
{
    IntPtr merged = new int[size1 + size2];

    int i = 0, j = 0, k = 0;

    while (i < size1 && j < size2)
    {
        if (arr1[i] <= arr2[j])
        {
            merged[k] = arr1[i];
            i++;
        }
        else
        {
            merged[k] = arr1[j];
            j++;
        }
        k++;
    }

    while (i < size1)
    {
        merged[k] = arr1[i];
        i++;
        k++;
    }

    while (j < size1)
    {
        merged[k] = arr2[j];
        j++;
        k++;
    }

    printVector(merged, size1 + size2);

    return merged;
}

IntPtr merge_sort(IntPtr array, int size)
{
    if (size == 1)
    {
        return array;
    }

    int size1 = size / 2;
    IntPtr arr1 = merge_sort(array, size / 2);
    int size2 = size % 2 == 0 ? (size / 2) : (size / 2) + 1;
    IntPtr arr2 = merge_sort(array + 1 + (size / 2), size2);
    printVector(arr1, size1);
    printVector(arr2, size2);
    return merge(arr1, size1, arr2, size2);
}

int main()
{
    int arr[] = {3, 2, 7, 4, 6, 8, 5};
    int size = 7;
    merge_sort(arr, size);
    printVector(arr, size);
    return 0;
}