#include<iostream>
#include<queue>
#include<vector>
#include<algorithm>
#include<set>
#include<utility>
using namespace std;


class Solution {
public:
    int helper(pair<int,int>&a, pair<int,int>&b , pair<int,int>c){
        int xa = a.first , ya = a.second, xb = b.first, yb = b.second , xc = c.first, yc  = c.second;
        return (yc-yb)*(xb-xa) - (yb-ya)*(xc-xb);
    }
    vector<vector<int>> outerTrees(vector<vector<int>>& trees) {
        sort(trees.begin(), trees.end());
        deque<pair<int,int>>upper , lower;
        for(auto &it:trees){
            int u = upper.size();
            int l = lower.size();
            while(u>=2 && helper(upper[u-2], upper[u-1],{it[0] , it[1]}) >0){
                u--;
                upper.pop_back();
            }
            while(l>=2 && helper(lower[l-2],lower[l-1] ,{it[0] , it[1]}) < 0){
                l--;
                lower.pop_back();
            }
            upper.push_back({it[0],it[1]});
            lower.push_back({it[0],it[1]});
            
        }
        vector<vector<int>>ans;
        
        set<pair<int,int>>st;
        for(auto it: upper){
            st.insert({it.first , it.second});
        }

        for(auto it: lower){
            st.insert({it.first , it.second});
        }
        for(auto it : st){
            ans.push_back({it.first, it.second});
        }
        return ans;
    }
};