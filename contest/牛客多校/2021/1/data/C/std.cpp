#include<bits/stdc++.h>
using namespace std;
#define N 100005
int totm,tot,last[N],to[2*N],Next[2*N],fa[N],q[N],n;
int a[N],l,r,dis[N],A[N],sumtime=0;
#define pb push_back
struct pa {
	int v,node;
};
struct val {
	pa v,g;
}f[N*50];
struct Ans {
	int v,s,t;
}ans;
int ls[N*50],rs[N*50];
int t[N];
inline void add(int x,int y) {
	Next[++totm]=last[x]; last[x]=totm; to[totm]=y;
}
inline void build(int x,int y) {
	l=0,r=1; q[1]=x;
	dis[x]=1;
	while (l<r) {
		int k=q[++l];
		for (int i=last[k];i;i=Next[i]) {
			if (fa[k]==to[i]) continue;
			if (to[i]==y) continue;
			fa[q[++r]=to[i]]=k;
			dis[to[i]]=dis[k]+1;
		}
	}
}
inline int build(int l,int r,int ll,int p) {
	int x=++tot;
	f[x]={{1,p},{1,p}};
	if (ans.v<1) {
		ans.v=1;
		ans.s=ans.t=p;
	}
	if (l==r) return x;
	int mid=(l+r)>>1;
	if (ll<=mid) {
		ls[x]=build(l,mid,ll,p);
	}
	else {
		rs[x]=build(mid+1,r,ll,p);
	}
	return x;
}
inline pa max(pa x,pa y) {
	if (x.v>y.v) return x;
	return y;
}

inline void up(int x) {
	f[x].v=max(f[ls[x]].v,f[rs[x]].v);
	f[x].g=max(f[ls[x]].g,f[rs[x]].g);
}

inline val MaxR(val x,val y) {
	return {x.v,max(x.g,y.g)};
}
inline val MaxL(val x,val y) {
	return {max(x.v,y.v),x.g};
}

inline void getans(val x,val y) {
	if (x.v.v+y.g.v>ans.v) {
		ans.v=x.v.v+y.g.v;
		ans.s=x.v.node;
		ans.t=y.g.node;
	}
	if (x.g.v+y.v.v>ans.v) {
		ans.v=x.g.v+y.v.v;
		ans.s=x.g.node;
		ans.t=y.v.node;
	}
}

inline int combine(int x,int y,val lans,val rans,int l,int r) {
	sumtime++;
	if (x) {
		getans(f[x], rans);
	}
	if (y) {
		getans(f[y],lans);
	}
	if (!x||!y) return x+y;
	if (l==r) {
		f[x].v=max(f[x].v,f[y].v);
		f[x].g=max(f[x].g,f[y].g);
		return x;
	}
	val lans1=MaxR(lans,f[rs[x]]);
	val rans1=MaxR(rans,f[rs[y]]);
	val lans2=MaxL(lans,f[ls[x]]);
	val rans2=MaxL(rans,f[ls[y]]);
	int mid=(l+r)>>1;
	if (ls[x]||ls[y]) {
		ls[x]=combine(ls[x],ls[y],lans1,rans1,l,mid);
	}
	if (rs[x]||rs[y]) {
		rs[x]=combine(rs[x],rs[y],lans2,rans2,mid+1,r);
	}
	up(x);
	return x;
}
inline void clear() {
	for (int i=1;i<=n;i++) fa[i]=0;
	for (int i=1;i<=tot;i++) ls[i]=rs[i]=0,f[i].v=f[i].g={0,0};
	tot=0;
	ans.v=ans.s=ans.t=0;
}
inline int change(int x,int l,int r,int ll,int p,val t) {
	if (!x) x=++tot;
	if (l==r) {
		if (!t.v.node) t.v.node=p;
		if (!t.g.node) t.g.node=p;
		//f[x]={{t.v.v+1,t.v.node},{t.g.v+1,t.g.node}};
		f[x].v=max(f[x].v,{t.v.v+1,t.v.node});
		f[x].g=max(f[x].g,{t.g.v+1,t.g.node});
		if (f[x].v.v>ans.v) {
			ans.v=f[x].v.v;
			ans.s=f[x].v.node;
			ans.t=p;
		}
		if (f[x].g.v>ans.v) {
			ans.v=f[x].g.v;
			ans.s=f[x].g.node;
			ans.t=p;
		}
		return x;
	}
	
	int mid=(l+r)>>1;
	if (ll<=mid) {
		t=MaxR(t,f[rs[x]]);
		ls[x]=change(ls[x],l,mid,ll,p,t);
	}
	else {
		t=MaxL(t,f[ls[x]]);
		rs[x]=change(rs[x],mid+1,r,ll,p,t);
	}
	up(x);
	return x;
}

inline void work(int p) {
	clear();
	for (int _i=1;_i<=n;_i++) {
		if (!fa[_i]&&_i!=p) {
			build(_i,p);
			for (int i=r;i;i--) {
				//fprintf(stderr,"%d %d %d\n",i,tot,sumtime);
				int x=q[i];
				t[x]=build(1,n,a[x],x);
				for (int j=last[x];j;j=Next[j]) {
					if (fa[to[j]]!=x) continue;
					t[to[j]]=change(t[to[j]],1,n,a[x],x,{{0,0},{0,0}});
					t[x]=combine(t[x],t[to[j]],{{0,0},{0,0}},{{0,0},{0,0}},1,n);
				}
			}
		}
	}
	//printf("%d %d %d\n", ans.v,ans.s,ans.t);
}

inline vector<int> getp(int s,int t,int times) {
	int x=s,y=t;
	while (x!=y) {
		if (dis[x]>dis[y]) x=fa[x];
		else y=fa[y];
	}
	int lca=x;
	int sum=0;
	vector<int>l1;
	vector<int>l2;
	for (int x=s;;x=fa[x]) {
		if (A[x]==times) {
			A[x]=times+1;
			l1.pb(x);
		}
		if (x==lca) break;
	}
	for (int x=t;x!=lca;x=fa[x]) {
		if (A[x]==times) {
			A[x]=times+1;
			l2.pb(x);
		}
	}
	while (l2.size()) {
		l1.pb(l2.back());
		l2.pop_back();
	}
	return l1;
}

int main() {
	//freopen("a.in","r",stdin);
	//freopen("std.out","w",stdout);
	scanf("%d",&n);
	if (n==1) {
		assert(0);
	}
	for (int i=1;i<n;i++) {
		int x,y;
		scanf("%d%d",&x,&y);
		add(x,y);
		add(y,x);
	}
	for (int i=1;i<=n;i++) scanf("%d",&a[i]);
	int times=0;
	work(0);
	int maxans=ans.v;
	int maxp=0;
	int maxs=ans.s;
	int maxt=ans.t;
	vector<int>now=getp(ans.s,ans.t,0);
	while (now.size()) {
		/*for (auto p:now) printf("%d ",p);
		puts("");*/
		int nextp=now[((now.size()-1)>>1)];
		work(nextp);
		if (ans.v<maxans) {
			maxans=ans.v;
			maxp=nextp;
			maxs=ans.s;
			maxt=ans.t;
		}
		//printf("maxans %d %d %d %d\n",nextp,ans.v,ans.s,ans.t);
		now=getp(ans.s,ans.t,++times);
		
	}
	//printf("%d %d %d %d\n",maxans,maxp,maxs,maxt);
	printf("%d\n",maxans);
	
}