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
int cas,n,m,A[M];
struct node{
	int len;
	ll max1,max2,min1,min2,res1,res2,res1_max,res1_min;
	node(int len=0){
		this->len=len;
		max1=max2=-1e18;
		min1=min2=1e18;
		res1=res2=res1_max=res1_min=-1e18;
	}
	void update_max(ll v){
		if(v>max1)max2=max1,max1=v;
		else if(v>max2)max2=v;
	}
	void update_min(ll v){
		if(v<min1)min2=min1,min1=v;
		else if(v<min2)min2=v;
	}
	node operator +(const node &A)const{
		if(len==0)return A;
		if(A.len==0)return *this;
		
		node T(len+A.len);
		
		T.update_max(max1);
		T.update_max(max2);
		T.update_max(A.max1);
		T.update_max(A.max2);
		
		T.update_min(min1);
		T.update_min(min2);
		T.update_min(A.min1);
		T.update_min(A.min2);
		
		MAX(T.res2,res2);
		MAX(T.res2,A.res2);
		MAX(T.res2,res1+A.res1);
		MAX(T.res2,max1+max2-A.min1-A.min2);
		MAX(T.res2,res1_max-A.min1);
		MAX(T.res2,max1+A.res1_min);
		
		MAX(T.res1,res1);
		MAX(T.res1,A.res1);
		MAX(T.res1,max1-A.min1);
		
		MAX(T.res1_max,res1_max);
		MAX(T.res1_max,A.res1_max);
		MAX(T.res1_max,res1+A.max1);
		MAX(T.res1_max,A.res1+max1);
		if(A.len>=2)MAX(T.res1_max,max1-A.min1+A.max1);
		if(len>=2)MAX(T.res1_max,max1-A.min1+max2);
		
		MAX(T.res1_min,res1_min);
		MAX(T.res1_min,A.res1_min);
		MAX(T.res1_min,res1-A.min1);
		MAX(T.res1_min,A.res1-min1);
		if(A.len>=2)MAX(T.res1_min,max1-A.min1-A.min2);
		if(len>=2)MAX(T.res1_min,max1-A.min1-min1);
		
		return T;
	}
}tree[M<<2];
void build(int l=1,int r=n,int p=1){
	if(l==r){
		tree[p]=node(1);
		tree[p].max1=tree[p].min1=1ll*A[l]*A[l];
		return;
	}
	int mid=l+r>>1;
	build(l,mid,p<<1);
	build(mid+1,r,p<<1|1);
	tree[p]=tree[p<<1]+tree[p<<1|1];
}
node query(int a,int b,int l=1,int r=n,int p=1){
	if(l>b||r<a)return node(0);
	if(l>=a&&r<=b)return tree[p];
	int mid=l+r>>1;
	return query(a,b,l,mid,p<<1)+query(a,b,mid+1,r,p<<1|1);
}

signed main(){
#ifndef ONLINE_JUDGE
//	freopen("jiedai.in","r",stdin);
//	freopen("jiedai.out","w",stdout);
#endif
	rd(cas);
	while(cas--){
		rd(n),rd(m);
		for(int i=1;i<=n;i++)rd(A[i]);
		build();
		while(m--){
			int l,r;
			rd(l),rd(r);
			print(query(l,r).res2);
		}
	}
	return (0-0);
}
