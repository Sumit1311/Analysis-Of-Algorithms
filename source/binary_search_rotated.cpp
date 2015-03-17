#include <iostream>
using namespace std;

int binary_search_rotated(int *arr,int low,int high,int k){
    //10,12,17,18,20,21,2,5,6,7
    if(low>high){
        return -1;
    }
    int mid=(low+high)/2;
    cout<<"Mid : "<<arr[mid]<<endl;
    if(arr[mid]== k){
        return 1;
    }
    if(arr[mid]<=arr[mid+1]){
        if(k>arr[mid]){
            //right part
            return binary_search_rotated(arr,mid+1,high,k);
        }else if(k <= arr[high]){
            //right part
            return binary_search_rotated(arr,mid+1,high,k);
        }else{
            //left part
            return binary_search_rotated(arr,low,mid-1,k);
        }
    }else{
        if(k > arr[mid]){
            //left part
            return binary_search_rotated(arr,low,mid-1,k);
        }else if(k >= arr[low]){
            //left part
            return binary_search_rotated(arr,low,mid-1,k);
        }else{
            //right part
            return binary_search_rotated(arr,mid+1,high,k);
        }
    }
}
