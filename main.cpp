#include <iostream>
#include "dividenconquer.h"

using namespace std;

int main() {
    //power funciton call
    cout << "Power : " <<power(5,2)<< endl;
    //median of two sorted arrays
    int array1[]= {10,12,17,18,20,21};
    int array2[]= {11,14,16,19,22,23};
    int n=sizeof(array1)/sizeof(array1[0]);
    cout<<"Median Of Two Arrays : "<<median_of_sorted_arrays(array1,array2,n);
    return 0;
}
