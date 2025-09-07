#include <iostream>
using namespace std;
int map[20][20];
bool vis[20][20];
int element[5][2];
int n, rare;
int front, back;
struct node
{
    int x, y, l;
};
node q[2000];
void init()
{
    front = back = 0;
    return;
}
void init2()
{
    for (int i = 0; i < 20; i++)
    {
        for (int j = 0; j < 20; j++)
        {
            vis[i][j] = 0;
        }
    }
    return;
}

void push(node temp)
{
    q[back++] = temp;
    return;
}
node pop()
{
    node temp = q[front];
    front++;
    return temp;
}
bool empty()
{
    return front == back;
}

bool isValid(int r, int c)
{
    return (r >= 0 && r < n && c >= 0 && c < n && map[r][c] == 1 && !vis[r][c]);
}
int dir[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
int bfs(int sx, int sy, int dx, int dy)
{
    node temp = {sx, sy, 0};
    push(temp);
    vis[sx][sy] = 1;
    while (!empty())
    {
        node frn = pop();
        if (frn.x == dx && frn.y == dy)
            return frn.l;
        for (int i = 0; i < 4; i++)
        {
            int newX = dir[i][0] + frn.x;
            int newY = dir[i][1] + frn.y;
            if (isValid(newX, newY))
            {
                node tt = {newX, newY, frn.l + 1};
                push(tt);
                vis[newX][newY] = 1;
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
        cin >> n >> rare;

        for (int i = 0; i < rare; i++)
        {
            int x, y;
            cin >> x >> y;
            element[i][0] = x-1;
            element[i][1] = y-1;
        }
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                cin >> map[i][j];
                vis[i][j] = 0;
            }
        }
        int ans = 1e6;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (map[i][j] == 1)
                {
                    int temp = 0;
                    for (int k = 0; k < rare; k++)
                    {
                        init();
                        init2();
                        temp = max(temp, bfs(i, j, element[k][0], element[k][1]));
                    }
                    ans = min(ans, temp);
                }
            }
        }

        cout << ans << endl;
    }
}