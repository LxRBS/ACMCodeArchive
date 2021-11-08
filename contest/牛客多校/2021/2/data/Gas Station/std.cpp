#include<bits/stdc++.h>
using namespace std;
using ll=long long;
#define pb push_back
#define rep(i,a,b) for(int i=a,i##end=b;i<=i##end;++i)
#define drep(i,a,b) for(int i=a,i##end=b;i>=i##end;--i)
char IO;
template <class T=int> T rd(){
	T s=0; int f=0;
	while(!isdigit(IO=getchar())) f|=IO=='-';
	do s=(s<<1)+(s<<3)+(IO^'0');
	while(isdigit(IO=getchar()));
	return f?-s:s;
}

const int N=1e5+10;

int n,m;
struct Edge{
	int to,nxt,w;
} e[N<<1];
int head[N],ecnt;
void AddEdge(int u,int v,int w){
	e[++ecnt]=(Edge){v,head[u],w};
	head[u]=ecnt;
}

int Ans[N],W[N];
ll A[N],B[N],D[N],H[N],C;
int Min,Rt,S[N],vis[N];
void FindRt(int n,int u,int f) {
	int m=0; S[u]=1;
	for(int i=head[u],v;i;i=e[i].nxt) if(!vis[v=e[i].to] && v!=f) FindRt(n,v,u),S[u]+=S[v],m=max(m,S[v]);
	m=max(m,n-S[u]);
	if(Min>m) Min=m,Rt=u;
}
int L[N],R[N],I[N],dfn,J[N];
struct BIT{
	int s[N],n;
	void Init(int m){ memset(s,0,((n=m)+1)<<2); }
	void Add(int p){ while(p<=n) s[p]++,p+=p&-p; }
	int Que(int p){
		int res=0;
		while(p) res+=s[p],p-=p&-p;
		return res;
	}
} T;
vector <int> G[N];
struct Que{ ll d; int id,k; };
vector <Que> Q[N];
int U[N];ll E[N];

void Dfs(int u,int f,ll s){
	H[++C]=-A[u],I[L[u]=++dfn]=u;
	for(int i=head[u],v;i;i=e[i].nxt) if(!vis[v=e[i].to] && v!=f) {
		A[v]=min(A[u],s-e[i].w);
		B[v]=min(B[u]+W[v]-e[i].w,0ll);
		D[v]=D[u]-e[i].w+W[v];
		J[v]=f?J[u]:v;
		Dfs(v,u,s-e[i].w+W[v]);
	}
	R[u]=dfn;
}
void Dfs(int u,int f){
	for(Que &i:Q[u]) Ans[i.id]-=i.k*T.Que(i.d=upper_bound(H+1,H+C+1,i.d)-H-1);
	T.Add(lower_bound(H+1,H+C+1,-A[u])-H);
	for(int i=head[u],v;i;i=e[i].nxt) if(!vis[v=e[i].to] && v!=f) Dfs(v,u);
	for(Que &i:Q[u]) Ans[i.id]+=i.k*T.Que(i.d);
	R[u]=0,Q[u].clear();
}
void Div(int n,int u){
	Min=1e9,FindRt(n,u,0),vis[u=Rt]=1;
	dfn=A[u]=B[u]=D[u]=C=0,J[u]=0,Dfs(u,0,W[u]);
	sort(H+1,H+C+1),C=unique(H+1,H+C+1)-H-1;
	rep(j,1,dfn) {
		int u=I[j];
		for(int i:G[u]) {
			if(B[u]+E[i]<0) continue; // can not reach root
			if(L[U[i]]<=L[u] && L[u]<=R[U[i]]) continue; // way blocked
			ll d=D[u]+E[i];
			Q[Rt].pb((Que){d,i,1});
			if(J[u]) Q[J[u]].pb((Que){d,i,-1});
			if(R[U[i]] && (L[U[i]]<L[J[u]] || L[U[i]]>R[J[u]])) Q[U[i]].pb((Que){d,i,-1});
		}
	}
	T.Init(C),Dfs(u,0);
	for(int i=head[u],v;i;i=e[i].nxt) if(!vis[v=e[i].to]) {
		if(S[v]>S[u]) S[v]=n-S[u];
		Div(S[v],v);
	}
}

int main(){
	n=rd(),m=rd();
	rep(i,2,n) {
		int u=rd(),v=rd(),w=rd();
		AddEdge(u,v,w),AddEdge(v,u,w);
	}
	rep(i,1,n) W[i]=rd();
	rep(i,1,m) {
		int u=rd();
		E[i]=rd<ll>(),U[i]=rd();
		G[u].pb(i);
	}
	Div(n,1);
	rep(i,1,m) printf("%d\n",Ans[i]);
}



