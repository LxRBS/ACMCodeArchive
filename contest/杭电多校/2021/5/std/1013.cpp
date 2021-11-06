#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define rep(i, a, b) for(int i=(a); i<(b); i++)
#define per(i, a, b) for(int i=(b)-1; i>=(a); i--)
#define sz(a) (int)a.size()
#define de(a) cout << #a << " = " << a << endl
#define dd(a) cout << #a << " = " << a << " "
#define all(a) a.begin(), a.end()
#define pw(x) (1ll<<(x))
#define endl "\n"
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef double db;
const int N=1e5+5;
const ll MAX=1e11;
vector<pii> v[N];
int a[N];
ll l,r,mid;
ll dp[N][2];
void dfs(int now,int pre){
    dp[now][0]=dp[now][1]=0;
    for(auto i:v[now]){
        int to=i.first,w=i.second;
        if(to==pre) continue;
        dfs(to,now);
        if(dp[now][0]+min(dp[to][1]+max(0,w-a[now]),dp[to][0]+max(0,w-a[to]-a[now]))<=mid){
            if(dp[now][1]+min(dp[to][1]+w,dp[to][0]+max(0,w-a[to]))<=mid)
            dp[now][1]=max(dp[now][1],min(max(dp[now][0],min(dp[to][1]+max(0,w-a[now]),dp[to][0]+max(0,w-a[to]-a[now]))),min(dp[to][1]+w,dp[to][0]+max(0,w-a[to]))));
            else dp[now][1]=max(dp[now][0],min(dp[to][1]+max(0,w-a[now]),dp[to][0]+max(0,w-a[to]-a[now])));
        }
        else if(dp[now][1]+min(dp[to][1]+w,dp[to][0]+max(0,w-a[to]))<=mid)
        dp[now][1]=max(dp[now][1],min(dp[to][1]+w,dp[to][0]+max(0,w-a[to])));
        else dp[now][1]=MAX;
        if(dp[now][0]+min(dp[to][1]+w,dp[to][0]+max(0,w-a[to]))<=mid)
        dp[now][0]=max(dp[now][0],min(dp[to][1]+w,dp[to][0]+max(0,w-a[to])));
        else dp[now][0]=MAX;
    }
} 
int main(){
    int t;
    scanf("%d",&t);
    while(t--){
        int n;
        scanf("%d",&n);
        for(int i=1;i<=n;i++){
            scanf("%d",&a[i]);
        }
        l=0,r=0;
        for(int i=1;i<n;i++){
            int x,y,z;
            scanf("%d%d%d",&x,&y,&z);
            v[x].pb({y,z});v[y].pb({x,z});
            r+=z; 
        }
        ll ans=-1;
        while(l<=r){
            mid=(l+r)/2;
            dfs(1,0);
            if(dp[1][0]<=mid||dp[1][1]<=mid){
                ans=mid;
                r=mid-1;
            }
            else{
                l=mid+1;
            }
        }
        printf("%lld\n",ans);
        for(int i=1;i<=n;i++){
            v[i].clear(); 
        }
    } 
}
  