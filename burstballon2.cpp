#include<iostream>
using namespace std;
int n;
int nums[20];
int dp[20][20];



int solve(int nums[], int l, int r){
    // base case
    if(l+1>=r){
        return 0;
    }
    if(dp[l][r] !=-1) return dp[l][r];
    int temp =0;
    for(int k = l+1 ; k<r; k++){
        temp = max(temp,nums[k]*nums[l]*nums[r]+ solve(nums,l,k) + solve(nums,k,r));
    }
    dp[l][r] = temp;

    return dp[l][r] ;
}



int main(){

        cin>>n;

        for(int i =1 ;i<=n; i++){
            cin>>nums[i];
        }
     if(n==1){
        cout<<nums[1]<<endl;
        return 0;
        }
        for (int i = 0; i <= n + 1; ++i)
        for (int j = 0; j <= n + 1; ++j)
            dp[i][j] = -1;
        nums[0]=1;
        nums[n+1] = 1;
        
        cout<<solve(nums,0,n+1)<<endl;
        
    return 0;
    
}
