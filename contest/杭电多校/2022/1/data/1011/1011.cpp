#include <bits/stdc++.h>
using namespace std;
const int mo=1e9+7;
int main()
{
	ios::sync_with_stdio(false);
	int gg=(mo+1)/2;
	int T;
	cin>>T;
	while (T--)
	{
		int n,m;
		cin>>n>>m;
		cout<<1ll*(n-m)*gg%mo<<endl;
	}
	return 0;
}
