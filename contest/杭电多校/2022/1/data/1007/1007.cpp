#include<bits/stdc++.h>
#define N 200009
using namespace std;
typedef long long ll;
int head[N],tot,f[N],dfn[N],c[N];
int n,m,q,deep[N],g[N][20],p[N];
int val[N],mx[N],siz[N];
int st[N],top,rbs[N],a[N],tp[N],fa[N],cost[N];
ll tr[N];
vector<int>op[N],vec[N];
inline ll rd(){
	ll x;
	scanf("%lld",&x);
	return x;
}
void upd(int x,int y){
	while(x<=n*2)tr[x]+=y,x+=x&-x;
}
ll query(int x){
	ll ans=0;
	while(x)ans+=tr[x],x-=x&-x;
	return ans;
}
int find(int x){
	return f[x]=f[x]==x?x:find(f[x]);
}
struct ed{
	int n,to;
}e[N];
struct Qnode{
	int opt,x,y;
}now[N];
struct Mem{
	int x,y,z;
};
vector<Mem>mem[N];
inline void add(int u,int v){
	e[++tot].n=head[u];
	e[tot].to=v;
	head[u]=tot;
}
struct edge{
	int u,v,w;
	inline bool operator <(const edge &b)const{
		return w<b.w;
	}
}b[N];
inline int jmp(int x,int y){
	for(int i=19;i>=0;--i)if(y&(1<<i))x=g[x][i];
	return x;
}
inline void updedge(int x,int y,int z){
	upd(dfn[y],z);
	if(g[x][0])upd(dfn[g[x][0]],-z);
}
inline ll Query(int l,int r){
	return query(r)-query(l-1);
}
inline int getlca(int u,int v){
	if(deep[u]<deep[v])swap(u,v);
	for(int i=19;i>=0;--i)if(deep[u]-(1<<i)>=deep[v])
	    u=g[u][i];
	if(u==v)return u;
	for(int i=19;i>=0;--i)if(g[u][i]!=g[v][i])
	    u=g[u][i],v=g[v][i];
	return g[u][0];
}
void dfs(int u){
	dfn[u]=++dfn[0];
	p[dfn[0]]=u;
	siz[u]=1;
	for(int i=1;(1<<i)<=deep[u];++i)
	    g[u][i]=g[g[u][i-1]][i-1];
	for(int i=head[u];i;i=e[i].n){
		int v=e[i].to;
		g[v][0]=u;
		deep[v]=deep[u]+1;
		dfs(v);
		siz[u]+=siz[v];
	}
}
void dfs1(int u){
	if(u<=n)mx[u]=val[u];
	else mx[u]=0;
	for(int i=head[u];i;i=e[i].n){
		int x=e[i].to;
		tp[x]=jmp(x,deep[x]-deep[u]-1);
		fa[x]=u;
		dfs1(x);
		mx[u]=max(mx[u],mx[x]);
	}
	if(u==2*n-1)tp[u]=u;
	updedge(tp[u],u,mx[u]);
}
inline void sol(int x,int y,int id){
	while(x){
		if(y>mx[x]){
			mem[id].push_back(Mem{tp[x],x,y-mx[x]});
			mx[x]=y;
		}
		else break;
		x=fa[x];
	}
}
void solve(){
	n=rd();m=rd();q=rd();
	for(int i=1;i<=n;++i){
	  c[i]=rd(),vec[c[i]].push_back(i);
	  if(c[i]==0)while(1);
    }
	for(int i=1;i<=n;++i)val[i]=rd();
	int opt,u,v,w;
	for(int i=1;i<=m;++i){
		u=rd();v=rd();w=rd();
		b[i]=edge{u,v,w};
	}
	for(int i=1;i<=n*2;++i)f[i]=i; 
	sort(b+1,b+m+1);
	int cnt=n;
	for(int i=1;i<=m;++i){
		int xx=find(b[i].u),yy=find(b[i].v);
		if(xx!=yy){
			++cnt;
			f[xx]=cnt;
			f[yy]=cnt;
			add(cnt,xx);add(cnt,yy);
			cost[cnt]=b[i].w;
		}
    }
    dfs(2*n-1);
    for(int i=1;i<=q;++i){
    	now[i].opt=rd();
		now[i].x=rd();
		now[i].y=rd();
    	if(now[i].opt==0){
    		op[c[now[i].x]].push_back(i);
		}
	}
    for(int i=0;i<=n*2;++i)head[i]=0;
    tot=0;
	for(int i=1;i<=n;++i)if(vec[i].size()){
		a[0]=0;
		for(int j=0;j<vec[i].size();++j){
			a[++a[0]]=dfn[vec[i][j]];
		}
		sort(a+1,a+a[0]+1);
		st[top=1]=2*n-1;rbs[rbs[0]=1]=2*n-1;
		for(int j=1;j<=a[0];++j){
			a[j]=p[a[j]];
			if(st[top]==a[j])continue;
			int lca=getlca(st[top],a[j]);
			if(lca==st[top]){
				st[++top]=a[j];
				rbs[++rbs[0]]=a[j];
				continue;
			}
			while(1){
				int fi=st[top],se=st[top-1];
				if(dfn[lca]>=dfn[se]){
					add(lca,fi);
					top--;break;
				}
				else add(se,fi),top--;
			}
			if(lca!=st[top]){
				st[++top]=lca;rbs[++rbs[0]]=lca;
			}
			st[++top]=a[j];rbs[++rbs[0]]=a[j];
			
		}
		while(top>1)add(st[top-1],st[top]),top--;
		dfs1(2*n-1);
		for(int j=0;j<op[i].size();++j){
			int x=op[i][j];
		    val[now[x].x]+=now[x].y;
			sol(now[x].x,val[now[x].x],x);
		}
		while(rbs[0]){
			int x=rbs[rbs[0]];
			head[x]=0;fa[x]=tp[x]=mx[x]=0;
			rbs[0]--;
		}
		tot=0;
	}
	for(int i=1;i<=q;++i){
		if(now[i].opt==0){
			for(int j=0;j<mem[i].size();++j){
				updedge(mem[i][j].x,mem[i][j].y,mem[i][j].z);
			}
		}
		else{
			int x=now[i].x,y=now[i].y;
			for(int i=19;i>=0;--i)if(g[x][i]&&cost[g[x][i]]<=y)x=g[x][i];
			printf("%lld\n",Query(dfn[x],dfn[x]+siz[x]-1));
		}
	}
    for(int i=0;i<=n*2;++i){
    	head[i]=dfn[i]=deep[i]=p[i]=siz[i]=val[i]=tr[i]=0;
    	vec[i].clear();
    	op[i].clear();
    	mem[i].clear();
    	for(int j=0;j<=19;++j)g[i][j]=0;
    	
	}
	tot=0;
}
int main(){ 
	int T;
	T=rd();
	while(T--){
		solve();
	}
}
