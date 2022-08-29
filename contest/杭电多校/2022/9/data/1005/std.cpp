#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn=1e6+10;
const int M=998244353;
int n,m,inv[maxn],res,cof;
int pow_(int x,int y){
    int ret=1;
    while (y){
        if (y&1) ret=1ll*ret*x%M;
        x=1ll*x*x%M; y>>=1;
    }
    return ret;
}
void solve(){
    cin >> n >> m;
    res=1; cof=pow_(n,M-2);
    for (int k=2;k<=m;k++){
        res=1ll*res*(n+k-1)%M*inv[k-1]%M;
        cout << 1ll*(res+M-1)*n%M*inv[k-1]%M*cof%M*k%M << endl;
    }
}
int main(){
    ios::sync_with_stdio(false);
    inv[1]=1; for (int i=2;i<maxn;i++) inv[i]=M-1ll*(M/i)*inv[M%i]%M;
    int T; cin >> T;
    while (T--) solve();
    return 0;
}