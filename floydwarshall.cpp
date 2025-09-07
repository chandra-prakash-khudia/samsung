#include <iostream>
using namespace std;
#define inf 1e8
int n;
int graph[100][100];
// int findMin(int vis[], int dis[]){
//     int node=-1;
//     int val = inf;
//     for(int i =0 ; i<2*n+2; i++){
//         if(dis[i] != inf && vis[i]==0 && dis[i] < val){
//             val = dis[i];
//             node = i;
//         }
//     }
//     return node;
// }
// void solve(){
//     int vis[2*n+2];
//     int dis[2*n+2];
//     for(int i =0 ; i<2*n+2; i++){
//         vis[i] = 0;
//         dis[i] = inf;
//     }
//     dis[0] = 0;
//     for(int i =0 ; i<2*n+1; i++){
//         int u = findMin(vis, dis);
//         vis[u] = 1;
//         for(int v = 0 ; v<2*n+2; v++){
//             if(dis[u] != inf && graph[u][v] !=-1 && vis[v] ==0 && dis[u] + graph[u][v] < dis[v]){
//                 dis[v]= dis[u]+ graph[u][v];
//             }
//         }
//     }
//     cout<<dis[1]<<endl;
// }

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        cin >> n;
        for (int i = 0; i < 2 * n + 2; i++)
        {
            for (int j = 0; j < 2 * n + 2; j++)
            {
                graph[i][j] = -1;
            }
        }
        int x[2 * n + 2];
        int y[2 * n + 2];
        for (int i = 0; i < 2; i++)
        {
            cin >> x[i] >> y[i];
        }
        for (int i = 2; i < 2 * n + 2; i += 2)
        {
            int cost;
            cin >> x[i] >> y[i] >> x[i + 1] >> y[i + 1] >> cost;
            graph[i][i + 1] = cost;
            graph[i + 1][i] = cost;
        }
        for (int i = 0; i < 2 * n + 2; i++)
        {
            for (int j = 0; j < 2 * n + 2; j++)
            {
                int dist = abs(x[i] - x[j]) + abs(y[i] - y[j]);
                if (graph[i][j] == -1 || graph[i][j] > dist)
                {
                    graph[i][j] = dist;
                    graph[j][i] = dist;
                }
            }
        }
        for(int k = 0; k<2*n+2; k++){
            for(int i =0 ; i<2*n+2;i++){
                for(int j = 0 ; j<2*n+2; j++){
                    if(graph[i][k] != -1 && graph[k][j] !=-1 && graph[i][j] > graph[i][k] + graph[k][j]){
                        graph[i][j] = graph[i][k] + graph[k][j];
                    }
                }
            }
        }
        cout << graph[0][1] << '\n';

    }
}