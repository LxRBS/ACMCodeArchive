#include<bits/stdc++.h>
using namespace std;
#define cs const
#define pb push_back
#define ll long long
#define gc getchar
inline int read(){
	char ch=gc();
	int res=0;bool f=1;
	while(!isdigit(ch))f^=ch=='-',ch=gc();
	while(isdigit(ch))res=(res*10)+(ch^48),ch=gc();
	return f?res:-res;
}
template<typename tp>inline bool chemx(tp &a,tp b){return (a<b)?(a=b,1):0;}
cs int N=100005;
int len,a[N];
vector<int> e[N];
struct seg{
	#define lc (u<<1)
	#define rc ((u<<1)|1)
	#define mid ((l+r)>>1)
	int *vl,*tg,*cov,n;
	void init(int _n){
		n=_n;
		vl=new int[(n+1)*4+1];
		tg=new int[(n+1)*4+1];
		cov=new int[(n+1)*4+1];
		for(int i=0;i<=n*4;i++)vl[i]=tg[i]=cov[i]=0;
	}
	void covernow(int u){
		cov[u]=1,vl[u]=0,tg[u]=0;
	}
	void pushnow(int u,int k){
		tg[u]+=k,vl[u]+=k;
	}
	void pushdown(int u){
		if(cov[u]){
			covernow(lc);
			covernow(rc);
			cov[u]=0;
		}
		if(tg[u]){
			pushnow(lc,tg[u]);
			pushnow(rc,tg[u]);
			tg[u]=0;
		}
	}
	void update(int u,int l,int r,int st,int des,int k){
		if(st<=l&&r<=des)return pushnow(u,k);
		pushdown(u);
		if(st<=mid)update(lc,l,mid,st,des,k);
		if(mid<des)update(rc,mid+1,r,st,des,k);
		vl[u]=vl[rc];
	}
	void update(int l,int r,int k){
		assert(l>=0);
		assert(l<=r);
		if(l>n)return;
		update(1,0,n,l,min(r,n),k);
	}
	void cover(int u,int l,int r,int st,int des){
		if(st<=l&&r<=des)return covernow(u);
		pushdown(u);
		if(st<=mid)cover(lc,l,mid,st,des);
		if(mid<des)cover(rc,mid+1,r,st,des);
		vl[u]=vl[rc];
	}
	int query(int u,int l,int r,int p){
		if(l==r)return vl[u];
		pushdown(u);
		if(p<=mid)return query(lc,l,mid,p);
		else return query(rc,mid+1,r,p);
	}
	int query(int p){
		assert(p>=0);
		return query(1,0,n,min(p,n));		
	}
	int find(int u,int l,int r,int st,int k){
		if(l==r){
			if(vl[u]<k)return l+1;
			return l;
		}
		pushdown(u);
		if(mid<st)return find(rc,mid+1,r,st,k);
		
		if(vl[lc]>=k)return find(lc,l,mid,st,k);
		return find(rc,mid+1,r,st,k);
	}
	void Chemx(int u,int l,int r,int p,int &k){
		if(l==r){
			if(vl[u]>k)k=vl[u];
			else vl[u]=k;
			return;
		}
		pushdown(u);
		if(p<=mid)Chemx(lc,l,mid,p,k);
		else Chemx(rc,mid+1,r,p,k);
		vl[u]=vl[rc];
	}
	void Chemx(int p,int &k){
		assert(p>=0);
		if(p>n)return;
		Chemx(1,0,n,p,k);
	}
	void Setmx(int l,int k){
		if(l>n)return;
		assert(l<=n);
		int ps=find(1,0,n,l,k);
		assert(ps<=n+1);
		if(ps>l)cover(1,0,n,l,ps-1),update(1,0,n,l,ps-1,k);
	}
    int find2(int u,int l,int r,int st,int des,int k){
		if(l==r){
			if(vl[u]<k)return l+1;
			return l;
		}
		pushdown(u);
		if(mid<st)return find2(rc,mid+1,r,st,des,k);
		if(des<=mid)return find2(lc,l,mid,st,des,k);
		if(vl[lc]>=k)return find2(lc,l,mid,st,des,k);
		return find2(rc,mid+1,r,st,des,k);
	}
	void Setmx2(int l,int r,int k){
		if(l>n)return;
        if(r>n)r=n;
        if(l>r)return;
		int ps=find2(1,0,n,l,r,k);
		assert(ps<=n+1);
		if(ps>l)cover(1,0,n,l,ps-1),update(1,0,n,l,ps-1,k);
	}
	void Set(int p,int k){
		assert(p<=n);
	//	cout<<p<<'\n';
		if(k<0){
			update(1,0,n,0,n,k);
			Setmx(0,0);
		}
		else{
			update(1,0,n,p,n,k);
		}
	}
	void clear(){
		delete[] vl;
		vl=NULL;
		delete[] tg;
		tg=NULL;
		delete[] cov;
		cov=NULL;
	}
	#undef lc
	#undef rc
	#undef mid
}tr[N];
 
 
vector<int> f[N];
int maxdep;
int ans;
int siz[N],dep[N],mxdep[N];
int son[N],top[N];
 
