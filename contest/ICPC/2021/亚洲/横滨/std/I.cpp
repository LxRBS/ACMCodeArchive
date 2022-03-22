#include<bits/stdc++.h>
#define ll long long
#define P pair<int,int>
using namespace std;
const int maxn=1e5+5;
int n,k;
struct nod{
	int v,h;
}a[maxn];
ll dp[maxn][205];
int main() {
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++) {
		scanf("%d%d",&a[i].v,&a[i].h);
	}
	sort(a+1,a+n+1,[](nod l,nod r) {return l.h<r.h;});
	for(int i=0;i<=n;i++) for(int j=1;j<=k;j++) dp[i][j]=-1e18;
	ll ans=-1e18;
	for(int i=1;i<=n;i++) {
		dp[i][1]=max(dp[i-1][1],1ll*a[i].v+a[i].h);
		for(int j=2;j<=k;j++) dp[i][j]=max(dp[i-1][j],dp[i-1][j-1]+a[i].v);
		ans=max(ans,dp[i-1][k-1]+a[i].v-a[i].h);
	}
	cout<<ans<<endl;
	return 0;
}