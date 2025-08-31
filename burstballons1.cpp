// //
// Submissions
// Discussions
// There are N Balloons marked with value Bi (where B(i…N)). User will be given Gun with N Bullets and user must shot N times. When any balloon explodes then its adjacent balloons becomes next to each other. User has to score highest points to get the prize and score starts at 0. Below is the condition to calculate the score. When Balloon Bi Explodes then score will be a product of Bi-1 & Bi+1 (score = Bi-1 * Bi+1). When Balloon Bi Explodes and there is only left Balloon present then score will be Bi-1. When Balloon Bi Explodes and there is only right Balloon present then score will be Bi+1. When Balloon Bi explodes and there is no left and right Balloon present then score will be Bi. Write a program to score maximum points.

// Input 4 1 2 3 4

// Output

// 20

// Input Format

// First line N Next line array of N integers

// Constraints

// 1 < N < 10

// Output Format

// Single integer

// Sample Input 0

// 4
// 1 2 3 4
// Sample Output 0

// 20



#include<iostream>
using namespace std;
int n;
int nums[20];
int dp[20][20];

// int score(int l, int i, int r) {
//     if (l == 0 && r == n + 1) return nums[i];    // no neighbors
//     if (l == 0)               return nums[r]  ;  // only right
//     if (r == n + 1)           return nums[l];    // only left
//     return nums[l] * nums[r];                        // both neighbors
// }

// int solve(int nums[], int l, int r){
//     // base case
//     if(l+1>=r){
//         return 0;
//     }
//     if(dp[l][r] !=-1) return dp[l][r];
//     int temp =0;
//     for(int k = l+1 ; k<r; k++){
//         temp = max(temp,score(l,k,r)+ solve(nums,l,k) + solve(nums,k,r));
//     }
//     dp[l][r] = temp;

//     return dp[l][r] ;
// }
void solve(){
    // len = r-l
for(int len = 2 ; len<=n+1; len++){
   for(int l = 0;l+len<=n+1;l++){
    int r = l+len;
    int best = 0;
    for(int k =l+1 ; k<r ; k++){
        int gain =0;
        if(l==0 && r == n+1) gain = nums[k];
        else if(l==0) gain = nums[r];
        else if(r==n+1) gain = nums[l];
        else gain = nums[l]*nums[r];
        int val = dp[l][k] + dp[k][r] +gain ;
        best = max(best, val);
    }
    dp[l][r] = best;
   }
}
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
            dp[i][j] = 0;
        solve();
        cout<<dp[0][n+1]<<endl;
        
    return 0;
    
}

