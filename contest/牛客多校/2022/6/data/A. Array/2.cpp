#include<bits/stdc++.h>
using namespace std;
int n,m,a[100005],val[200005],ans[1000005];
vector<int>g[200005];int tot;
void dfs(int x,int st,int k){
    if(x<=n){
        for(int i=st;i<=m;i+=k)ans[i]=x;
        return;
    }
    dfs(g[x][0],st,k*2);
    dfs(g[x][1],st+k,k*2);
}
vector<int>buc[100005]; 
int main(){
	freopen("7.in","r",stdin);
	freopen("7.out","w",stdout);
    scanf("%d",&n);
    int mx=1;
    for(int i=1;i<=n;i++)scanf("%d",&a[i]),mx=max(mx,a[i]);
    m=1;while(m<mx)m<<=1;
    for(int i=1;i<=n;i++){
        int pw=1;
        while(pw<=a[i])pw<<=1;
        pw>>=1;
        a[i]=pw;
    }
    priority_queue<pair<int,int> >q;
    for(int i=1;i<=n;i++)q.push(make_pair(a[i],i));
    tot=n;
    while(q.size()>=2){
        pair<int,int>p1=q.top();q.pop();
        pair<int,int>p2=q.top();q.pop();
        int id=++tot;
        g[id].push_back(p1.second);
        g[id].push_back(p2.second);
        val[id]=min(p1.first,p2.first)/2;
        q.push(make_pair(val[id],id));
    }
    dfs(tot,1,1);
    printf("%d\n",m);
    for(int i=1;i<=m;i++)printf("%d ",ans[i]);
	for(int i=1;i<=n;i++)buc[i].push_back(0);
    for(int i=1;i<=m;i++){
		int x=ans[i];
		buc[x].push_back(i);
		buc[x].push_back(i+m);
	}
	for(int i=1;i<=n;i++)buc[i].push_back(m+m+1);
	for(int i=1;i<=n;i++){
		sort(buc[i].begin(),buc[i].end());
		if(buc[i].size()==2)return 1;
		for(int j=1;j<buc[i].size();j++){
			if(buc[i][j]-buc[i][j-1]>a[i])return 1;
		}
	}
    return 0;
}
