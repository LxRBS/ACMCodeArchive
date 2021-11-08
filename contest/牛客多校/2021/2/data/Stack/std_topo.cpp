#include<bits/stdc++.h>
using namespace std;
#define M 1000005
int a[M],val[M],dep[M];
vector<int>d[M];
void js(){
	puts("-1");
	exit(0);
}
int sk[M],r,ans[M];
int main(){
	int n,k;
	scanf("%d%d",&n,&k);
	for(int i=1,x,w;i<=k;++i){
		scanf("%d%d",&x,&w);
		if(val[x]&&w!=val[x])js();
		val[x]=w;
	}
	for(int i=1;i<=n;++i){
		if(val[i]){
			if(r+1<val[i])js();
			int t=r+1-val[i];
			if(t>r)js();
			for(int j=1;j<=t;++j)d[i].push_back(sk[r]),dep[sk[r--]]++;
			if(r)d[sk[r]].push_back(i),dep[i]++;
			sk[++r]=i;
		}else{
			if(r)d[sk[r]].push_back(i),dep[i]++;
			sk[++r]=i;	
		}
	}
	int l=1,r=0;
	for(int i=1;i<=n;++i)if(dep[i]==0)sk[++r]=i;
	while(l<=r){
		int p=sk[l++];ans[p]=l-1;
		for(int i=0;i<(int)d[p].size();++i){
			int v=d[p][i];
			dep[v]--;
			if(dep[v]==0)sk[++r]=v;
		}
	}
	for(int i=1;i<=n;++i)printf("%d ",ans[i]);
}
