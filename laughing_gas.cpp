#include <iostream>
using namespace std;
#define qsize 10000
int m, n, bx, by;
int graph[100][100], vis[100][100];
int mv[4][2] = {{1,0},{0,1},{-1,0},{0,-1}};

struct point{
    int x, y, l;
};

bool valid(int x, int y){
    return (x>=0 && x < m)&& (y >= 0 && y<n);
}

struct queue{
    point arr[qsize];
    int front, rear, len;
    void init(){front = 0;rear = -1; len = 0;}
    point pop(){
        point temp = arr[front];
        front = (front+1)%qsize;
        len--;
        return temp;

    }
    void push(point x){
        rear = (rear+1)%qsize;
        arr[rear] = x;
        len++;
    }
    bool empty(){return len == 0;}
} q;


int solve(){
    int ans = 0;
    q.init();
    q.push({bx, by, 0});
    vis[bx][by] = 1;
    while(!q.empty()){
        point p = q.pop();
        ans = max(ans, p.l);
        for(int i = 0;i<4;i++){
            int x = p.x+mv[i][0], y = p.y+mv[i][1];
            if(valid(x, y) && !vis[x][y] && graph[x][y] == 1){
                vis[x][y] = 1;
                q.push({x,y, p.l+1});
            }
        }
    }
    return ans;
}

int main(){
    int t;
    cin>>t;
    while(t--){
        cin>>n>>m;
        for(int i = 0;i<m;i++){
            for(int j = 0;j<n;j++){
                cin>>graph[i][j];
                vis[i][j] = 0;

            }
        }
        cin>>bx>>by;
        bx--;
        by--;
        cout<<solve()<<endl;
    }

}
