#include<iostream>
using namespace std;
int n;
int k;


void sort(int arr[]){
    for(int i =0 ; i<n ; i++){
        int element = arr[i];
        int temp = arr[i];
        int index = i;
        for(int j =i+1 ; j<n;j++){
            if(arr[j] < element){
                element = arr[j];
                index = j;
            }
        }
        arr[i] = element;
        arr[index]= temp;
    }

}
bool check(int arr[],int dis){
    int last = arr[0];
    int cnt =1;
    for(int i =1; i<n ; i++){
        if(arr[i] - last >= dis){
            last = arr[i];
            cnt++;
            if(cnt == k) return true;
        }
    }
    return false;
}
int solve(int arr[]){
    // first of all sort the array

    int start = 1;
    int end = arr[n-1] - arr[0];
    int ans = -1;
    while(start <=end){
        int mid = start+ (end-start)/2;
        if(check(arr, mid)){
            ans= mid;
            start = mid+1;
        }else{
            end = mid-1;
        }
    }
    return ans;
}
int main(){
    int t;
    cin>>t; 
    while(t--){
        cin>>n;
        int arr[n];
        for(int i =0 ; i<n ; i++){
            cin>>arr[i];
        }
        cin>>k;
        sort(arr);
        cout<<solve(arr);

    }
    return 0;

}



void mergeRanges(int arr[], int l, int mid, int r, int temp[]) {
    int i = l;       // pointer for left half
    int j = mid + 1; // pointer for right half
    int k = l;       // pointer for temp

    while (i <= mid && j <= r) {
        if (arr[i] <= arr[j]) {
            temp[k++] = arr[i++]; // stable: <= keeps left elements before right when equal
        } else {
            temp[k++] = arr[j++];
        }
    }
    while (i <= mid) temp[k++] = arr[i++];
    while (j <= r)   temp[k++] = arr[j++];

    // copy back to original array
    for (int idx = l; idx <= r; ++idx) arr[idx] = temp[idx];
}

void mergeSortRec(int arr[], int l, int r, int temp[]) {
    if (l >= r) return;
    int mid = l + (r - l) / 2;
    mergeSortRec(arr, l, mid, temp);
    mergeSortRec(arr, mid + 1, r, temp);
    mergeRanges(arr, l, mid, r, temp);
}

void mergeSort(int arr[], int n) {
    if (n <= 1) return;
    int *temp = new int[n];        // allocate temporary buffer once
    mergeSortRec(arr, 0, n - 1, temp);
    delete[] temp;
}
