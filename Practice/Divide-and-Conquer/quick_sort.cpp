#include<iostream>
#include<stdlib.h>

using namespace std;

void printArray(int *arr, int begin, int end) {
	cout<<"Array is (" <<begin << "-" <<end <<"): ";
	for(int i = begin; i <= end; ++i) {
		cout<<arr[i]<<",";
	}
	cout<<endl;
}

void swap(int &a, int &b) {
	int temp = a;
	a = b;
	b = temp;
}

int partition(int *arr, int begin, int end) {
	int pIndex = begin;
	int l = pIndex + 1, h = end;
	
	while( l < h ) {
		while( ( arr[l] < arr[pIndex] ) && l < end) {
			l++;
		}
		
		while( ( arr[h] > arr[pIndex]  ) && h > begin) {
			h--;
		}
		//cout<<"Low  : "<<l<<", High : "<<h<<endl;
		if( l < h ) {
			int temp = arr[l];
			arr[l] = arr[h];
			arr[h] = temp;
		}
		//printArray(arr, begin, end);
	}
	//cout<<"High  : "<<h<<", Pivot : "<<pIndex<<endl;
	if(arr[pIndex] > arr[h]) {
		int temp = arr[pIndex];
		arr[pIndex] = arr[h];
		arr[h] = temp;
	}
	return h;
}

int partition1(int *arr, int begin, int end) {
	int pIndex = begin;
	int l = end + 1, h = end;
	printArray(arr, begin, end);
	
	while( h > begin) {
		if(arr[pIndex] > arr[h]) {
			l--;
			int temp = arr[l];
			arr[l] = arr[h];
			arr[h] = temp;
		}
		h--;
	}
	
	printArray(arr, begin, end);
	int temp = arr[pIndex];
	arr[pIndex] = arr[l-1];
	arr[l-1] = temp;
	return l - 1;
	
}

int partition3(int *arr, int begin, int end) {
	int rIndex = rand() % (end - begin);
	
	swap(arr[begin + rIndex], arr[begin]);
	cout<<"After swap ";
	printArray(arr, begin, end);
	int pIndex = begin;
	int l = end + 1, h = end;
	printArray(arr, begin, end);
	
	while( h > begin) {
		if(arr[pIndex] > arr[h]) {
			l--;
			int temp = arr[l];
			arr[l] = arr[h];
			arr[h] = temp;
		}
		h--;
	}
	
	printArray(arr, begin, end);
	int temp = arr[pIndex];
	arr[pIndex] = arr[l-1];
	arr[l-1] = temp;
	printArray(arr, begin, end);
	return l - 1;
	
}

void approach1(int *arr, int begin, int end) {
	cout<<"Called with " << begin << "-" << end << endl;
	if(begin >= end) {
		return;
	}
	
	int h = partition3(arr, begin, end);
	
	//printArray(arr, begin, end);
	approach1(arr, begin, h-1);
	approach1(arr, h + 1, end);
}

void threeWayPartition(int *arr, int low, int high, int &i, int &j) {
	
	int mid = low ;
	int pIndex = high;
	while(mid < high) {
		if(arr[mid] < arr[pIndex]) {
			swap(arr[mid], arr[low]);
			low++;
			mid++;
		} else if( arr[mid] > arr[pIndex]) {
			swap(arr[mid], arr[high]);
			high--;
		} else {
			mid++;
		}
		
		cout<<"Low : "<<low<<", Mid : "<<mid<<", High : "<<high<<endl;
		printArray(arr, low, high);
	}
	
	i = low - 1; 
	j = high;
	
}

void threeWayPartitionDesc(int *arr, int begin, int end, int& i, int& j) {
	int mid = end;
	int pIndex = begin;
	
	while(mid >= begin) {
		if(arr[mid] > arr[pIndex]) {
			swap(arr[mid], arr[begin]);
			begin++;
		} else if(arr[mid] == arr[pIndex]) {
			mid--;
		} else {
			swap(arr[mid], arr[end]);
			end--;
			mid--;
		}
//		cout<<"Low : "<<begin<<", Mid : "<<mid<<", High : "<<end<<endl;
//		printArray(arr, begin, end);
	}
	
	i = begin;
	j = end+1;
}

void approach2(int * arr, int begin, int end) {
	
	if(begin >= end) {
		return;
	}
	
	int i, j;
	
	threeWayPartition(arr, begin, end, i, j);
	
	approach2(arr, begin, i);
	approach2(arr, j, end);
	
}

int main() {
	//int arr[] = {5,8,2,4,3,6,10};
	//int arr[] = {5,8,7,11,12,6,10};
	//int arr[] = {15,8,7,11,12,6,10};
	// 5,3,2,4,8,6,10
	//int arr[] = {6,7,8,10,11,12,13};
	int arr[] = {7,6,5,4,3,2,1};
	int size = 7;
	//int arr[] = {9, 8};
	//int size = 2;
	cout<<"Unsorted ";
	printArray(arr, 0 ,size - 1);
	approach1(arr, 0, size - 1);
	cout<<"Sorted ";
	printArray(arr, 0 ,size - 1);


	int arr1[] = {1,5,3,5,3,6,5,2,5,7,8,9,5};
	int size1 = 13;
	cout<<"Unsorted ";
	printArray(arr1, 0 ,size1 - 1);
	approach2(arr1, 0, size1 - 1);
	cout<<"Sorted ";
	printArray(arr1, 0 ,size1 - 1);	
	return 0;
}
