#include <iostream>
using namespace std;

int grid[100][100];
int used[100];

int main() {
    int n, m, k;
    cin >> n >> m >> k;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> grid[i][j];
        }
        used[i] = 0; 
    }

    int maxi = -1;

    for (int i = 0; i < n; i++) {
        if (used[i]) continue; 

 
        int zeros = 0;
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == 0) zeros++;
        }

        if (zeros <= k && (k - zeros) % 2 == 0) {
            int countRows = 1;
            used[i] = 1;

            // compare with other rows
            for (int r = i + 1; r < n; r++) {
                if (used[r]) continue;

                bool same = true;
                for (int c = 0; c < m; c++) {
                    if (grid[i][c] != grid[r][c]) {
                        same = false;
                        break;
                    }
                }

                if (same) {
                    used[r] = 1;
                    countRows++;
                }
            }
            if (countRows > maxi) maxi = countRows;
        }
    }

    cout << maxi << endl;
    return 0;
}
