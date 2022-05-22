// [3,2,4,6,8,7]
// [3,2,7,4,6,8]
// [2,3,4,6,7,8] --> 5
// [5,2,3,4,1,6]
// [1,2,3,4,5,6]
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
typedef int * IntPtr;
typedef vector<int> VectorInt;

void printVector(IntPtr arr, int begin, int end)
{
	cout<<"Vector : ";
	for(int i = begin; i <= end; ++i) {
		cout<<arr[i]<<",";
	}
	cout<<endl;
}

//Wrong approach and understanding
int approach1(IntPtr array, int begin, int end)
{
	/// !!!!!! DONT USE THIS !!!!!
	/// Incorrect way
    int countInversions = 0;
    VectorInt tempV(array+begin, array+end);
    sort(tempV.begin(), tempV.end());
    for (int i = 0; i < tempV.size(); ++i)
    {
        if (tempV[i] != array[i])
        {
            countInversions++;
        }
    }
    return countInversions;
}

int approach2(IntPtr array, int begin, int end)
{
    int countInversions = 0;

    for (int i = begin; i < end; ++i)
    {
        for (int j = i + 1; j <= end; ++j)
        {
            if (array[i] > array[j])
            {
                countInversions++;
            }
        }
    }

    return countInversions;
}

int countInversions(IntPtr array, int begin, int mid, int end) {
	int count = 0;
	int size1 = mid - begin + 1;
	int size2 = end - mid;
	IntPtr first = new int[size1];
	IntPtr second = new int[size2];
//	cout<<"Before ";
//	printVector(array, begin, end);
	for(int i = begin; i <= mid; ++i) {
		first[i-begin] = array[i];
	}
	
	for(int i = mid + 1; i <= end; ++i) {
		//cout<<"setting second : "<<array[i]<<endl;
		second[i - mid - 1] = array[i];
	}
	
//	cout<<begin<<"-"<<mid<<"-"<<end<<endl;
//
//	cout<<"First : ";
//	printVector(first, 0, (mid - begin));
//	
//	cout<<"Second : ";
//	printVector(second, 0, (end - mid) - 1);
	
	int i = 0, j = 0, k = begin;
	
	while(i < size1 && j < size2) {
		if(first[i] >= second[j]) {
			array[k] = second[j];
			j++;
			count+=(size1 - i);
		} else {
			array[k] = first[i];
			i++;
		}
		k++;
	}
	
	while(i < size1) {
			array[k] = first[i];
			i++;
			k++;
	}
	
	while( j < size2) {
		array[k] = second[j];
			j++;
			k++;
	}
	
	
//	printVector(array, begin, end);
//	cout<<count<<endl;
	return count;
	
}

int approach3(IntPtr array, int begin, int end)
{   
    if(begin >= end) {
		return 0;
	}
	int mid = begin + ((end - begin) / 2);
    //cout<<"counting for "<<begin<<"-"<<mid<<"-"<<end<<endl;
	int count = approach3(array, begin, mid) + approach3(array, mid+1, end);
	return count + countInversions(array, begin, mid, end);
}

int main()
{
    //int arr[] = {3, 2, 7, 4, 6, 8};
    int arr[] = {8, 4, 2, 1};
    //int size = 6;
    int size = 4;
    cout << approach1(arr, 0, 3 ) << endl;//!!!Wrong Method. Don't Use it!!!!
    cout << approach2(arr, 0, 3 ) << endl;
    cout << approach3(arr, 0, 3 ) << endl;
}
