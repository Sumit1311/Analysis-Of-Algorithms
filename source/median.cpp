#include "dividenconquer.h"

int median(int *,int);
int minimum(int,int);
int maximum(int,int);

int median_of_sorted_arrays(int *arr1,int *arr2,int n) {
    int m1=0;
    int m2=0;

    if(n<=0) {
        return -1;
    }
    if(n==1) {
        return (arr1[0]+arr2[0])/2;
    }
    if(n == 2) {
        return (maximum(arr1[0],arr2[0]) + minimum(arr1[n-1],arr2[n-1]))/2;
    }

    m1=median(arr1,n);
    m2=median(arr2,n);

    if(m1 == m2) {
        return m1;
    }
    if(m1<m2) {
        if(n%2 == 0) {
            return median_of_sorted_arrays(arr1+n/2-1,arr2,n/2+1);
        } else {
            return median_of_sorted_arrays(arr1+n/2,arr2,n/2);
        }
    } else {
        if(n%2 == 0) {
            return median_of_sorted_arrays(arr2+n/2-1,arr1,n/2+1);
        } else {
            return median_of_sorted_arrays(arr2+n/2,arr1,n/2);
        }
    }
}

int median(int *arr,int n) {
    if(n%2 == 0) {
        return (arr[n/2] + arr[n/2-1])/2;
    } else {
        return arr[n/2];
    }
}

int minimum(int x,int y) {
    return x>y?y:x;
}

int maximum(int x,int y) {
    return x>y?x:y;
}
