#include<bits/stdc++.h>
using namespace std;
const int maxn=3e4+5;
int in[maxn],n;
vector<int>lik[maxn];
vector<int>col[maxn];
int f[maxn],dfn[maxn],low[maxn];
bool vis[maxn];
int idx,tot;
stack<int>s;
void tarjan(int u) {
	dfn[u]=low[u]=++idx;
	s.push(u);
	vis[u]=1;
	for(auto v:lik[u]) {
		if(!dfn[v]) {
			tarjan(v);
			low[u]=min(low[u],low[v]);
		} else if(vis[v]) {
			low[u]=min(low[u],dfn[v]);
		}
	}
	if(dfn[u]==low[u]) {
		tot++;
		int tmp;
		do{
			tmp=s.top();s.pop();
			col[tot].push_back(tmp);
			f[tmp]=tot;
			vis[tmp]=0;
		}while(tmp!=u);
		col[tot].push_back(u);
		f[u]=tot;
		vis[u]=0;
	}
}
int main() {
	int m,u,v;
	vector<int>ans;
	scanf("%d%d",&n,&m);
	for(int i=0;i<m;i++) {
		scanf("%d%d",&u,&v);
		lik[u].push_back(v);
	}
	for(int i=1;i<=n;i++) {
		if(!dfn[i]) tarjan(i);
	}
	for(int i=1;i<=n;i++) {
		for(auto v:lik[i]) {
			if(f[i]!=f[v]) {
				in[f[v]]++;
			}
		}
	}
	for(int i=1;i<=tot;i++) {
		if(in[i]==0) {
			ans.push_back(*min_element(col[i].begin(),col[i].end()));
		}
	}
	sort(ans.begin(),ans.end());
	for(auto x:ans) printf("%d\n",x);
	return 0;
}