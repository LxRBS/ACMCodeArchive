#include<bits/stdc++.h>
#include<queue>
#define INF 0x3f3f3f3f
#define int long long

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
int n,dp[3010][3010],ans,cnt,tong[3010];
struct Point{
	int x,y;
}p[3010];
struct Edge{
	int u,v;int w;
}edge[6000010];
inline int cmp(Edge u,Edge v){
	return u.w<v.w;
}
inline int dist(int u,int v){
	return (p[u].x-p[v].x)*(p[u].x-p[v].x)+(p[u].y-p[v].y)*(p[u].y-p[v].y);
}
signed main(){
	n=read();
	for(int i=1;i<=n;i++){
		p[i].x=read();p[i].y=read();
	}
	for(int i=0;i<=n;i++){
		for(int j=1;j<=n;j++){
			if(i==j)continue;
			cnt++;edge[cnt].u=i;edge[cnt].v=j;edge[cnt].w=dist(i,j);
		}
	}
	sort(edge+1,edge+cnt+1,cmp);
	for(int i=1;i<=cnt;){
		int b=i;int e=i;
		while(edge[b].w==edge[e].w){
			int lst=edge[e].u;int cur=edge[e].v;
			dp[lst][cur]=max(dp[lst][cur],tong[cur]+1);
			e++;
		}
		for(int j=b;j<e;j++){
			int lst=edge[j].u;int cur=edge[j].v;
			tong[lst]=max(tong[lst],dp[lst][cur]);
			//cout<<lst<<" "<<cur<<" "<<dp[lst][cur]<<endl;
		}
		i=e;
	}
	for(int i=1;i<=n;i++){
		ans=max(ans,dp[0][i]);
	}
	cout<<ans<<endl;
	return 0;
}