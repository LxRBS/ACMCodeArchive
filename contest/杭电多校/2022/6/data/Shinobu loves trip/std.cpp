#include<bits/stdc++.h>
#define ll long long
#define all(x) x.begin(),x.end()
using namespace std;
int qm(int a, int b, const int P){
    int res = 1;
    while(b){
        if(b&1) res = (ll)res*a%P;
        a = (ll)a*a%P;
        b >>= 1;
    }return res;
}
ll P; int a;
int n, q;
const int maxn = 2e5 + 5;
void sol1(){
    unordered_map<int, int> f;
    ll cur = 1; int len = 0;
    while(len<maxn && !f.count(cur)){
        f[cur] = len;
        cur = (ll)cur*a%P;
        len++;
    }
    vector<int> s(n), is(n);
    vector<int> d(n);
    for(int i = 0; i < n; ++i){
        cin>>s[i]>>d[i];
        assert(s[i] < P && s[i] >= 0);
        assert(d[i] <= 200000 && d[i] >= 1);
        if(s[i]) is[i] = qm(s[i], P-2, P);
    }
    while(q--){
        ll x; cin>>x;
        assert(x >= 0 && x < P);
        int ans = 0;
        if(x == 0){
            for(int i = 0; i < n; ++i) if(s[i]==0) ans++;
        }else{
            for(int i = 0; i < n; ++i){
                if(s[i] == 0) continue;
                ll ak = (ll)x * is[i] % P;
                if(f.count(ak) && f[ak] <= d[i]) ans++;
            }
        }
        cout<<ans<<endl;
    }
}
int main(){
    int T = 1; cin>>T; assert(T <= 5 && T > 0);
    while(T--){
        cin>>P>>a;
        assert(P > 2 && P <= 1e9+7);
        assert(a >= 2 && a < P);
        cin>>n>>q;
        assert(n <= 1000 && n > 0);
        assert(q <= 1000 && q > 0);
        
        sol1();
    }
    return 0;
}