#include<bits/stdc++.h>
using namespace std;

int n;
int a[1000005];



void solve(){
	cin>>n;
	for(int i=0;i<=n;++i){
		cin>>a[i];
	}
	for(int i=n;i>0;--i){
		a[i-1]+=a[i]/2;
	}
	if(a[0]) cout<<"Alice\n";
	else cout<<"Bob\n";
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
