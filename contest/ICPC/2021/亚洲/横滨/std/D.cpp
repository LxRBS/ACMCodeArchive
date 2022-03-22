#include<bits/stdc++.h>
#define lson rt<<1
#define rson rt<<1|1
#define inf 0x3f3f3f3f
#define ll long long
#define P pair<ll,int>
using namespace std;
const int maxn=3e5+5;
struct nod{
	int u,p;
}a[maxn];
ll score[maxn],ans[maxn];
int sum[maxn<<2],tag[maxn<<2];
int add[maxn<<2];
vector<P>st;
int find(P x) {return lower_bound(st.begin(),st.end(),x)-st.begin()+1;}
void up(int rt) {sum[rt]=sum[lson]+sum[rson];}
void down(int rt) {
	tag[lson]+=tag[rt];add[lson]+=tag[rt];
	tag[rson]+=tag[rt];add[rson]+=tag[rt];
	tag[rt]=0;
}
void update(int l,int r,int rt,int x,int v) {
	if(l==r) {
		sum[rt]+=v;
		int id=st[l-1].second;
		if(v==-1) ans[id]+=add[rt];
		else if(v==1) add[rt]=0;
		else abort();
		return;
	}
	down(rt);
	int m=l+r>>1;
	if(x<=m) update(l,m,lson,x,v);
	else update(m+1,r,rson,x,v);
	up(rt);
}
void update_mv(int l,int r,int rt,int L,int R) {
	if(L>R) return;
	if(L<=l&&R>=r) {
		tag[rt]++;add[rt]++;
		return;
	}
	down(rt);
	int m=l+r>>1;
	if(L<=m) update_mv(l,m,lson,L,R);
	if(m<R) update_mv(m+1,r,rson,L,R);
	up(rt);
}
int qry(int l,int r,int rt,int L,int R) {
	if(L>R) return 0;
	if(L<=l&&R>=r) return sum[rt];
	down(rt);
	int m=l+r>>1,res=0;
	if(L<=m) res+=qry(l,m,lson,L,R);
	if(m<R) res+=qry(m+1,r,rson,L,R);
	up(rt);
	return res;
}
int pos[maxn];
int main() {
	int n,Q;
	scanf("%d%d",&n,&Q);
	for(int i=1;i<=n;i++) st.push_back(P(0,i));
	for(int i=0;i<Q;i++) {
		scanf("%d%d",&a[i].u,&a[i].p);
		score[a[i].u]+=a[i].p;
		st.push_back(P(score[a[i].u],a[i].u));
	}
	sort(st.begin(),st.end());
	st.erase(unique(st.begin(),st.end()),st.end());
	int N=st.size();
	for(int i=1;i<=n;i++) {
		int x=find(P(0,i));
		pos[i]=x;
		update(1,N,1,x,1);
	}
	memset(score,0,sizeof(score));
	for(int i=0;i<Q;i++) {
		if(a[i].p==0) continue;
		int u=a[i].u;
		int pre=pos[u],from=0,to=0;
		int l=find(P(score[u],inf));
		if(a[i].p<0) to=find(P(score[u],0))-1;
		else from=find(P(score[u],0));
		score[u]+=a[i].p;
		int nex=find(P(score[u],u));
		if(a[i].p<0) from=find(P(score[u],0));
		else to=find(P(score[u],0))-1;
		int r=find(P(score[u],inf));


		update(1,N,1,pre,-1);
		ans[u]+=abs(qry(1,N,1,l,N)-qry(1,N,1,r,N));
		update_mv(1,N,1,from,to);
		update(1,N,1,nex,1);
		pos[u]=nex;

	}
	for(int i=1;i<=n;i++) {
		update(1,N,1,pos[i],-1);
	}
	for(int i=1;i<=n;i++) printf("%lld\n",ans[i]);
	return 0;
}