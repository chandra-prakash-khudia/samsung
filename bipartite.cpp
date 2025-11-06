#include <iostream>
#include<vector>
using namespace std;
// int n;
// int graph[100][100];

// bool solve(int node, int color[], int clr)
// {

//     color[node] = clr;
//     for (int i = 0; i < n; i++)
//     {
//         if (graph[node][i] == 1)
//         {
//             if (color[i] == -1)
//             {
//                 if (!solve(i, color, 1 - clr))
//                     return false;
//             }
//             else if (color[i] == clr)
//                 return false;
//         }
//     }
//     return true;
// }

// int main()
// {
//     cin >> n;
//     int color[n];
//     for (int i = 0; i < n; i++)
//     {
//         for (int j = 0; j < n; j++)
//         {
//             cin >> graph[i][j];
//         }
//         color[i] = -1;
//     }
//     bool check = true;
//     for (int i = 0; i < n; i++)
//     {
//         if (color[i] == -1)
//         {
//             if (!solve(i, color, 0))
//             {
//                 check = false;
//             }
//         }
//     }
//     if (check)
//     {
//         bool first = true;
//         for (int i = 0; i < n; i++)
//         {
//             if (color[i] == 0)
//             {
//                 if (!first)
//                     cout << " ";
//                 cout << i;
//                 first = false;
//             }
//         }
//         cout << "\n";

//         // print nodes with color 0 in next line
//         first = true;
//         for (int i = 0; i < n; i++)
//         {
//             if (color[i] == 1)
//             {
//                 if (!first)
//                     cout << " ";
//                 cout << i;
//                 first = false;
//             }
//         }
//         cout << "\n";
//     }
//     else
//     {
//         cout << -1 << endl;
//     }
// }


int main() {
  

    // There are 10 test cases
    for(int t = 1; t <= 10; t++){
        int V, E;
        cin >> V >> E;
        vector<vector<int>> adj(V+1);
        // Build adjacency list
        for(int i = 0; i < E; i++){
            int u, v;
            cin >> u >> v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        vector<int> color(V+1, -1);
        bool isBipartite = true;
        vector<int> whiteVertices;

        // BFS-based coloring for each component
        for(int start = 1; start <= V && isBipartite; start++){
            if(color[start] != -1) continue;  // already colored in a previous component

            queue<int> q;
            vector<int> compNodes;
            color[start] = 0;
            q.push(start);
            compNodes.push_back(start);

            // BFS traversal
            while(!q.empty() && isBipartite){
                int u = q.front(); q.pop();
                for(int w : adj[u]){
                    if(color[w] == -1){
                        color[w] = 1 - color[u];
                        q.push(w);
                        compNodes.push_back(w);
                    } else if(color[w] == color[u]){
                        // Found same color on adjacent vertices -> not bipartite
                        isBipartite = false;
                        break;
                    }
                }
            }
            if(!isBipartite) break;

            // Partition this component's nodes by color
            vector<int> part0, part1;
            for(int node : compNodes){
                if(color[node] == 0) part0.push_back(node);
                else part1.push_back(node);
            }
            // Add the smaller part to whiteVertices
            if(part0.size() <= part1.size()) {
                whiteVertices.insert(whiteVertices.end(), part0.begin(), part0.end());
            } else {
                whiteVertices.insert(whiteVertices.end(), part1.begin(), part1.end());
            }
        }

        // Output the result
        cout << "#" << t;
        if(!isBipartite){
            cout << " -1\n";
        } else {
            sort(whiteVertices.begin(), whiteVertices.end());
            cout << " " << whiteVertices.size();
            for(int v : whiteVertices) {
                cout << " " << v;
            }
            cout << "\n";
        }
    }
    return 0;
}
