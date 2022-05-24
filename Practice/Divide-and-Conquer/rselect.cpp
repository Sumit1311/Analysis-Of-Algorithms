#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int dSelectMax(int *arr, int begin, int end, int order);

void swap(int& a, int& b) {
	int temp = a;
	a = b;
	b = temp;
}

void printArray(int *arr, int begin, int end) {
	cout<<"Array is ("<<begin<<"-"<<end<<") : ";
	while(begin <= end) {
		cout<<arr[begin++]<<",";
	}
	cout<<endl;
}

int partitionAsc(int *arr, int begin, int end) {
	int pIndex = end;
//	int origB = begin, origE = end;
	
	while(begin < end) {
		if(arr[begin] < arr[pIndex]) {
			begin++;
		} else {
			end--;
			swap(arr[end], arr[begin]);
		}
//		cout<<begin<<","<<end<<","<<endl;
//		printArray(arr, origB, origE);
	}
	swap(arr[pIndex], arr[end]);
	return end;
}

int partitionDesc(int *arr, int begin, int end) {
	int pIndex = begin;
	
	while(begin <= end) {
		if(arr[begin] >= arr[pIndex] ) {
			begin++;
		} else {
			swap(arr[end], arr[begin]);
			end--;
		}
	}
	swap(arr[begin-1], arr[pIndex]);
	return begin-1;
}

int rselectMin(int *arr, int begin, int end, int i) {
	int pIndex = partitionAsc(arr, begin, end);
	cout<<"After partitioning around "<<pIndex<<" ";
	printArray(arr, begin, end);
	if(pIndex == (i-1)) {
		return arr[pIndex];
	} else if(pIndex > (i-1)) {
		return rselectMin(arr, begin, pIndex - 1, i);
	} else {
		return rselectMin(arr, pIndex + 1, end, i);
	}
}

int rselectMax(int *arr, int begin, int end, int order) {
	int pIndex = partitionDesc(arr, begin, end);
	
	cout<<"After partitioning around "<<pIndex<<" ";
	printArray(arr, begin, end);
	
	if(pIndex == (order - 1)) {
		return arr[pIndex];
	} else if(pIndex < (order - 1)) {
		return rselectMax(arr, pIndex+1, end, order);
	} else {
		return rselectMax(arr, begin, pIndex-1, order);
	}
}

void printVector(vector<int>::iterator begin, vector<int>::iterator end) {
	cout<<"Vector is :";
	while(begin < end) {
		cout<<(*begin)<<",";
		begin++;
	}
	cout<<endl;
}

vector<int>::iterator partitionAsc(vector<int>::iterator begin, vector<int>::iterator end) {
	vector<int>::iterator pivot = end - 1;
	end = end - 1;
	while(begin < end) {
		if(*begin > *pivot) {
			end--;
			swap(*begin, *end);
		} else {
			begin++;
		}
//		printVector(begin, end);
//		cout<<"begin : "<<*begin<<", end : "<<*end<<endl;
	}
//	cout<<"begin : "<<*begin<<", end : "<<*end<<", pivot"<<*pivot<<endl;
	swap(*pivot, *begin);
	return begin;
}

int rselectMin(vector<int>::iterator begin, vector<int>::iterator end , int order) {
//	printVector(begin, end);
	vector<int>::iterator p = partitionAsc(begin, end);
//	printVector(begin, end);
	int numOfEle = abs(distance(p, begin)) + 1;
//	cout<<"Distance : "<<numOfEle<<", order :"<<order<<endl;
	if( numOfEle == order) {
		return *p;	
	} else if(numOfEle > order) {
		return rselectMin(begin, p, order);
	} else {
		return rselectMin(p + 1, end, order - numOfEle);
	}
	
}

int getMedian(int *arr, int begin, int end) {
	int length = end - begin + 1;
	if(length == 1) {
		return arr[begin];
	}
	sort(arr+begin, arr+end+1);
	cout<<"getMedian ";
	printArray(arr, begin, end);
	int mIndex = (length) / 2 ;
	cout<<"Median is at "<<mIndex<<endl;
	return arr[mIndex];
}

int getPivot(int *arr, int begin, int end) {
	int len = end - begin + 1;
	if(len == 1) {
		return arr[begin];
	}
	int length = ((len) % 5) == 0 ? len / 5 : (len / 5) + 1;
	int *medians = new int[length];
	int offset = 0;
	int endOfArray = len < 5 ? offset + len  : offset + 5 ;
	for(int i = 0; i < length; ++i) {
		int lengthOfArray = len < 5 ? len : 5;
		int *tempArray = new int[lengthOfArray];
		copy(arr+offset, arr+endOfArray, tempArray);
		medians[i] = getMedian(tempArray, 0 , lengthOfArray - 1);
		len -= 5;
		offset = endOfArray;
		endOfArray = len < 5 ? offset + len : offset + 5;
	}
	if(length == 1) {
		return medians[0];
	}
	else if(length == 2) {
		return medians[length/2];
	} else {
		return dSelectMax(medians, 0, length - 1, (length / 2) + 1 );	
	}
}

int dPartitionDesc(int *arr, int begin, int end) {
	int pivot = getPivot(arr, begin, end);
	int pIndex = begin;
	for(; pIndex <= end; ++pIndex) {
		if(arr[pIndex] == pivot) {
			break;
		}
	}
	swap(arr[pIndex], arr[begin]);
	pIndex = begin;

	while(begin <= end) {
		if(arr[begin] >= arr[pIndex] ) {
			begin++;
		} else {
			swap(arr[end], arr[begin]);
			end--;
		}
	}
	swap(arr[begin-1], arr[pIndex]);
	return begin-1;
}

int dSelectMax(int *arr, int begin, int end, int order) {
	cout<<"dSelectMax ";
	printArray(arr, begin, end);
	int pIndex = dPartitionDesc(arr, begin, end);
	cout<<"After partitioning around "<<pIndex<<" and order is "<<order<<" ";
	printArray(arr, begin, end);
	if(pIndex == (order - 1)) {
		return arr[pIndex];
	} else if( pIndex > (order - 1)){
		return dSelectMax(arr, begin, pIndex - 1, order);
	} else {
		return dSelectMax(arr, pIndex + 1, end, order);
	}
}



int main() {
	int arr[] = {5,10,2,4,3,6,11,23,9,12,25,15,16};
	int size = sizeof(arr) / sizeof(arr[0]);
	int i = 3;
	
	cout<<i<<"(th) min is : "<<rselectMin(arr, 0, size - 1, i)<<endl;
	printArray(arr, 0, size - 1);
	cout<<i<<"(th) max is : "<<rselectMax(arr, 0, size - 1, i)<<endl;
	
	vector<int> arr1(arr, arr + size);
	int order = 4;
	cout<<order<<"(th) min is : "<<rselectMin( arr1.begin(), arr1.end(), order)<<endl;
	
	cout<<order<<"(th) max is : "<<dSelectMax(arr, 0, size - 1, order);
	return 0;
}
