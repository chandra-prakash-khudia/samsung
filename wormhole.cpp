#include<iostream>
#include<vector>
using namespace std;
// #define inf 1e8
// int n ;
// int graph[100][100];
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

// int main(){
//     int t;
//     cin>>t;
//     while(t--){
//         cin>>n;
//         for(int i = 0 ; i<2*n+2 ; i++){
//             for(int j =0 ; j< 2*n+2; j++){
//                 graph[i][j] = -1;
//             }
//         }
//     int x[2*n+2];
//     int y[2*n+2];
//     for(int i = 0 ; i<2; i++){
//         cin>>x[i]>>y[i];
//     }
//     for(int i = 2 ; i<2*n+2 ;i +=2){
//         int cost;
//         cin>>x[i]>>y[i] >> x[i+1]>>y[i+1]>>cost;
//         graph[i][i+1] = cost;
//         graph[i+1][i] = cost;
//     }
//     for(int  i = 0 ; i<2*n+2 ; i++){
//         for(int j = 0 ; j<2*n+2; j++){
//             int dist = abs(x[i] - x[j]) + abs(y[i] - y[j]);
//             if(graph[i][j] == -1 || graph[i][j] > dist) {
//              graph[i][j] = dist;
//              graph[j][i] = dist;
// }

//         }
//     }
//     solve();
//     }
// }



using ll = long long;
const ll INF = (ll)9e18;

// Manhattan distance between two integer points
inline ll manhattan(pair<int,int> a, pair<int,int> b) {
    return llabs((ll)a.first - b.first) + llabs((ll)a.second - b.second);
}

int main() {

    int sx, sy, tx, ty;
    if (!(cin >> sx >> sy)) return 0; // no input
    cin >> tx >> ty;
    int N; cin >> N;

    // Node indexing:
    // 0 -> source
    // 1 -> target
    // 2 .. 2+2*N-1 -> wormhole endpoints (two nodes per wormhole)
    int nodes = 2 + 2 * N;
    vector<pair<int,int>> pts(nodes);
    pts[0] = {sx, sy};
    pts[1] = {tx, ty};

    vector<int> wormCost(N);
    for (int i = 0; i < N; ++i) {
        int x1, y1, x2, y2, c;
        cin >> x1 >> y1 >> x2 >> y2 >> c;
        pts[2 + 2*i]     = {x1, y1};
        pts[2 + 2*i + 1] = {x2, y2};
        wormCost[i] = c;
    }

    // Build adjacency as a matrix stored in vectors.
    // graph[u][v] = weight (Manhattan or wormhole). -1 means not set yet.
    vector<vector<ll>> graph(nodes, vector<ll>(nodes, -1));

    // Fill walking edges (Manhattan) between every pair
    for (int i = 0; i < nodes; ++i) {
        for (int j = i+1; j < nodes; ++j) {
            ll d = manhattan(pts[i], pts[j]);
            graph[i][j] = d;
            graph[j][i] = d;
        }
    }

    // Insert wormhole edges (both directions) with given cost,
    // but keep the minimum of wormhole cost and walking cost.
    for (int i = 0; i < N; ++i) {
        int u = 2 + 2*i;
        int v = u + 1;
        ll c = wormCost[i];
        if (graph[u][v] == -1 || graph[u][v] > c) {
            graph[u][v] = c;
            graph[v][u] = c;
        }
    }

    // Dijkstra using min-heap
    vector<ll> dist(nodes, INF);
    dist[0] = 0;
    priority_queue<pair<ll,int>, vector<pair<ll,int>>, greater<pair<ll,int>>> pq;
    pq.push({0, 0});

    while (!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        if (d > dist[u]) continue;

        if (u == 1) break; // reached target
        for (int v = 0; v < nodes; ++v) {
            if (graph[u][v] == -1) continue;
            ll w = graph[u][v];
            if (dist[v] > d + w) {
                dist[v] = d + w;
                pq.push({dist[v], v});
            }
        }
    }

    cout << dist[1] << '\n';
    return 0;
}