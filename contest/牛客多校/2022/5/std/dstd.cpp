#include<bits/stdc++.h>
#include<map>
#define INF 0x3f3f3f3f
#define int long long
const int Mod=1e9+7;
using namespace std;
inline int read(){
	int w=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-')f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		w=(w<<3)+(w<<1)+ch-48;
		ch=getchar();
	}
	return w*f;
}
int n,m,cnt,head[300010],dp[300010][3],a[300010],ans,num[300010][3],ret[300010][3];
struct Edge{
	int from,to,next;
}edge[600010];
inline void addedge(int u,int v){
	cnt++;
	edge[cnt].from=u;
	edge[cnt].to=v;
	edge[cnt].next=head[u];
	head[u]=cnt;
}
inline void ins(int u,int v){
	addedge(u,v);addedge(v,u);return;
}
inline void dfs(int u,int fa){
	for(int i=head[u];i;i=edge[i].next){
		int v=edge[i].to;if(v==fa)continue;dfs(v,u);
		ans+=dp[u][1]*dp[v][1];ans%=Mod;
		ans+=dp[u][2]*dp[v][2];ans%=Mod;
		dp[u][1]=dp[u][1]*dp[v][1]+dp[u][1]+dp[v][1];dp[u][1]%=Mod;
		dp[u][2]=dp[u][2]*dp[v][2]+dp[u][2]+dp[v][2];dp[u][2]%=Mod;
		ans+=dp[v][a[u]];
	}
	dp[u][a[u]]++;dp[u][a[u]]%=Mod;
	ans++;ans%=Mod;
	return;
}
signed main(){
	n=read();
	for(int i=1;i<=n;i++){
		char ch;cin>>ch;
		if(ch=='0')a[i]=1;
		else a[i]=2;
	}
	for(int i=1;i<n;i++){
		int x=read();int y=read();ins(x,y);
	}
	dfs(1,0);
	cout<<ans<<endl;
	return 0;
}