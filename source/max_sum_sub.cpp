#include "dividenconquer.h"
#include <iostream>

using namespace std;

int maximum=0;
int rec_compute(int*,int,int,int);

int max_sum_sub(int *arr,int n){
    int i = 0;
    for(i = 0;i < n;i++){
        if(arr[i]<0){
            maximum += arr[i];
        }
    }
    //cout<<"Maximum : "<<maximum<<endl;
    return rec_compute(arr,0,n,-1);
}

int rec_compute(int *arr,int start,int length,int left){
    cout<<"Current :"<<arr[start+(length-1)/2]<<endl;
    if(length <= 1){
        if(maximum < arr[start]){
            maximum=arr[start];
        }
        return arr[start];
    }
    int leftRec=rec_compute(arr,start,(length-1)/2,1);
    cout<<"Left Rec : "<<leftRec<<endl;
    cout<<"Maximum : "<<maximum<<endl;
    int rightRec=rec_compute(arr,start+(length-1)/2+1,(length-1)-(length-1)/2,0);
    cout<<"Right Rec : "<<rightRec<<endl;
    cout<<"Maximum : "<<maximum<<endl;
    if(leftRec > maximum){
        maximum=leftRec;
    }
    if(rightRec > maximum){
        maximum=rightRec;
    }
    if (arr[start+(length-1)/2] > maximum){
        maximum=arr[start+(length-1)/2];
    }
    cout<<"Maximum : "<<maximum<<endl;
    int temp=0;
    int temp2=0;
    if(left == 1){
        temp=rightRec + arr[start+(length-1)/2];
        temp2=leftRec + rightRec + arr[start+(length-1)/2];
        cout<<"Temp : "<<temp<< endl;
        cout<<"Temp 2 : "<<temp2<<endl;
        if(temp >= temp2){
            if(temp > maximum){
                maximum=temp;
            }
            return temp;
        }else{
            if(temp2 > maximum){
                maximum=temp2;
            }
            return temp2;
        }
    }
    if(left == 0){
        temp=leftRec + arr[start+(length-1)/2];
        temp2=leftRec + rightRec + arr[start+(length-1)/2];
        cout<<"Temp : "<<temp<< endl;
        cout<<"Temp 2 : "<<temp2<<endl;
        if(temp >= temp2){
            if(temp > maximum){
                maximum=temp;
            }
            return temp;
        }else{
            if(temp2 > maximum){
                maximum=temp2;
            }
            return temp2;
        }
    }
    temp=rightRec + arr[start+(length-1)/2];
    temp2=leftRec + rightRec + arr[start+(length-1)/2];
    int temp3=leftRec+arr[start+(length-1)/2];
    if(temp > maximum){
        maximum=temp;
    }
    if(temp2 > maximum){
        maximum=temp2;
    }
    if(temp3 > maximum){
        maximum=temp3;
    }

    return maximum;
}
