#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
template<class T>inline void MAX(T &x,T y){if(y>x)x=y;}
template<class T>inline void MIN(T &x,T y){if(y<x)x=y;}
template<class T>inline void rd(T &x){
	x=0;char o,f=1;
	while(o=getchar(),o<48)if(o==45)f=-f;
	do x=(x<<3)+(x<<1)+(o^48);
	while(o=getchar(),o>47);
	x*=f;
}
template<class T>inline void print(T x,bool op=1){
	static int top,stk[105];
	if(x<0)x=-x,putchar('-');
	if(x==0)putchar('0');
	while(x)stk[++top]=x%10,x/=10;
	while(top)putchar(stk[top--]+'0');
	putchar(op?'\n':' ');
}
const int M=1e5+5;
const int mod=998244353;
int cas,n,m,A[M],B[M];
struct node{
	int x,vl,vr;
	int l,r;
}Q[M];
pair<int,int>diff[M];
int fa[M];
int getfa(int x){
	return x==fa[x]?x:fa[x]=getfa(fa[x]);
}

int tree[M<<2],lazy_mul[M<<2],lazy_add[M<<2];
void build(int l=0,int r=n,int p=1){
	lazy_mul[p]=1;
	lazy_add[p]=0;
	tree[p]=0;
	if(l==r)return;
	int mid=l+r>>1;
	build(l,mid,p<<1);
	build(mid+1,r,p<<1|1);
}
void down(int p,int l,int r){
	if(lazy_mul[p]!=1){
		tree[p<<1]=1ll*tree[p<<1]*lazy_mul[p]%mod;
		lazy_mul[p<<1]=1ll*lazy_mul[p<<1]*lazy_mul[p]%mod;
		lazy_add[p<<1]=1ll*lazy_add[p<<1]*lazy_mul[p]%mod;
		tree[p<<1|1]=1ll*tree[p<<1|1]*lazy_mul[p]%mod;
		lazy_mul[p<<1|1]=1ll*lazy_mul[p<<1|1]*lazy_mul[p]%mod;
		lazy_add[p<<1|1]=1ll*lazy_add[p<<1|1]*lazy_mul[p]%mod;
		lazy_mul[p]=1;
	}
	if(lazy_add[p]){
		int mid=l+r>>1;
		tree[p<<1]=(tree[p<<1]+1ll*(mid-l+1)*lazy_add[p])%mod;
		lazy_add[p<<1]=(lazy_add[p<<1]+lazy_add[p])%mod;
		tree[p<<1|1]=(tree[p<<1|1]+1ll*(r-mid)*lazy_add[p])%mod;
		lazy_add[p<<1|1]=(lazy_add[p<<1|1]+lazy_add[p])%mod;
		lazy_add[p]=0;
	}
}
void update(int a,int b,int mul,int add,int l=0,int r=n,int p=1){
	if(l>b||r<a)return;
	if(l>=a&&r<=b){
		if(mul!=1){
			tree[p]=1ll*tree[p]*mul%mod;
			lazy_mul[p]=1ll*lazy_mul[p]*mul%mod;
			lazy_add[p]=1ll*lazy_add[p]*mul%mod;
		}
		if(add){
			tree[p]=(tree[p]+1ll*(r-l+1)*add)%mod;
			lazy_add[p]=(lazy_add[p]+add)%mod;
		}
		return;
	}
	down(p,l,r);
	int mid=l+r>>1;
	update(a,b,mul,add,l,mid,p<<1);
	update(a,b,mul,add,mid+1,r,p<<1|1);
	tree[p]=(tree[p<<1]+tree[p<<1|1])%mod;
}
int query(int a,int b,int l=0,int r=n,int p=1){
	if(l>b||r<a)return 0;
	if(l>=a&&r<=b)return tree[p];
	down(p,l,r);
	int mid=l+r>>1;
	return (query(a,b,l,mid,p<<1)+query(a,b,mid+1,r,p<<1|1))%mod;
}

signed main(){
#ifndef ONLINE_JUDGE
//	freopen("jiedai.in","r",stdin);
//	freopen("jiedai.out","w",stdout);
#endif
	rd(cas);
	while(cas--){
		rd(n),rd(m);
		for(int i=1;i<=n;i++)rd(A[i]),rd(B[i]);
		for(int i=1;i<=m;i++)rd(Q[i].x),rd(Q[i].vl),rd(Q[i].vr);
		
		for(int i=1;i<=n;i++)fa[i]=i;
		for(int i=1;i<n;i++)diff[i]=make_pair(A[i]-B[i+1],i);
		sort(diff+1,diff+n);
		sort(Q+1,Q+1+m,[](node &a,node &b){
			return a.vr>b.vr;
		});
		int now=n-1;
		for(int i=1;i<=m;i++){
			while(now>=1&&diff[now].first>=Q[i].vr){
				int pos=diff[now].second;
				fa[pos]=pos+1;
				now--;
			}
			Q[i].r=getfa(Q[i].x);
		}
		
		for(int i=1;i<=n;i++)fa[i]=i;
		for(int i=1;i<n;i++)diff[i]=make_pair(A[i+1]-B[i],i);
		sort(diff+1,diff+n);
		sort(Q+1,Q+1+m,[](node &a,node &b){
			return a.vl>b.vl;
		});
		now=n-1;
		for(int i=1;i<=m;i++){
			while(now>=1&&diff[now].first>=Q[i].vl){
				int pos=diff[now].second;
				fa[pos+1]=pos;
				now--;
			}
			Q[i].l=getfa(Q[i].x);
		}
		
		sort(Q+1,Q+1+m,[](node &a,node &b){
			return a.r<b.r;
		});
		build();
		update(0,0,1,1);
		for(int i=1;i<=m;i++){
			int l=Q[i].l,r=Q[i].r;
			update(r,r,1,query(l-1,r));
			update(0,l-2,2,0);
		}
		print(query(n,n));
	}
	return (0-0);
}
