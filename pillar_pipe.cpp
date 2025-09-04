#include <iostream>
using namespace std;

int n;
int ans;
int dp[50][10000];

int solve(int * arr,int i, int diff){
    if(i == n){
        if(diff == 0)return 0;
        return -1e9;
    }
    if(dp[i][diff] != -1)return dp[i][diff];
    
    int res = solve(arr, i+1, diff);
    res = max(res, solve(arr, i+1, diff+arr[i]));
    if(diff >= arr[i]){
        res = max(res, arr[i]+solve(arr, i+1, diff-arr[i]));
    }
    else{
        res = max(res, diff+solve(arr, i+1, arr[i]-diff));
    }

    return dp[i][diff] = res;
}

int main(){
    int t;
    cin>>t;
    while(t--){
        cin>>n;
        int arr[n];
        for(int i = 0;i<n;i++){
            cin>>arr[i];
        }
        fill(&dp[0][0], &dp[0][0]+ 50*10000, -1);
        ans = 0;
        cout<<solve(arr, 0, 0)<<endl;
    }
}
