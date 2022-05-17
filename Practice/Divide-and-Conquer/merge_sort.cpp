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
            merged[k] = arr2[j];
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

    while (j < size2)
    {
        merged[k] = arr2[j];
        j++;
        k++;
    }
//	cout<<"Merged Array"<<endl;   
//    printVector(merged, size1 + size2);

    return merged;
}

IntPtr merge_sort(IntPtr array, int size)
{
    if (size == 1)
    {
        return array;
    }

    int size1 = size / 2;
    IntPtr arr1 = merge_sort(array, size1);
    int size2 = size % 2 == 0 ? size1 : size1 + 1;
    IntPtr arr2 = merge_sort(array + size1, size2);
//    cout<<"First SubArray"<<endl;    
//	printVector(arr1, size1);
//    cout<<"Second SubArray"<<endl;    
//	printVector(arr2, size2);
    
    IntPtr merged = merge(arr1, size1, arr2, size2);
    return merged;
}

int main()
{
    int arr[] = {3, 2, 7, 4, 6, 8, 5};
    int size = 7;
    cout<<"Unsorted ";
    printVector(arr, size);
    IntPtr sorted = merge_sort(arr, size);
    cout<<"Sorted ";
    printVector(sorted, size);
    return 0;
}
