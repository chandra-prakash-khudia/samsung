
// have to check memoizaton code yet

#include <iostream>
using namespace std;
// int result;
int n;
const int MAX = 1000;
int nums[MAX];

// void solve(int p1, int p2, int idx){
//     if (idx > n) {
//         if (p1 == p2) result = max(result, p1);
//         return;
//     }
//     solve(p1 + nums[idx], p2, idx + 1);
//     solve(p1, p2 + nums[idx], idx + 1);
//     solve(p1, p2, idx + 1);
// }

int dp[500][1000];
int solve(int idx , int diff){
    if(idx==n){
        if(diff ==0) return 0;
        return -1e7;
    }
    if(dp[idx][diff] !=-1) return dp[idx][diff];
    int res = solve(idx+1, diff);
    res = max(res, solve(idx+1, diff+ nums[idx]));
    res = max(res, min(diff, nums[idx]) + solve(idx+1, abs(diff-nums[idx])));
    return dp[idx][diff] = res;

}
int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        cin >> n;
        for (int i = 0; i < n; i++)
        {
            cin >> nums[i];
        }

        // result = -1;
        // int pillar1 = 0;
        // int pillar2 = 0;
        // solve(pillar1, pillar2, 1);
        for(int i =0; i<500;i++){
            for(int j = 0 ; j<1000;j++){
                dp[i][j] =-1;
            }
        }

        cout << solve(0,0) << endl;
    }
}