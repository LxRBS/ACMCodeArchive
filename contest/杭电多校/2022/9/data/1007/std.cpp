#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int M=998244353;
int n,k,r,a[5005],dp[5005][5005];
void solve(){
    memset(dp,0,sizeof(dp));
    cin >> n >> k >> r;
    for (int i=1;i<=n;i++) cin >> a[i];
    int p=0; dp[0][0]=1;
    for (int i=1;i<=n;i++){
        while (p+1<i&&a[p+1]+r<=a[i]) ++p;
        int s=i-p-1;
        for (int j=s+1;j<=i;j++)
            dp[i][j]=(1ll*(j-s)*dp[i-1][j]+dp[i-1][j-1])%M;
    }
    cout << dp[n][k] << endl;
}
int main(){
    //freopen("input.txt","r",stdin);
    //freopen("output.txt","w",stdout);
    int T; cin >> T;
    while (T--) solve();
}