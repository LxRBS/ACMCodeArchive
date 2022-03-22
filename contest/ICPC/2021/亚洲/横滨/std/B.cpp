#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn=3e5+5;
char mp[40][40];
int n,m;
ll dfs(int p,int l,int r) {
	for(int i=l;i<=r;i++) {
		if(mp[p][i]!='.') {
			if(mp[p][i]>='0'&&mp[p][i]<='9') return mp[p][i]-'0';
			else {
				ll sl=dfs(p+1,l,i-1),sr=dfs(p+1,i+1,r);
				if(mp[p][i]=='+') return sl+sr;
				else if(mp[p][i]=='-') return sl-sr;
				else if(mp[p][i]=='*') return sl*sr;
			}
		}
	}
}
int main() {
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) scanf("%s",mp[i]+1);
	cout<<dfs(1,1,m)<<endl;
	return 0;
}