#include <bits/stdc++.h>
#include "testlib.h"

using namespace std;

const string YES = "YES";
const string NO = "NO";

int n;
vector<int> a;
int check(InStream &in)
{
	string tans = upperCase(in.readToken());

	if (tans != YES && tans != NO)
		in.quitf(_wa, "%s or %s expected in answer, but %s found.",YES.c_str(), NO.c_str(), compress(tans).c_str());
	if(tans==NO)return -1;
	vector<int> vis(n+5),p(n+5);
	for(int i=1; i<=n; i++)
	{
		p[i]=in.readInt(1,n);
		if(vis[p[i]])in.quitf(_wa,"Not a permutation.");
		vis[p[i]]=1;
		if(p[i]==a[i])in.quitf(_wa,"P_%d == A_%d.",i,i);
	}
	if(not in.seekEoln())in.quitf(_pe,"Expected Eoln.");
	return 1;
}

int main(int argc, char* argv[])
{
	registerTestlibCmd(argc, argv);

	int T=inf.readInt();
	while(T--)
	{
		n=inf.readInt();
		a.resize(n+5);
		for(int i=1; i<=n; i++)
		{
			a[i]=inf.readInt();
		}
		int d1=check(ouf);
		int d2=check(ans);
		if(d1==-1 and d2!=-1)quitf(_wa,"Jury has answer but participant has not.");
		if(d2==-1 and d1!=-1)quitf(_fail,"Participant has answer but jury has not.");
	}
	quitf(_ok,"ok");
	return 0;
}
