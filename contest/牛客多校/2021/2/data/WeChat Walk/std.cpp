#include<bits/stdc++.h>
using namespace std;
#define M 200005
#define N 10000005
vector<int>d[M],g[M];
int hd[550][M/10];
int n,m,t,q,mk[M],a[M],ans[M],s,id[M],cnt,cs=0,mx[M],nx[N],to[N],tot;
void add(int x){
	for(int i=0;i<(int)g[x].size();++i){
		int s=id[g[x][i]];
		nx[++tot]=hd[s][a[x]];hd[s][a[x]]=tot;
		to[tot]=x;
	}
}
void Add(int x){
	for(int i=0;i<(int)g[x].size();++i)mx[g[x][i]]=max(mx[g[x][i]],a[x]);
}

int main(){
	scanf("%d%d%d",&n,&m,&q);s=2*sqrt(m)+1;
	for(int i=1,x,y;i<=m;++i){
		scanf("%d%d",&x,&y);
		d[x].push_back(y);
		d[y].push_back(x);
	}
	for(int i=1;i<=n;++i){
		for(int j=0;j<(int)d[i].size();++j){
			int v=d[i][j];
			if((int)d[v].size()>=s)g[i].push_back(v);
		}
	}
	for(int i=1;i<=n;++i)if((int)d[i].size()>=s)id[i]=++cnt;
	for(int i=1;i<=q;++i){
		int p1=i,p2,p3;
		scanf("%d%d",&p2,&p3);a[p2]+=p3;
		if(mk[p2])add(p2);
		else{
			cs+=d[p2].size();
			if(!id[p2]){
				while(1){
					int id=0,w=0;
					for(int j=0;j<(int)d[p2].size();++j){
						int v=d[p2][j];w=max(w,a[v]);
						if(mk[v]&&(id==0||a[v]<a[id]))id=v;
					}
					if(!id){
						if(w<a[p2])mk[p2]=p1,add(p2);
						break;
					}
					if(a[id]>a[p2])break;
					ans[id]+=p1-mk[id];mk[id]=0;
				}
			}else{
				int s=id[p2];
				for(int t=a[p2]-p3+1;t<=a[p2];++t){
					for(int i=hd[s][t];i;i=nx[i]){
						int v=to[i];
						if(a[v]==t&&mk[v]){
							ans[v]+=p1-mk[v];
							mk[v]=0;
						}
					}
				}
				if(mx[p2]<a[p2])mk[p2]=p1,add(p2);
			}
		}Add(p2);
	}
	for(int i=1;i<=n;++i)if(mk[i])ans[i]=ans[i]+q-mk[i];
	for(int i=1;i<=n;++i)printf("%d\n",ans[i]);
}
