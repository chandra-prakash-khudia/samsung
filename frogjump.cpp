
/*

Given a 2 D matrix where 1 represent the places where the frog can jump and 0 represent the empty spaces,
the frog can move freely in horizontal direction (on 1’s only) without incurring any cost (jump).
A vertical jump from a given point of the matrix to other point on the matrix can be taken (on 1’s only)
with cost as the number of jumps taken.
Given a source and destination, the frog has to reach the destination minimizing the cost (jump).
*/
#include <iostream>
using namespace std;
int map[100][100];
int dp[100][100];
int vis[100][100];
int dir[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
int n, m;
int sx, sy, dx, dy;
bool isValid(int x, int y)
{
    return (x > 0 && x <= n && y > 0 && y <= m && map[x][y] == 1 && !vis[x][y]);
}
void solve(int x, int y, int ans)
{
    // vis[x][y] = 1;
    if (ans >= dp[x][y])
        return;

    dp[x][y] = ans;
    if (x == dx && y == dy)
        return;
    vis[x][y] = 1;

    for (int i = 0; i < 4; i++)
    {
        int newX = x + dir[i][0];
        int newY = y + dir[i][1];
        int temp = 0;
        if (!isValid(newX, newY))
            continue;

        int cost = (newX == x) ? 0 : 1; // same row -> horizontal move -> cost 0; else vertical -> cost 1
        solve(newX, newY, ans + cost);
    }
    vis[x][y] = 0;
}
int main()
{
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            cin >> map[i][j];
            dp[i][j] = 10000;
            vis[i][j] = 0;
        }
    }
    cin >> sx >> sy >> dx >> dy;
    solve(sx, sy, 0);
    if (dp[dx][dy] == 10000)
    {
        cout << -1 << endl;
    }
    else
    {

        cout << dp[dx][dy] << endl;
    }
}
