#include <bits/stdc++.h>
using namespace std;

using ll=long long;
#define rep(i,n) for(int i=0;i<n;i++)
#define MAX_N 100005

ll n,p[MAX_N*2],c[MAX_N*2],ans,dp[2][MAX_N*2][2];
bool vis[MAX_N*2];
ll solve(ll v){
    if(p[p[v]]==v){
        vis[v]=true;
        vis[p[v]]=true;
        return c[v]+c[p[v]];
    }
    dp[1][v][1]=c[v];
    ll u;
    rep(i,2){
        u=v;
        vis[u]=true;
        while(p[u]!=v){
            dp[i][p[u]][0]=max(dp[i][u][0],dp[i][u][1]);
            dp[i][p[u]][1]=dp[i][u][0]+c[p[u]];
            u=p[u];
            vis[u]=true;
        }
    }
    return max(dp[0][u][1],dp[1][u][0]);
}
int main(){
    cin>>n;
    rep(i,n){
        cin>>p[i];
        p[i]--;
        p[i]+=n;
    }
    rep(i,n)p[i+n]=i;
    rep(i,n*2){
        cin>>c[i];
        ans+=c[i];
    }
    rep(i,n*2){
        if(!vis[i])ans-=solve(i);
    }
    cout<<ans<<endl;
}
