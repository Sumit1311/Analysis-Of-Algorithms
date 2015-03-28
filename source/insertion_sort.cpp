void insertion_sort(int *arr,int len){
    for(int i=1;i<len;i++){
        int key=arr[i];
        int j=i-1;
        //check arr[0...i-1 ]elements are if they are greater then shift them in the right
        //until a smaller element than key occurs.
        while(j>=0 && arr[j]>key){
            arr[j+1]=arr[j];
            j=j-1;
        }
        arr[j+1]=key;
    }
}