int F(int u,int i){
	if(i<0)return 0;
	return tr[top[u]].query(dep[u]-dep[top[u]]+i);
}
 
void dfs1(int u,int fa){
	for(int v:e[u])if(v!=fa){
		dep[v]=dep[u]+1,dfs1(v,u);
		if(mxdep[v]>mxdep[son[u]])son[u]=v;
	}
	mxdep[u]=mxdep[son[u]]+1;
}
void dfs2(int u,int fa,int tp){
	top[u]=tp;if(u==tp)tr[u].init(mxdep[u]);
	if(son[u])dfs2(son[u],u,tp);
	for(int v:e[u])if(v!=son[u]&&v!=fa)dfs2(v,u,v);
}
void merge(int u,int v){
	int ps2=max(len-mxdep[v],mxdep[v]+2);
	vector<int> now(mxdep[v]+2);
	for(int i=2;i<=mxdep[v]+1;i++){
		chemx(now[i],F(u,i)+F(v,min(i-1,len-i)));
		chemx(now[i],F(v,i-1)+F(u,min(i,len-i+1)));
	}
	for(int i=2;i<=mxdep[v]+1;i++){
		tr[top[u]].Chemx(dep[u]-dep[top[u]]+i,now[i]);
	}

	if(mxdep[v]+1+1<ps2){
		tr[top[u]].update(dep[u]-dep[top[u]]+(mxdep[v]+2),dep[u]-dep[top[u]]+(ps2-1),F(v,mxdep[v]));
	}
	
	for(int i=ps2;i<=len&&i<=mxdep[u];i++){
		tr[top[u]].update(dep[u]-dep[top[u]]+i,dep[u]-dep[top[u]]+i,F(v,len-i));
	}
	
	int res=0;
	for(int i=2;i<=mxdep[v]+1;i++)
	if(min(i-1,len-i)>=0){
		tr[top[u]].Chemx(dep[u]-dep[top[u]]+i,res);
	}
	if(mxdep[v]+1+1<ps2){
		tr[top[u]].Setmx2(dep[u]-dep[top[u]]+(mxdep[v]+2),ps2-1,res);
	}
	if(ps2<=mxdep[u]&&ps2<=len){
		if(ps2)res=max(res,F(u,ps2-1));
		for(int i=ps2;i<=len&&i<=mxdep[u];i++)tr[top[u]].Chemx(dep[u]-dep[top[u]]+i,res);
	}
	tr[top[u]].Setmx(dep[u]-dep[top[u]]+min(len,mxdep[u])+1,res);
	tr[v].clear();
 
}
void dfs3(int u,int fa){
	if(son[u])dfs3(son[u],u);
	for(int v:e[u])if(v!=fa){
		if(v==son[u])continue;
		dfs3(v,u),merge(u,v);
	}
	tr[top[u]].Set(dep[u]-dep[top[u]]+1,a[u]);
    chemx(ans,F(u,min(len,mxdep[u])));
    chemx(ans,a[u]);
}
void dfs4(int u,int fa){
	siz[u]=dep[u]=mxdep[u]=son[u]=top[u]=0;
	for(int v:e[u])if(v!=fa){
		dfs4(v,u);
	}
}
void dp(int u,int fa){
	dep[u]=1;
	dfs1(u,fa);
	chemx(maxdep,mxdep[u]);
	dfs2(u,fa,u);	
	dfs3(u,fa);
    f[u].resize(mxdep[u]+1);
	tr[u].clear();
	dfs4(u,fa);
}

 
int n;
int main(){
//     #ifdef Stargazer
// //    freopen("1.in","r",stdin);
//     #endif
	int T=read();int tt=clock(),sn=0;;
	while(T--){
		ans=-1e9;
		n=read(),len=read();
		sn+=n;int ok=1;
		for(int i=1;i<=n;i++)a[i]=read(),ok&=(a[i]<0);
		for(int i=1;i<n;i++){
			int u=read(),v=read();
			e[u].pb(v),e[v].pb(u);
		}
        if(ok==1){
            for(int i=1;i<=n;i++)chemx(ans,a[i]);
            cout<<ans<<'\n';
        }
	//	solve(rt);
        else{
            dp(1,0);
		    cout<<ans<<'\n';
        }
        for(int i=1;i<=n;i++)e[i].clear();
	}
}