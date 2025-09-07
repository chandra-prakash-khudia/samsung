/*
There is an island surrounded by oil mines. You will be given n companies and m oil mines having values.
You have to distribute the mines to "n" companies in fair manner. Remember the companies can have oil
mines adjacent to each other and not in between of each others.After distributing them compute the
difference of oil mines from the company getting highest and company getting lowest. This number
should be minimum.(then only the distribution can be termed as fair).

Input
2
2 4
6 13 10 2
2 4
6 10 13 2

output
5
1
*/
#include <iostream>
#include <climits>
using namespace std;

int companies, mines;



void solve(int currIdx, int oilMines[], bool visited[], int currMinSum, int currMaxSum, int activePartitionSum, int count, int &ans)
{
    // we made full cycle and returned to initial mine
    if (visited[currIdx])
    {
        int finalMin = min(activePartitionSum, currMinSum);
        int finalMax = max(activePartitionSum, currMaxSum);

        if (count == companies - 1)
        {
            ans = min(ans, finalMax - finalMin);
        }
        return;
    }
    // visit
    visited[currIdx] = true;
    int j = (currIdx + 1) % mines;
    // recurrisive call
    // add currentMine to current companny
    solve(j, oilMines, visited, currMinSum, currMaxSum, activePartitionSum + oilMines[currIdx], count, ans);
    int minV = min(activePartitionSum, currMinSum);
    int maxV = max(activePartitionSum, currMaxSum);
    // make new company
    solve(j, oilMines, visited, minV, maxV, oilMines[currIdx], count + 1, ans);
    visited[currIdx] = false;
}
int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        cin >> companies >> mines;
        int arr[mines];
        bool vis[mines];
        for (int i = 0; i < mines; i++)
        {
            cin >> arr[i];
            vis[i] = false;
        }
        int minDifference = INT_MAX;
        for (int startIndex = 0; startIndex < mines; startIndex++)
        {
            int nextIndex = (startIndex + 1) % mines;

            vis[startIndex] = true;


            solve(nextIndex, arr, vis,
                                       INT_MAX, INT_MIN,     
                                       arr[startIndex], 
                                       0,                    
                                       minDifference);

     
            vis[startIndex] = false;
        }
        cout << minDifference << endl;
    }
    return 0;
}