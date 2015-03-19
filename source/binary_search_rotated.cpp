#include <iostream>
using namespace std;

int binary_search_rotated(int *arr,int low,int high,int k){
    //10,12,17,18,20,21,2,5,6,7
    //2,5,6,7,10,12,17,18,20,21
    //20,21,2,5,6,7,10,12,17,18
    if(low>high){
        return -1;
    }
    int mid=(low+high)/2;
    cout<<"Mid : "<<arr[mid]<<endl;
    if(arr[mid]== k){
        return 1;
    }
    if(arr[mid] > k){
        if(arr[high] < arr[mid] && arr[high] >= k){
            //right
            return binary_search_rotated(arr,mid+1,high,k);
        }else{
            //left
            return binary_search_rotated(arr,low,mid-1,k);
        }
    }else{
        if(arr[low] > arr[mid] && arr[low] <= k){
            //left
            return binary_search_rotated(arr,low,mid-1,k);
        }else{
            //right
            return binary_search_rotated(arr,mid+1,high,k);
        }
    }
}
