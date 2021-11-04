#include <bits/stdc++.h>
#define pb emplace_back
using namespace std;
const int inf=1e9,N=32;
vector<int> primes;
int f[2][N];
void init(){
    for(int p=2;p*p<=inf;++p){
        int ok=1;
        for(int q=2;q*q<=p;++q) if(p%q==0) { ok=0; break; }
        if(ok) primes.pb(p);
    }
    f[0][0]=0;
    for(int i=0;i<2;++i){
        for(int j=0;j<N;++j){
            if(i||j){
                set<int> s;
                if(i) s.insert(0);
                for(int u=0;u<j;++u) s.insert(f[i][u]);
                while(s.count(f[i][j])) ++f[i][j];
            }
        }
    }
}
int sg(int x){
    //cerr<<"sg "<<x<<":";
    int ord[2]={0,0};
    for(int u:primes){
        if(u*u>x) break;
        while(x%u==0) ++ord[u>2],x/=u;
    }
    if(x>1) ++ord[x>2];
    //cerr<<f[ord[0]>0][ord[1]]<<"\n";
    return f[ord[0]>0][ord[1]];
}
int main(){
    int t; scanf("%d",&t); init();
    while(t--){
        int m,s=0,x; scanf("%d",&m);
        while(m--) scanf("%d",&x),s^=sg(x);
        printf("%c\n","WL"[!s]);
    }
}