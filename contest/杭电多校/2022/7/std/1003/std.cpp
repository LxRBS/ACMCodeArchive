#include<bits/stdc++.h>

using namespace std;

#define gc c=getchar()
#define r(x) read(x)
#define ll long long

template<typename T>
inline void read(T &x){
    x=0;T k=1;char gc;
    while(!isdigit(c)){if(c=='-')k=-1;gc;}
    while(isdigit(c)){x=x*10+c-'0';gc;}x*=k;
}

const int N=1e7+7;
const int p=998244353;

vector<int>G[N];
int deg[N];
int s0[N];
int s1[N];
int s2[N];

inline int add(int a,int b){
    return (a+=b)>=p?a-p:a;
}

inline int sub(int a,int b){
    return (a-=b)<0?a+p:a;
}

inline ll calc(int x){
    return (ll)x*(x-1)/2%p;
}

int main(){
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    int T;
    r(T);
    while(T--){
    int n;r(n);
    for(int i=1;i<=n;++i)G[i].clear(),deg[i]=s0[i]=s1[i]=s2[i]=0;
    for(int i=1;i<n;++i){
        int u,v;r(u),r(v);
        G[u].push_back(v);
        G[v].push_back(u);
        ++deg[u],++deg[v];
    }
    for(int x=1;x<=n;++x){
        s0[x]=deg[x];
        for(auto &y:G[x]){
            s1[x]=add(s1[x],deg[y]-1);
            s2[x]=add(s2[x],calc(deg[y]-1));
        }
    }
    int ans=0;
    for(int x=1;x<=n;++x){
        if(s0[x]>=4){
            for(auto &y:G[x]){
                if(s0[y]>=3){
                    int head=sub(s0[x],3);
                    int foot=sub(s0[y],1);
                    int hand=sub(s1[x],foot);
                    ans=add(ans,(ll)head*sub(calc(hand),sub(s2[x],calc(deg[y]-1)))%p*calc(foot)%p);
                }
            }
        }
    }
    printf("%d\n",ans);
    }
    return 0;
}