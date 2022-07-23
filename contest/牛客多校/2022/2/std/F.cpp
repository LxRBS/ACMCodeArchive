#include<bits/stdc++.h>
#define fi first
#define se second
#define pb push_back
#define mkp make_pair
#define int long long
using namespace std;

typedef double db;
typedef pair<int,int> pii;
typedef pair<char,int> pci;
typedef long long ll;
const int N=5e5+100,mod=1000000007,inf=1e9+7;

int read(){
    int ret=0,f=0;char c=getchar();
    while(!isdigit(c)){if(c=='-')f=1;c=getchar();}
    while(isdigit(c)){ret=ret*10+(c^48);c=getchar();}
    return f?-ret:ret;
}

int n,Q;

struct Segment{
	#define ls (x<<1)
	#define rs (x<<1|1)
	int sum[N<<2],tag[N<<2];
	void pushup(int x){
		sum[x]=sum[ls]+sum[rs];
	}
	void pushdown(int x){
		if(!tag[x]) return;
		sum[ls]+=tag[x];sum[rs]+=tag[x];
		tag[ls]+=tag[x];tag[rs]+=tag[x];
		tag[x]=0;
	}
	void update(int x,int l,int r,int L,int R,int v){
		if(L>R) return;
		if(L<=l && r<=R){
			sum[x]+=v;tag[x]+=v;
			return;
		}
		pushdown(x);
		int mid=(l+r)>>1;
		if(L<=mid) update(ls,l,mid,L,R,v);
		if(R>mid) update(rs,mid+1,r,L,R,v);
		pushup(x);
	}
	int query(int x,int l,int r,int p){
		if(l>r) return 0;
		if(l==r) return sum[x];
		pushdown(x);
		int mid=(l+r)>>1;
		if(p<=mid) return query(ls,l,mid,p);
		else return query(rs,mid+1,r,p);
	}
	#undef ls 
	#undef rs
}T;

namespace Trie{
	int m=1;
	int c[N][26],nc[N][26],cnt[N],dep[N],fa[22][N],nextp[N][26];
	int tim,ind[N];
	void insert(const vector<char>&s,vector<int>&p,int id){
		int now=1,n=s.size();
		for(int i=0;i<n;++i){
			int t=s[i]-'a';
			if(!c[now][t]) c[now][t]=++m;
			now=c[now][t];p.pb(now);
		}
	}
	void dfs(int x,int dp){
		dep[x]=dp;ind[x]=++tim;
		for(int i=0;i<26;++i){
			if(c[x][i]){
				fa[0][c[x][i]]=x;
				//printf("now:%d next:%d edge:%d\n",x,c[x][i],i);
				dfs(c[x][i],dp+1);
				nc[x][i]=nc[c[x][i]][i];
				//printf("now:%d next:%d edge:%d nc:%d\n",x,c[x][i],i,nc[x][i]);
			}
			else{
				nc[x][i]=x;
				nextp[x][i]=tim+1;
			}
		}
	}
	void init(){
		dfs(1,0);
		for(int j=1;j<19;++j) for(int i=1;i<=m;++i){
			fa[j][i]=fa[j-1][fa[j-1][i]];
		}
		++m;//the last point should have one more
	}
	int jump(int now,int stp){
		for(int i=0;i<19;++i){
			if(stp&(1<<i)) now=fa[i][now];
		}
		return now;
	}
};
using namespace Trie;

struct Tquery{
	int op,x,y;
	Tquery(int _op=0,int _x=0,int _y=0):op(_op),x(_x),y(_y){}
};
vector<Tquery>qr;

vector<pair<int,int> >s;
vector<char>ts[N];
vector<int>pos[N];
int tlen[N];
char ss[N];

void buildtrie(){
	for(int i=1,len;i<=n;++i){
		scanf("%s",ss);len=strlen(ss);
		for(int j=0;j<len;++j) ts[i].pb(ss[j]);
		tlen[i]=ts[i].size();
	}

	for(int i=1;i<=Q;++i){
		int op=read(),x=0,y=0;
		//cout<<op<<"!!!!!!!!!!!!"<<endl;
		if(op&1){
			x=read();
			scanf("%s",ss);y=ss[0]-'a';
			if(op==1) ts[x].pb(ss[0]);
		}
		else if(op==2) x=read();
		qr.pb(Tquery(op,x,y));
	}
	for(int i=1;i<=n;++i){
		insert(ts[i],pos[i],i);
	}
	init();
	for(int i=1;i<=n;++i){
		int l=ind[pos[i][tlen[i]-1]];
		T.update(1,1,m,l+1,m,1);
	}
}

int totlen,nowlen,cur;
void solve(){
	n=read();Q=read();
	scanf("%s",ss);int len=strlen(ss);
	for(int i=0;i<len;++i) s.pb(mkp(i+1,ss[i]-'a')),++totlen;

	buildtrie();
	
	cur=1;nowlen=0;
	for(int i=0;i<totlen;++i){
		int t=s[i].se;
		if(!c[cur][t]) break;
		++nowlen;cur=c[cur][t];
	}
	//printf("cur:%d nowlen:%d\n",cur,nowlen);
	for(int i=0;i<Q;++i){
		int op=qr[i].op,x=qr[i].x,y=qr[i].y;
		//printf("!!%d %d %d\n",op,x,y);
		if(op==1){
			int l=ind[pos[x][tlen[x]-1]],r=ind[pos[x][tlen[x]]];
			++tlen[x];
			T.update(1,1,m,l+1,m,-1);T.update(1,1,m,r+1,m,1);
		}
		else if(op==2){
			totlen-=x;
			if(totlen<nowlen){
				cur=jump(cur,nowlen-totlen);
				nowlen=totlen;
			}
			while(totlen<s.back().fi){
				auto t=s.back();s.pop_back();
				if(!s.size() || s.back().fi<totlen){
					t.fi=totlen;
					s.pb(t);
				}
			}
		}
		else if(op==3){
			pii t=mkp(x+s.back().fi,y);
			if(nowlen==s.back().fi){
				cur=nc[cur][y];nowlen=dep[cur];
				//printf("!!!!!!down:%d %d %d %d\n",cur,y,nc[cur][y],nowlen);
			}
			s.pb(t);totlen+=x;
			if(nowlen>totlen)
				cur=jump(cur,nowlen-totlen),nowlen=dep[cur];
		}
		else{
			if(nowlen==s.back().fi){
				printf("%lld\n",T.query(1,1,m,ind[cur]));
			}
			else{
				int p=lower_bound(s.begin(),s.end(),mkp(nowlen,0ll))-s.begin(),t;
				if(s[p].fi>nowlen) t=s[p].se;
				else t=s[p+1].se;
				printf("%lld\n",T.query(1,1,m,nextp[cur][t])); 
			}
		}
		//printf("cur:%d nowlen:%d\n",cur,nowlen);
		//for(auto v:s) printf("%d %d\n",v.fi,v.se);
		//puts("====");
	}
}

signed main(){
	//freopen("1.in","r",stdin);
	//freopen("f.out","w",stdout);
    for(int cas=1;cas--;){
        solve();
    }
    return 0;
}

/*
6 11
abe
aaa
aa
aab
aac
abd
bc
4
2 1
4
3 1 d
4
3 2 a
4
2 4
4 
1 3 d
4

5
4
4
5
0
0
*/
