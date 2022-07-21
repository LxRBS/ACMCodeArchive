#include<bits/stdc++.h>
using namespace std;


int n,m,cnt;

bitset<1050> f[1050],g[1050];


void solve(){
	cin>>n>>m;
	for(int j=0;j<1024;++j){
		f[j].reset();
	}
	f[0][0]=1;
	int x,y;
	int ans=-1;
	for(int i=1;i<=n;++i){
		cin>>x>>y;
		for(int j=0;j<1024;++j){
			g[j]=f[j];
			g[j]<<=x;
		}
		for(int j=0;j<1024;++j){
			f[j]|=g[j^y];
		}
	}
	
	for(int j=0;j<1024;++j){
		if(f[j][m]){
			ans=j;
		}
	}
	cout<<ans<<endl;
	return;
}

int main(){
	std::ios::sync_with_stdio(false);
	cin.tie(0);
	int t=1;cin>>t;
	for(int i=1;i<=t;++i){
		solve();
	}
	return 0;
} 
