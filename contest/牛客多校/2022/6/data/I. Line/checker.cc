#include<fstream>
#include<bits/stdc++.h>
using namespace std;
int n,d,x[11],y[11],m;
pair<int,int>p[100005];
int main(){
	ifstream fin("input");
	ifstream fout("user_output");
	fin>>n>>d;
	for(int i=1;i<=n;i++)fin>>x[i]>>y[i];
	fout>>m;
	if(m>100000||m<=0)return 1;
	for(int i=1;i<=m;i++)fout>>p[i].first>>p[i].second;
	sort(p+1,p+m+1);
	for(int i=2;i<=m;i++)if(p[i-1]==p[i])return 1;
	for(int i=1;i<=n;i++){
		map<long long,int>cnt;
		for(int j=1;j<=m;j++){
			cnt[1ll*p[j].first*y[i]-1ll*p[j].second*x[i]]++;
		}
		for(auto p:cnt)if(p.second!=d)return 1;
	}
	return 0;
}
