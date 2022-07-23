#include <cstdio>
#include <cstring>
#include <algorithm>
#define MN 10000

const int INF = 0x3f3f3f3f;

using std::min;

int n,m;
int _f[2][MN+5];

int main(){
	scanf("%d%d",&n,&m);
	int ans = INF;
	memset(_f,0x3f,sizeof(_f));
	for(int i=1;i<=n;i++){
		int* f = _f[i&1];
		int* g = _f[(i&1)^1];
		g[1] = 0;
		for(int j=2;j<=m;j++){
			f[j] = g[j]+1;
		}
		int l;
		scanf("%d",&l);
		for(int j=1;j<=l;j++){
			int u,v;
			scanf("%d%d",&u,&v);
			f[v] = min(f[v],g[u]+1);
		}
		ans = min(ans,f[m]);
	}
	if(ans!=INF){
		printf("%d\n",ans);
	}else{
		puts("-1");
	}
}
