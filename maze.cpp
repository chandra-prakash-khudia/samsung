/*
https://blog.csdn.net/lihenair/article/details/17227667
http://www.mamicode.com/info-detail-995985.html
https://www.oipapio.com/cn/article-8650635
https://blog.csdn.net/broadCE/article/details/47959227
--------------------------------------------------------
There is a maze that has one entrance and one exit. Jewels are placed in passages of the maze.
You want to pick up the jewels after getting into the maze through the entrance and before getting
out of it through the exit. You want to get as many jewels as possible, but you don’t want to take
the same passage you used once.

When locations of a maze and jewels are given, find out the greatest number of jewels you can get
without taking the same passage twice, and the path taken in this case.

Input
There can be more than one test case in the input file. The first line has T, the number of test cases.
Then the totally T test cases are provided in the following lines (T ≤ 10 ).

In each test case, In the first line, the size of the maze N (1 ≤ N ≤ 10) is given.
The maze is N×N square-shaped. From the second line through N lines, information of the maze is given.
“0” means a passage, “1” means a wall, and “2” means a location of a jewel. The entrance is located
on the upper-most left passage and the exit is located on the lower-most right passage.
There is no case where the path from the entrance to the exit doesn’t exist.

Output
From the first line through N lines, mark the path with 3 and output it. In N+1 line, output the
greatest number of jewels that can be picked up. Each test case must be output separately as a empty.
*/

#include <iostream>
using namespace std;
int ans;
int maze[20][20];
int n;
int cpy[20][20];

bool valid(int x, int y)
{
    return ((x >= 0 && x < n && y >= 0 && y < n) && (maze[x][y] == 0 || maze[x][y] == 2));
}
int dir[4][2] = {{0, 1}, {1, 0}, {-1, 0}, {0, -1}};
void solve(int x, int y, int cnt)
{
    if (x == n - 1 && y == n - 1)
    {
        if (cnt > ans)
        {
            ans = cnt;
            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < n; j++)
                {
                    cpy[i][j] = maze[i][j];
                }
            }
        }
        return;
    }
    for (int i = 0; i < 4; i++)
    {
        int newX = x + dir[i][0];
        int newY = y + dir[i][1];
        if (valid(newX, newY))
        {
            int temp = maze[newX][newY] / 2;
            maze[newX][newY] = 3;
            solve(newX, newY, cnt + temp);
            maze[newX][newY] = temp * 2;
        }
    }
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
            for (int j = 0; j < n; j++)
            {
                cin >> maze[i][j];
            }
        }
        ans = -1;
        int startAdd = (maze[0][0] == 2) ? 1 : 0;
        maze[0][0] = 3; // mark start visited

        solve(0, 0, startAdd);

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                cout << cpy[i][j] << " ";
            }
            cout << endl;
        }
        cout << ans << endl;
        ;
    }
}
