#include <cstdio>
#include <cstring>
#include <algorithm>
#define MN 5000
#define MM 20

using std::max;

using ll = long long;

const int INF = 1000000001;

namespace GTI
{
    char gc(void)
       {
        const int S = 1 << 16;
        static char buf[S], *s = buf, *t = buf;
        if (s == t) t = buf + fread(s = buf, 1, S, stdin);
        if (s == t) return EOF;
        return *s++;
    }
    ll gti(void)
       {
        ll a = 0, b = 1, c = gc();
        for (; !isdigit(c); c = gc()) b ^= (c == '-');
        for (; isdigit(c); c = gc()) a = a * 10 + c - '0';
        return b ? a : -a;
    }
    int gts(char *s)
       {
        int len = 0, c = gc();
        for (; isspace(c); c = gc());
        for (; c != EOF && !isspace(c); c = gc()) s[len++] = c;
        s[len] = 0;
        return len;
    }
    int gtl(char *s)
       {
        int len = 0, c = gc();
        for (; isspace(c); c = gc());
        for (; c != EOF && c != '\n'; c = gc()) s[len++] = c;
        s[len] = 0;
        return len;
    }
}
using GTI::gti;
using GTI::gts;
using GTI::gtl;

int n,m,k;

struct Matrix{
    int a[MM+2][MM+2];
    
    Matrix(int x=0){
        memset(a,0,sizeof(a));
        for(int i=1;i<=m;i++){
            a[i][i] = x;
        }
    }
    
    Matrix operator * (const Matrix& that)const{
        Matrix ret;
        for(int i=1;i<=m;i++){
            for(int j=1;j<=m;j++){
                for(int k=1;k<=m;k++){
                    ret.a[i][j] = limit(ret.a[i][j]+(ll)this->a[i][k]*that.a[k][j]);
                }
            }
        }
        return ret;
    }
    
    static int limit(ll x){
        if(x>=INF) return INF;
        else return x;
    }
    
};

Matrix d[MN+5],b[MN+5];

bool check(const Matrix& lhs,const Matrix& rhs){
    int ans = 0;
    for(int i=1;i<=m;i++){
        ans = Matrix::limit(ans+(ll)lhs.a[1][i]*rhs.a[i][m]);
    }
    return ans<=k;
}

void solve(){
    n = gti();
    m = gti();
    k = gti();
    for(int i=1;i<=n;i++){
        int l = gti();
        d[i] = 1;
        while(l--){
            int u = gti();
            int v = gti();
            d[i].a[u][v] = 1;
        }
    }
    int ans = 0;
    Matrix csuf = 1;
    b[0].a[1][m] = INF;
    for(int r=1,l=0,lim=0;r<=n;r++){
        csuf = csuf*d[r];
        while(!check(b[l],csuf)){
            l++;
            if(l>lim){
                b[r] = d[r];
                for(int i=r-1;i>lim;i--){
                    b[i] = d[i]*b[i+1];
                }
                lim = r;
                csuf = 1;
            }
        }
        ans = max(ans,r-l+1);
    }
    printf("%d\n",ans);
}

int main(){
    int T = gti();
    while(T--) solve();
}
