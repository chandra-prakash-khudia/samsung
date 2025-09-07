/*
https://www.cnblogs.com/kingshow123/p/practicec2.html
http://www.voidcn.com/article/p-mpfarobd-bgr.html
*/

/*
There is a mobile piece and a stationary piece on the N×M chessboard.
The available moves of the mobile piece are the same as set out in the image below.
You need to capture the stationary piece by moving the mobile piece with the minimum amount of moves.

Write a program to find out the minimum number moves to catch a piece.

[Input]
Several test cases can be included in the inputs. T, the number of cases is given in the first row of the
inputs. After that, the test cases as many as T (T ≤ 20) are given in a row.
N, the numbers of the rows and M, the number of columns of the chessboard are given in the first row of
each test case.
R & C is the location information of the attacking piece and S & K is the location of the defending pieces
and are given in the row at the second line. However, the location of the uppermost end of the left end
is (1, 1)

[Output]
For each test case, you should print "Case #T" in the first line where T means the case number.

For each test case, you should output the minimum number of movements to catch a defending piece at the
first line of each test case. If not moveable, output equals ‘-1’.

[I/O Example]

Input
2
9 9
3 5 2 8
20 20
2 3 7 9

Output
Case #1
2
Case #2
5
*/

#include <iostream>
using namespace std;
int maxi = 30;
int chess[30][30];
int n, m;
struct node
{
    int x;
    int y;
    int level;
};
int front, back;
void init()
{
    front = 0;
    back = 0;
}
node q[1000];
void push(node temp)
{
    q[back++] = temp;
}
node pop()
{
    node temp = q[front];
    front++;
    return temp;
}
bool isEmpty()
{
    return front == back;
}
bool valid(int x, int y)
{
    return (x > 0 && x <= n && y > 0 && y <= m && chess[x][y] == 0);
}
int solve(int dx, int dy, int sx, int sy)
{
    push({sx, sy, 0});
    chess[sx][sy] = -1;
    int moves[8][2] = {
        {-2, -1}, {-2, +1}, {-1, -2}, {-1, +2}, {+1, -2}, {+1, +2}, {+2, -1}, {+2, +1}};

    while (!isEmpty())
    {
        node front = pop();
        int x = front.x;
        int y = front.y;
        int lvl = front.level;
        if (x == dx && y == dy)
            return lvl;
        for (int i = 0; i < 8; i++)
        {
            int nx = x + moves[i][0];
            int ny = y + moves[i][1];
            if (valid(nx, ny))
            {
                push({nx, ny, lvl + 1});
                chess[nx][ny] = -1;
            }
        }
    }
    return -1;
}
int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        cin >> n >> m; //. row col
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= m; j++)
            {
                chess[i][j] = 0;
            }
        }
        init();
        int sx, sy, kx, ky;
        cin >> sx >> sy >> kx >> ky;
        int ans = solve(sx, sy, kx, ky);
        cout << ans << endl;
    }
}
