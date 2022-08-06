#include<bits/stdc++.h>
using namespace std;
int t,n;
long long x;
vector<int>d;
long long get(int x,int n)
{
	if (x==d.size()) return n;
	if (n<2) return 0;
	return d[x]?get(x+1,n/2):get(x+1,(n+1)/2);
}
long long dg(int x,int l,int r)
{
	if (x==d.size()) return 1ll*(l+r)*(r-l+1)/2;
	if (l==1) l++;
	if (l>r) return 0;
	if (d[x])
	{
		long long ans=dg(x+1,l/2,r/2)*2;
		if (l%2==1) ans-=get(x+1,l/2);
		if (r%2==0) ans-=get(x+1,r/2);
		return ans;
	}
	else
	{
		long long ans=dg(x+1,(l+1)/2,(r+1)/2)*2;
		if (l%2==0) ans-=get(x+1,(l+1)/2);
		if (r%2==1) ans-=get(x+1,(r+1)/2);
		return ans;
	}
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>t;
	while (t--)
	{
		cin>>n>>x;
		d.clear();
		while (x) d.emplace_back(x&1),x>>=1;
		d.pop_back();
		reverse(d.begin(),d.end());
		cout<<dg(0,1,n)<<'\n';
	}
	return 0;
}