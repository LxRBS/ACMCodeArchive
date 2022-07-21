#include<bits/stdc++.h>
using namespace std;
#define LL long long
#define pb push_back

LL M=998244353;
const int N=1e5+10;

char ss[1<<24],*A=ss,*B=ss;
char gc()
{
  return (A==B&&(B=(A=ss)+fread(ss,1,1<<20,stdin),A==B)?EOF:*A++);
}
int read()
{
	int x=0;
	char c;
	while (c=gc(),c<48||c>57) ; x=c-48;
  while (c=gc(),47<c&&c<58) x=x*10+c-48;
  return x;
}


vector<int> factor[N];

void add(LL &x,LL y){
    x+=y;
    if(x>=M) x-=M;
}

bool is_pri[N+10];
LL pri[60000];
int mu[N+10];
int cntp=0;

void init_pri(){
    mu[1]=1;
    for(int i=2;i<=N;++i){
        if(!is_pri[i]) {
            pri[++cntp]=i;
            mu[i]=-1;
        }
        for(int j=1;j<=cntp&&pri[j]*i<=N;++j){
            is_pri[pri[j]*i]=1;
            if(i%pri[j]==0) {
                mu[pri[j]*i]=0;
                break;
            }
            else{
                mu[pri[j]*i]=-mu[i];
            }
        }
    }
}


void init(){
    for(int i=1;i<=100000;++i) factor[i].clear();
    for(int i=1;i<=100000;++i){
        for(int j=i;j<=100000;j+=i){
            factor[j].pb(i);
        }
    }
    init_pri();
}

int n,m,K;
int num,tp,cnt;
struct edge{
    int u,v;
};
bool Flag;
int Sum;
vector<edge> U[N];
vector<int> a[N],b[N+N];
int dfn[N],low[N],q[N],cf[N];

void Tarjan(int x,int fa){
    int y;
    dfn[x]=low[x]=++num;cf[x]=0;
    q[++tp]=x;
    for(int i=0;i<a[x].size();++i){
        y=a[x][i];
        if(!dfn[y]){
            Tarjan(y,x);
            cf[x]+=cf[y];
            low[x]=min(low[x],low[y]);
            if(low[y]==dfn[x]){
                ++cnt;b[cnt].clear();
                for(int j=0;j!=y;){
                    b[cnt].push_back(q[tp]);
                    b[q[tp]].push_back(cnt);
                    j=q[tp];--tp;
                }
                b[cnt].push_back(x);
                b[x].push_back(cnt);
            //    cout<<cnt<<endl;
            //    for(int j=0;j<b[cnt].size();++j) cout<<b[cnt][j].r<<" ";
            //    cout<<endl;
            }
        }
        else if(dfn[y]<dfn[fa]){
            low[x]=min(low[x],dfn[y]);
            cf[x]++;
            cf[y]--;
        }
        else{
            low[x]=min(low[x],dfn[y]);
        }
    }
    if(cf[x]>1) Flag=1;
    return;
}

LL F[N+N];
LL ans[N];

void DP(int x,int fa,int op){
    int y,z,l=b[x].size();
    for(int i=0;i<l;++i){
        y=b[x][i];
        if(y==fa) continue;
        DP(y,x,op);
    }
    
    if(x<=n){
        F[x]=1;
        for(int i=0;i<l;++i){
            y=b[x][i];
            if(y==fa) continue;
            add(ans[op],F[y]*F[x]%M);
            add(F[x],F[y]);
        }
    }
    else if(l==2){
        F[x]=0;
        for(int i=0;i<l;++i){
            y=b[x][i];
            if(y==fa) continue;
            add(F[x],F[y]);
        }
    }
    else{
        F[x]=0;
        for(int i=0;i<l;++i){
            y=b[x][i];
            if(y==fa) continue;
            add(ans[op],F[y]*F[x]%M);
            add(F[x],(F[y]+F[y])%M);
        }
    }
    return;
}
void solve(){
    int u,v,w;
    n=read();m=read();K=read();
    for(int i=1;i<=K;++i){
        U[i].clear();
        ans[i]=0;
    }
    
    for(int i=1;i<=m;++i){
        u=read();v=read();w=read();
        for(auto j:factor[w]){
            U[j].pb((edge){u,v});
        }
    }
    vector<int> que;
    for(int i=1;i<=K;++i){
        que.clear();
        for(auto ed:U[i]){
            a[ed.u].clear();
            a[ed.v].clear();
            b[ed.u].clear();
            b[ed.v].clear();
            dfn[ed.u]=dfn[ed.v]=0; 
            que.pb(ed.u);
            que.pb(ed.v);
        }
        for(auto ed:U[i]){
            a[ed.u].pb(ed.v);
            a[ed.v].pb(ed.u);
        }
        num=tp=0;cnt=n;
        for(auto x:que){
            if(!dfn[x]){
                Tarjan(x,0);
                if(Flag){
                    cout<<"wrong data"<<endl;
                    exit(0);
                    return;
                }
                DP(x,0,i);
            } 
        }
    }
    for(int i=1;i<=K;++i){
        for(int j=2;j*i<=K;++j){
            ans[i]+=mu[j]*ans[i*j];
        }
        ans[i]=(ans[i]%M+M)%M;
    }
//    for(int i=1;i<=K;++i){
//        cout<<ans[i]<<" ";
//    }
//    cout<<endl;

    LL Ans=0;
    for(int i=1;i<=K;++i){
        Ans^=ans[i];
    }
    cout<<Ans<<endl;
    return;
}

int main(){
    
    std::ios::sync_with_stdio(false);
    cin.tie(0);
    
    init();
    
    
    int t=1;
//	cin>>t;
	t=read();
    for(int i=1;i<=t;++i){
        solve();
    }
    return 0;
} 
