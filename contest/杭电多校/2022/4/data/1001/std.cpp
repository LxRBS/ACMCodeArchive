#include <cstdio>
#include <cstring>
#define MN 500

using ll = long long;

const int mod = 1000000007;

int n,m;
int a[MN+5];
int f[MN+5][MN+5],g[MN+5][MN+5];

void solve(){
    memset(f,0,sizeof(f));
    memset(g,0,sizeof(g));
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
    }
    if(n&1){
        puts("0");
        return;
    }
    for(int i=0;i<=n;i++){
        g[i+1][i] = 1;
    }
    for(int len=2;len<=n;len+=2){
        for(int l=1;l+len-1<=n;l++){
            int r = l+len-1;
            if(a[l]>=0&&a[r]<=0){
                int e;
                if(a[l]==0&&a[r]==0){
                    e = m;
                }else if(a[l]==0||a[r]==0){
                    e = 1;
                }else if(a[l]+a[r]==0){
                    e = 1;
                }else{
                    e = 0;
                }
                f[l][r] = (ll)g[l+1][r-1]*e%mod;
            }
            for(int nl=l;nl<=r;nl+=2){
                g[l][r] = (g[l][r]+(ll)g[l][nl-1]*f[nl][r])%mod;
            }
        }
    }
    printf("%d\n",g[1][n]);
}

int main(){
    int T;
    scanf("%d",&T);
    //T = 1;
    while(T--) solve();
}
