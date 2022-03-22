#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+5,inf=0x3f3f3f3f,maxm=70;
int a[maxn],b[maxn],n,m;
int G[maxm][maxm];
int linker[maxm],lx[maxm],ly[maxm];
int slack[maxm];
bool visx[maxm],visy[maxm];
int mans[maxm];
bool DFS(int x) {
	visx[x]=1;
	for(int y=1;y<=m;y++) {
		if(visy[y]) continue;
		int tmp=lx[x]+ly[y]-G[x][y];
		if(tmp==0) {
			visy[y]=1;
			if(linker[y]==-1||DFS(linker[y])) {
				linker[y]=x;
				mans[x]=y;
				return 1;
			}
		} else if(slack[y]>tmp) slack[y]=tmp;
	}
	return false;
}
int KM() {
	memset(linker,-1,sizeof(linker));
	memset(ly,0,sizeof(ly));
	for(int i=1;i<=m;i++) {
		lx[i]=-inf;
		for(int j=1;j<=m;j++) {
			if(G[i][j]>lx[i]) lx[i]=G[i][j];
		}
	}
	for(int x=1;x<=m;x++) {
		for(int i=1;i<=m;i++) slack[i]=inf;
		while(1) {
			memset(visx,0,sizeof(visx));
			memset(visy,0,sizeof(visy));
			if(DFS(x)) break;
			int d=inf;
			for(int i=1;i<=m;i++) {
				if(!visy[i]&&d>slack[i]) d=slack[i];
			}
			for(int i=1;i<=m;i++) if(visx[i]) lx[i]-=d;
			for(int i=1;i<=m;i++) if(visy[i]) ly[i]+=d;else slack[i]-=d;
		}
	}
	int res=0;
	for(int i=1;i<=m;i++) if(linker[i]!=-1) res+=G[linker[i]][i];
	return res;
}
int ans[maxm];
bool vl[maxm],vr[maxm];
int g[maxm][maxm];
int main() {
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) scanf("%d",a+i);
	for(int i=1;i<=n;i++) scanf("%d",b+i);
	for(int i=1;i<=m;i++) {
		for(int j=1;j<=m;j++) {
			for(int k=1;k<=n;k++) {
				if(a[k]==i&&b[k]==j) g[i][j]++;
			}
		}
	}
	for(int i=1;i<=n;i++)  {
		if(ans[a[i]]) continue;
		int u=a[i];
		int mx=0,p=0;
		for(int v=1;v<=m;v++) {
			if(vr[v]) continue;
			memset(G,0,sizeof(G));
			for(int x=1;x<=m;x++) {
				for(int y=1;y<=m;y++) {
					if(ans[x]||vr[y]||x==u||v==y) continue;
					G[x][y]=g[x][y]; 
				}
			}
			int res=KM()+g[u][v];
			if(res>mx) {mx=res;p=v;}
		}
		if(p==0) for(int v=1;v<=m;v++) if(!vr[v]) {p=v;break;}
		ans[a[i]]=p;
		vr[p]=1;
	}
	for(int i=1;i<=n;i++) cout<<ans[a[i]]<<' ';
	return 0;
}