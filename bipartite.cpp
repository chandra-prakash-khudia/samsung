#include <iostream>
using namespace std;
int n;
int graph[100][100];

bool solve(int node, int color[], int clr)
{

    color[node] = clr;
    for (int i = 0; i < n; i++)
    {
        if (graph[node][i] == 1)
        {
            if (color[i] == -1)
            {
                if (!solve(i, color, 1 - clr))
                    return false;
            }
            else if (color[i] == clr)
                return false;
        }
    }
    return true;
}

int main()
{
    cin >> n;
    int color[n];
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> graph[i][j];
        }
        color[i] = -1;
    }
    bool check = true;
    for (int i = 0; i < n; i++)
    {
        if (color[i] == -1)
        {
            if (!solve(i, color, 0))
            {
                check = false;
            }
        }
    }
    if (check)
    {
        bool first = true;
        for (int i = 0; i < n; i++)
        {
            if (color[i] == 0)
            {
                if (!first)
                    cout << " ";
                cout << i;
                first = false;
            }
        }
        cout << "\n";

        // print nodes with color 0 in next line
        first = true;
        for (int i = 0; i < n; i++)
        {
            if (color[i] == 1)
            {
                if (!first)
                    cout << " ";
                cout << i;
                first = false;
            }
        }
        cout << "\n";
    }
    else
    {
        cout << -1 << endl;
    }
}