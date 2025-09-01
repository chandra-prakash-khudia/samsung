#include <iostream>
using namespace std;

int n;

// helper: copy grid into another
void copyGrid(int src[15][5], int dest[15][5], int rows) {
    for(int i=0; i<rows; i++) {
        for(int j=0; j<5; j++) {
            dest[i][j] = src[i][j];
        }
    }
}

int solve(int grid[15][5], int row, int col, int bomb) {
    if(row <= 0 || col < 0 || col >= 5) return 0;

    int res = 0;

    // 3 possible moves: stay, left, right
    for(int d=-1; d<=1; d++) {
        int nc = col + d;
        if(nc >= 0 && nc < 5 && grid[row-1][nc] != 2) {
            res = max(res, (grid[row-1][nc] == 1 ? 1 : 0) + solve(grid, row-1, nc, bomb));
        }
    }

    // if bomb is available
    if(bomb == 1) {
        int newGrid[15][5];
        copyGrid(grid, newGrid, row);  // copy only rows we care about

        // apply bomb in 5x5 above control zone
        int limit = max(0, row-5);
        for(int i=row-1; i>=limit; i--) {
            for(int j=0; j<5; j++) {
                if(newGrid[i][j] == 2) newGrid[i][j] = 0;
            }
        }

        res = max(res, solve(newGrid, row, col, 0));
    }

    return res;
}

int main() {
    int t;
    cin >> t;
    int i=1;
    while(i<=t) {
        cin >> n;
        int arr[15][5];
        for(int i=0; i<n; i++) {
            for(int j=0; j<5; j++) {
                cin >> arr[i][j];
            }
        }
        cout <<"#" << i << " "<<solve(arr, n, 2, 1) << endl;
        i++;
    }
}










