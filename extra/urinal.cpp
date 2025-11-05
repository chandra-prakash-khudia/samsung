#include<iostream>
#include<vector>
using namespace std;
 void solve(int n , int k , vector<int>&arr){
    for(int i =0 ; i<k;i++){
        int len = 0 , best = 0 , best_last =1;
        for(int j = 0; j<n ; j++){
            if(arr[i]==0){
                len++;
            }else{
                len = 0;
            }
            if(len>=best){
                best = len;
                best_last =j;
            }
        }
        if(best==0) break; // no ports available
        int start = best_last - len + 1;
        int mid = (start + best_last)/2;
        arr[mid] =1;
    }

 }
 int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t; 
    if (!(cin >> t)) return 0;
    while (t--) {
        int n, k;
        cin >> n >> k;
        vector<int> arr(n, 0);
        solve(n, k, arr);
        for (int x : arr) cout << x << ' ';
        cout << '\n';
    }
    return 0;
}
