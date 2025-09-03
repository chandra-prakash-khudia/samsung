#include <iostream>
using namespace std;

int graph[50][50];
int n, m;

int vis[50];
int inrec[50];
int parent[50];

int tempCycle[50];
int tempSize = 0;

int bestCycle[50];
int bestSize = 0;
int bestSum = 1e8;
bool found = false;


void cycle(int j){
    vis[j] = 1;
    inrec[j] =1;
    for(int i = 0;i<n;i++){
        if(graph[j][i] == 0)continue;

        if(!vis[i]){
            parent[i] = j;
            cycle(i);
        }
        else if(inrec[i]){
            int sum = i;
            int sz = 0;
            tempCycle[sz++] = i;
            for(int k = j;k != i; k = parent[k]){
                tempCycle[sz++] = k;
                sum+=k;
            }

            if(bestSum > sum){
                bestSum = sum;
                bestSize = sz;
                for(int p = 0;p<sz;p++)bestCycle[p] = tempCycle[p];
                found = true;
            }

        }
    }

    inrec[j] = 0;
}

int main(){
    cin>>n;
    cin>>m;
    for(int i =0;i<n;i++){
        for(int j = 0;j<n;j++){
            graph[i][j] = 0;
        }
    }
    for(int i =0;i<m;i++){
        int x, y;
        cin>>x>>y;
        graph[x][y] = 1;
    }

    for(int i =0;i<n;i++){
        vis[i] = 0;
        inrec[i] = 0;
        parent[i] = -1;
    }

    for(int i = 0;i<n;i++){
        if(!vis[i]){
            parent[i] = -1;
            vis[i] = 1;
            inrec[i] = 1;
            cycle(i);
            inrec[i] = 0;
        }
    }
    if(!found)cout<<"no cycle\n";
    else {
        for(int i = 0;i<bestSize;i++){
            cout<<bestCycle[i]<<" ";
        }
        cout<<endl;
    }
}
