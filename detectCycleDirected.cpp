#include <iostream>
using namespace std;

int n, m;
int graph[11][11];
int path[11];
bool visited[11];
int cycles[100][11]; // store up to 100 cycles
int cycleLen[100];
int cycleCount = 0;



void store(int idx, int depth)
{
    int temp[11], len = 0;
    for (int i = idx; i <= depth; i++)
    {
        temp[len++] = path[i];
    }
    // stored the path in temp
    // check whether this cycle
    for (int i = 0; i < cycleCount; i++)
    {
        if (cycleLen[i] == len)
        {
            bool found = true;
            for (int k = 0; k < len; k++)
            {
                if (cycles[i][k] != temp[k])
                {
                    found = false;
                    break;
                }
            }
            if (found)
                return;
        }
    }
    for (int i = 0; i < len; i++)
    {
        cycles[cycleCount][i] = temp[i];
    }
    cycleLen[cycleCount] = len;
    cycleCount++;
}



void dfs(int u, int depth)
{
    visited[u] = true;
    path[depth] = u;
    for (int v = 1; v <= n; v++)
    {
        if (graph[u][v])
        {
            if (!visited[v])
                dfs(v, depth + 1);
            else
            {
                for (int i = 0; i <= depth; i++)
                {
                    if (path[i] == v)
                    {
                        store(i, depth);
                        break;
                    }
                }
            }
        }
    }
    visited[u] = false;
}
void sortArray(int arr[], int len)
{
    for (int i = 0; i < len; i++)
    {
        for (int j = i + 1; j < len; j++)
        {
            if (arr[j] < arr[i])
            {
                int tmp = arr[i];
                arr[i] = arr[j];
                arr[j] = tmp;
            }
        }
    }
}

int main()
{
    cin >> n >> m;

    // init
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
            graph[i][j] = 0;
        visited[i] = false;
    }

    for (int i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;
        graph[u][v] = 1;
    }

    // run dfs from each node
    for (int i = 1; i <= n; i++)
    {
        dfs(i, 0);
    }

    if (cycleCount == 0)
    {
        cout << -1 << endl;
        return 0;
    }

    // find cycle with minimum sum
    int bestIdx = 0, minSum = 1e9;
    for (int c = 0; c < cycleCount; c++)
    {
        int sum = 0;
        for (int j = 0; j < cycleLen[c]; j++)
            sum += cycles[c][j];
        if (sum < minSum)
        {
            minSum = sum;
            bestIdx = c;
        }
    }

    // sort the chosen cycle
    sortArray(cycles[bestIdx], cycleLen[bestIdx]);

    // print
    for (int j = 0; j < cycleLen[bestIdx]; j++)
    {
        cout << cycles[bestIdx][j] << (j + 1 == cycleLen[bestIdx] ? '\n' : ' ');
    }

    return 0;
}
// /* https://sapphireengine.com/@/6tfphj */
// /* https://cses.fi/problemset/task/1678 */
// #include<iostream>
// using namespace std;

// int graph[100][100];
// int n;

// bool dfs( int node , bool *visited , bool *inloop , int &prev ){
// 	visited[node] = 1;
// 	inloop[node] = 1;
//     for(int i=0;i<n;i++){
// 	    if( graph[node][i]){
// 	      	if(!visited[i]){
// 	      		if(dfs( i , visited , inloop , prev)){

// 				    if(i==prev)
// 	      	 	 	    cout<<i<<" " , prev=-1;
// 	      	 	    else if (prev!=-1)
// 					    cout<<i<<" ";

// 	      	 	    return true;
// 	      	    }
// 			}
// 			else if ( inloop[i] ){
// 				    prev=i;
// 			 	    return true;
// 		    }
// 	    }
//     }

//     inloop[node]=0;
// 	return false;
// }

// bool checkCycle (bool *visited){
//     int prev = -1;
//     bool inloop[100] = {false};  // Use fixed size array, assuming n <= 100

// 	for(int i=0; i<n; i++)
// 	    if( !visited[i] && dfs(i,visited, inloop, prev))
// 	        return true;

// 	return false;
// }

// int main(){
// 	// Input nodes
// 	cin>>n;
// 	for(int i=0;i<n;i++)
// 	    for(int j=0;j<n;j++)
// 	        graph[i][j]=0;

// 	// Input Edges
// 	int t;
// 	cin>>t;
// 	int x,y;
// 	for(int i=0;i<t;i++){
// 		cin>>x>>y;
// 		graph[x][y]=1;
// 	}

//     bool visited[100] = {false};  // Use fixed size array, assuming n <= 100

// 	cout<<checkCycle(visited)<<endl;

// 	return 0;
// }