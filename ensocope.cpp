// ///Raka, a CSE student from IIITG developed an endoscope to explore inner part of ruined water pipes. It is possible explore the inner part of the pipes putting the endoscope into a certain part of the pipe. The endoscope can be moved in the pipes only. Meanwhile, when the pipes are connected to each other, if the length of the endoscope is long enough to explore, it is able to inspect the connected pipe. However, we cannot observe every pipe because the length of the endoscope is limited.

// When the map of the ground water pipe, the location where the endoscope to out in, and the length of the endoscope is given, calculate the number of pipe which are available to explore. Length of endoscope means the range upto which endoscope can explore. There are seven kind of pipes, and description for each pipe are shown below





#include<iostream>
// take intput , create a quere data struecure , add push , pop , emoty operation , define  valid, left, right, up , down
using namespace std;
int M,N, X,Y,L;
int mp[50][50] , vis[50][50];
struct node {
    int xc;
    int yc;
    int rem; // remaining steps
};

node arr[2600];
int front ;
int back;
void init(){
    front=0;
    back = 0;
}
void push(node temp){
  arr[back] = temp;
  back++;
}
node pop(){
    node temp = arr[front];
    front++;
    return temp;
}
bool empty(){
    return front == back;
}

bool valid(int x, int y){
    if(x>=0 && x<M && y>=0 && y<N){
        return true;
    }
    return false;
}
bool left(int x ,int y){
    return (mp[x][y] == 1 || mp[x][y] == 3 || mp[x][y] == 6 || mp[x][y] == 7 );
}
bool right(int x ,int y){
    return (mp[x][y] == 1 || mp[x][y] == 3 || mp[x][y] == 4 || mp[x][y] == 5 );
}
bool up(int x ,int y){
    return (mp[x][y] == 1 || mp[x][y] == 2 || mp[x][y] == 4 || mp[x][y] == 7 );
}
bool bottom(int x ,int y){
    return (mp[x][y] == 1 || mp[x][y] == 2 || mp[x][y] == 5 || mp[x][y] == 6 );
}

int solve(int x , int  y , int l){
    int ans = 0;
    push({x,y,l});
    vis[x][y] = 1;
    while(!empty()){
        node curr = pop();
        int newX = curr.xc;
        int newY = curr.yc;
        int val = curr.rem;
        if(val==0) continue;
        ans++;
        // left
        if(valid(newX,newY-1) && left(newX, newY) && right(newX,newY-1) && !vis[newX][newY-1]){
            push({newX,newY-1, val-1});
            vis[newX][newY-1] = 1;
        }
         if(valid(newX,newY+1) && right(newX,newY)  && left(newX, newY+1) && !vis[newX][newY+1]){
            push({newX,newY+1, val-1});
            vis[newX][newY+1] = 1;
        }
         if(valid(newX-1,newY) && up(newX, newY) && bottom(newX-1,newY) && !vis[newX-1][newY]){
            push({newX-1,newY, val-1});
            vis[newX-1][newY] = 1;
        }
         if(valid(newX+1,newY) && bottom(newX, newY) && up(newX+1,newY) && !vis[newX+1][newY]){
            push({newX+1,newY, val-1});
            vis[newX+1][newY] = 1;
        }
    }
    return ans;
}

int main(){
    int t;
    cin>>t;
    while(t--){
        cin>>M>>N>>X>>Y>>L;
        for(int i =0 ; i<M; i++){
            for(int j = 0 ; j<N;j++){
                cin>>mp[i][j];
                vis[i][j] = 0;
            }
        }
        init();
        if(mp[X][Y] >0){
            cout<<solve(X,Y,L)<<endl;
        }else{
            cout<<0<<endl;
        }

    }
}