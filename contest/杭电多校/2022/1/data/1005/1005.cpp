#include<bits/stdc++.h>
#define N 100009
using namespace std;
typedef long long ll;
int head[N],tot;
int n,Q,len[N],du[N],link[N];
ll dp[N],hsum[N];
bool vis[N],vis2[N];
char s[N];
vector<int>vec[N];
vector<ll>sum[N];
queue<int>q;
inline ll rd(){
	ll x;
	scanf("%lld",&x);
	return x;
}
struct edge{
	int n,to;
}e[N];
inline void add(int u,int v){
	e[++tot].n=head[u];
	e[tot].to=v;
	head[u]=tot;
}
void solve(){
	n=rd();Q=rd();
	tot=0;
	int xxx=0;
	for(int i=1;i<=n;++i){
		scanf("%s",s+1);
		len[i]=strlen(s+1);
		xxx+=len[i];
		int st=0;
		for(int j=1;j<=len[i];++j){
			if(s[j]=='>')st=j+1;
		}
		int x=0;
		for(int j=st;j<=len[i];++j){	
			if(isalpha(s[j])){
				vec[i].push_back(s[j]);
			}
			else if(isdigit(s[j]))x=x*10+s[j]-'0';
			else if(s[j]==']'){
				vec[i].push_back(-x);
				add(x,i);
				if(x==i)dp[i]=2e18;
				du[i]++;
				x=0;
			}
		}
		dp[i]=vec[i].size();
	}
	for(int i=1;i<=n;++i)if(!du[i]){
		q.push(i);
	}
	while(!q.empty()){
		int u=q.front();q.pop();
		for(int i=head[u];i;i=e[i].n){
			int v=e[i].to;
			dp[v]+=dp[u]-1;
			dp[v]=min(dp[v],(ll)2e18);
			if(!--du[v])q.push(v);
		}
	}
	for(int i=1;i<=n;++i){
	    if(du[i])dp[i]=2e18;
	}
	for(int i=1;i<=n;++i){
		ll sm=0;
		for(int j=0;j<vec[i].size();++j){
			if(vec[i][j]<0){
				sm=min((ll)2e18,sm+dp[-vec[i][j]]);
				sum[i].push_back(sm);
				if(sm==2e18){
					link[i]=-vec[i][j];
					vec[i].resize(j+1);
					break;
				}
			}
			else{
				sm++;
				sum[i].push_back(sm);
			}
		}
    }
    for(int i=1;i<=n;++i){
    	if(link[i]&&!vis[i]){
    		int x=i;
    		ll sm=0;
    		while(!vis[x]){
    			vis[x]=1;
    			x=link[x];
			}
			bool tag=0;
			if(!vis2[x])tag=1;
			x=i;
			while(!vis2[x])vis2[x]=1,x=link[x];
			if(!tag)continue;
			int now=x;
			while(1){
				sm=min((ll)2e18,sm+sum[x][sum[x].size()-2]);
				x=link[x];
				if(x==now)break;
			}
	        x=now;
	        while(1){
	        	hsum[x]=sm;
	        	x=link[x];
	        	if(x==now)break;
			}
		}
	}
	int x;
	ll y;
	int pp=0;
	for(int i=1;i<=Q;++i){
		x=rd();y=rd();
		if(y>dp[x]){
			puts("-1");
			continue;
		}
		while(1){	
		    pp++;
			if(hsum[x]){
				y=(y-1)%hsum[x]+1; 
			}
			int l=0,r=vec[x].size()-1,ans=-1;
			while(l<=r){
				int mid=(l+r)>>1;
				if(sum[x][mid]>=y){
					ans=mid;
					r=mid-1;
				}
				else l=mid+1;
			}
			if(ans)y-=sum[x][ans-1];
			if(vec[x][ans]<0){
				x=-vec[x][ans];
			}
			else {
	        	printf("%c\n",vec[x][ans]);
				break;
			}
		}
	}
	for(int i=1;i<=n;++i){
		head[i]=link[i]=du[i]=len[i]=dp[i]=hsum[i]=vis[i]=vis2[i]=0;
		vec[i].clear();
		sum[i].clear();
	}
	tot=0;
}
int main(){
	int T=rd();
	while(T--)solve();
    return 0;
}

