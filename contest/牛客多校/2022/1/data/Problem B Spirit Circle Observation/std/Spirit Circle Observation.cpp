#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<queue>
#include<map>
#include<set>
#include<cmath>
#include<vector>
#include<cassert>
#include<ctime>
#include<bitset>
#include<functional>
typedef long long ll;
using namespace std;
#define pii pair<int,int>
#define pll pair<ll,ll>
#define pil pair<int,ll>
#define pli pair<ll,int>
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define N 800010
#define P 10
vector<int>G[N],rG[N];
struct SAM{
	int tr[N][P],fa[N],len[N],siz[N];
	int endpos[N];
	int cnt,last;
	void init(){//dont forget!!!
        cnt=last=1;
        memset(tr[1],0,sizeof(tr[1]));
		fa[1]=len[1]=0;
    }
	void add(int c,int pos){
		int p=last,np=++cnt;
        memset(tr[cnt],0,sizeof(tr[cnt]));
        endpos[cnt]=pos;
		siz[np]=1;
		last=np;
		len[np]=len[p]+1;
		while(p&&!tr[p][c])tr[p][c]=np,p=fa[p];
		if(!p)fa[np]=1;
		else{
			int q=tr[p][c];
			if(len[q]==len[p]+1)fa[np]=q;
			else{
				int nq=++cnt;len[nq]=len[p]+1;endpos[cnt]=0;
				memcpy(tr[nq],tr[q],sizeof(tr[q]));
				fa[nq]=fa[q];
				fa[q]=fa[np]=nq;
				while(tr[p][c]==q)tr[p][c]=nq,p=fa[p];
			}
		}
	}
	void insert(char a[]){
		int i;
		for(i=1;a[i];i++)add(a[i]-'0',i);//can be changed
	}
	void build(vector<int>G[],vector<int>rG[]){
		int i;
		for(i=1;i<=cnt;i++){
			G[fa[i]].pb(i);
			rG[i].pb(fa[i]);
		}
	}
}sam;
map<int,int>s0[N],s9[N];
char s[N];
int len0[N],len9[N];
queue<int>Q;
int indeg[N];
int main(){
	int i,j,n,cur=0;
	scanf("%d%s",&n,s+1);
	sam.init();
	sam.insert(s);
	sam.build(G,rG);
	len0[n+1]=len9[n+1]=1;
	for(i=n;i>=1;i--){
		len0[i]=s[i]=='0'?len0[i+1]+1:1;
		len9[i]=s[i]=='9'?len9[i+1]+1:1;
	}
	ll res=0;
	for(i=0;i<9;i++){
		for(j=1;j<=sam.cnt;j++){
			s0[j].clear();s9[j].clear();
			if(sam.endpos[j]){
				if(s[sam.endpos[j]+1]==i+'1')s0[j][len0[sam.endpos[j]+2]]++;
				if(s[sam.endpos[j]+1]==i+'0')s9[j][len9[sam.endpos[j]+2]]++;
			}
			indeg[j]=G[j].size();
			if(!indeg[j])Q.push(j);
		} 
		map<int,int>t0,t9;
		t0.clear();t9.clear();
		for(j=1;j<=n;j++)if(s[j]=='1'+i)t0[len0[j+1]]++;
		for(j=1;j<=n;j++)if(s[j]=='0'+i)
			for(auto x:t0){
				if(x.fi<=len9[j+1])res+=1LL*x.fi*x.se;
				else res+=len9[j+1]*x.se;
			}
		while(!Q.empty()){
			int p=Q.front();Q.pop();
			if(p==1)break;
			for(auto q:rG[p]){
				for(auto x:s0[p]){
					auto len=x.fi,cnt=x.se;
					for(auto y:s9[q]){
						if(y.fi<=len)res+=1LL*sam.len[q]*cnt*y.fi*y.se;
						else res+=1LL*sam.len[q]*cnt*len*y.se;
					}
				}
				for(auto x:s9[p]){
					auto len=x.fi,cnt=x.se;
					for(auto y:s0[q]){
						if(y.fi<=len)res+=1LL*sam.len[q]*cnt*y.fi*y.se;
						else res+=1LL*sam.len[q]*cnt*len*y.se;
					}
				}
				for(auto x:s0[p])s0[q][x.fi]+=x.se;
				for(auto x:s9[p])s9[q][x.fi]+=x.se;
				if(!--indeg[q])Q.push(q);
			}
		}
	}
	printf("%lld",res);
	return 0;
}