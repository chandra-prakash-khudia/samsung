#include <iostream>
using namespace std;
int arr[1000][1000];
int n;
bool solve(int node, bool vis[], int parent, int &prev)
{
    vis[node] = true;

    for (int i = 0; i < n; i++)
    {

        if (arr[node][i] == 1 && !vis[i])
        {

            if (solve(i, vis, node, prev))
            {
                if (node == prev)
                {
                    cout << node << " ";
                    prev = -1;
                }
                else if (prev != -1)
                {
                    cout << node << " ";
                }
                return true;
            }
        }
        else if (arr[node][i] == 1 && i != parent && vis[i])
        {
            prev = i;
            cout << node << " ";
            return true;
        }
    }
    return false;
}
int main()
{
    int m;
    cin >> n >> m;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            arr[i][j] = 0;
        }
    }
    for (int i = 0; i < m; i++)
    {
        int x, y;
        cin >> x >> y;
        arr[x][y] = 1;
        arr[y][x] = 1;
    }
    bool vis[n];
    for (int i = 0; i < n; i++)
    {
        vis[i] = false;
    }
    int prev = -1;
    bool check = solve(0, vis, -1, prev);
    if (!check)
    {
        cout << "False" << endl;
    }
}
