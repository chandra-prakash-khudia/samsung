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










// #include<iostream>
// using namespace std;

// void maxCoins(int arr[6][5],int crow,int ccol,int temp,int &ans,int bomb,int effect){
// 	if(crow == -1){
// 		if(temp > ans){
// 			ans = temp;
// 		}
// 		return;
// 	}
// 	for(int i=-1;i<=1;i++){
// 		if((ccol+i) < 0 || (ccol+i) > 4)
// 			continue;
// 		if(arr[crow][ccol+i] == 1 || arr[crow][ccol+i] == 0){//No enemy
// 			if(bomb == 0){
// 				maxCoins(arr,crow-1,ccol+i,temp+arr[crow][ccol+i],ans,bomb,effect-1);//If bomb has already been used, reduce its effect by 1
// 			}else{
// 				maxCoins(arr,crow-1,ccol+i,temp+arr[crow][ccol+i],ans,bomb,effect);
// 			}
			
// 		}else{//Enemy
// 			if(bomb == 0){
// 				if(effect > 0){
// 					maxCoins(arr,crow-1,ccol+i,temp,ans,bomb,effect-1);//Bomb already used so can pass but effect reduces by 1
// 				}
// 			}else{
// 				maxCoins(arr,crow-1,ccol+i,temp,ans,0,5); //Use bomb ans set effect for five rows
// 			}
// 		}
// 	}
// 	return;
// }