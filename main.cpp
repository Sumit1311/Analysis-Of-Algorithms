#include <iostream>
#include "dividenconquer.h"

using namespace std;

int main() {
    //power funciton call
    //cout << "Power : " <<power(5,2)<< endl;
    //median of two sorted arrays
    //int array1[]= {10,12,17,18,20,21};
    //int array2[]= {11,14,16,19,22,23};
    //int n=sizeof(array1)/sizeof(array1[0]);
    //cout<<"Median Of Two Arrays : "<<median_of_sorted_arrays(array1,array2,n)<< endl;

    /*int array_sum[]= {-2, -5, 6, -2, -3, 1, 5, -6};
    int len=sizeof(array_sum)/sizeof(array_sum[0]);
    cout<<"Maximum Sum ofg Subarrays : "<<max_sum_sub(array_sum,len);*/

    int array3[]={10,12,17,18,20,21,2,5,6,7};
    int n=sizeof(array3)/sizeof(array3[0]);
    cout<<"Element 6 : "<<binary_search_rotated(array3,0,n-1,9);
    return 0;
}
