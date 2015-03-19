int binary_search_optimal(int *ar,int l,int h,int k){
    int mid=0;
    while(l-h >= 1){
        mid=l+(h-l)/2;
        if(ar[mid] <= k){
            l=mid;
        }else{
            h=mid;
        }
    }
    if(ar[l] == k){
        return l;
    }
    return -1;
}
