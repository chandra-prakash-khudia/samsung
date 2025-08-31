#include<iostream>

#include <cstring>

using namespace std;

int abs(int i){
    if(i>0){
        return i;
    }
return -i;
}
int n,ans,x[20],y[20];
int dis(int i ,int j){
    return abs(x[i]-x[j]) + abs(y[i]-y[j]);
}

void helper(int x ,bool vis[], int nodes, int val){
    if(nodes==n){
        ans = min(ans, val+dis(x,n+1));
        return ;
    }
    for(int i =1; i<=n; i++){
        if(!vis[i]){
            vis[i] = true;
            helper(i,vis, nodes+1, val + dis(x,i));
            vis[i] = false;
        }
    }
}
int main(){
    int t=1;
    while(t<=10){
        cin>>n;
        cin>>x[n+1]>>y[n+1] >> x[0]>>y[0];
        for(int i =1 ; i<=n ; i++){
            cin>>x[i]>>y[i];
        }
        ans = 1e8;
     bool vis[n+2];
     memset(vis,false,sizeof(vis));
     helper(0,vis,0,0);
     cout<<"# " <<t<<" "<<ans<<endl;
        t++;

    }
}