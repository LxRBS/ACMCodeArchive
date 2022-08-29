#include<bits/stdc++.h>
#define pb push_back
using namespace std;
typedef long long ll;
const int maxn=1e7+5;
typedef vector<int> vi;
int prime[maxn/10],f[maxn],n,Q;
bool p[maxn];
void sieve(int n){
    int cnt=0;
    for (int i=2;i<=n;i++){
        if (!p[i]) prime[++cnt]=i,f[i]=i;
        for (int j=1;j<=cnt&&prime[j]*i<=n;j++){
            p[prime[j]*i]=1;
            f[prime[j]*i]=prime[j];
            if (i%prime[j]==0) break;
        }
    }
}   
int m,ret; 
set<int> S;
vi a;
void pv(int x){
    while (x>1){
        int y=f[x];
        if (S.find(y)==S.end()) S.insert(y);
        while (x%y==0) x/=y;
    }
}
void dfs(int x,int s,int o){
    if (x==m){
        ret+=o*(n/s);
        return;
    }
    dfs(x+1,s,o);
    if (s<=n/a[x]) dfs(x+1,s*a[x],-o);
}
int calc(int x,int y){
    S.clear(); pv(x); pv(y);
    a.clear(); for (auto x:S) a.pb(x);
    m=a.size(); ret=0; 
    dfs(0,1,1);
    return ret;
}
int main(){
    //freopen("input.txt","r",stdin);
    //freopen("output.txt","w",stdout);
    ios::sync_with_stdio(false);
    cin >> n >> Q;
    sieve(n);
    while (Q--){
        int x,y; cin >> x >> y;
        assert(x!=y);
        if (__gcd(x,y)==1){
            cout << 1 << ' ' << 1 << endl;
            continue;
        }
        int ans=calc(x,y);
        if (__gcd(x,y)==2) ans++;
        cout << 2 << ' ' << ans << endl;
    }
    return 0;
}