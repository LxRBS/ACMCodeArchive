#include <bits/stdc++.h>
#include "testlib.h"

using namespace std;

int n,m;
vector<map<int,int>> G;
int check(InStream &in)
{
	int d=in.readInt(0,2000000000);
	int k=in.readInt(1,m);
	if(k==1)in.quitf(_wa,"Cycle does not contain any edges");
	vector<int> cyc;
	for(int i=1;i<=k;i++)
	{
		int x=in.readInt(1,n);
		cyc.push_back(x);
	}
	set<tuple<int,int,int>> eg;
	int minn=1e9,maxx=-1e9;
	for(int i=0;i<k;i++)
	{
		int u=cyc[i],v=cyc[(i+1)%k],w;
		if(G[u].find(v)==G[u].end())in.quitf(_wa,"Edge %d-%d does not appear in original graph",u,v);
		else w=G[u][v];
		if(u>v)swap(u,v);
		if(eg.find(make_tuple(u,v,w))!=eg.end())in.quitf(_wa,"Cycle contains repeated edge %d-%d",u,v);
		eg.emplace(u,v,w);
		minn=min(minn,w);
		maxx=max(maxx,w);
	}
	if(d!=maxx-minn)
		in.quitf(_wa, "Cycle has range %d, but output says %d",maxx-minn,d);
	return d;
}

int main(int argc, char* argv[])
{
	registerTestlibCmd(argc, argv);
	
	n=inf.readInt(),m=inf.readInt();
	G.resize(n+5);
	for(int i=1;i<=m;i++)
	{
		int u,v,w;
		u=inf.readInt();
		v=inf.readInt();
		w=inf.readInt();
		G[u][v]=w;
		G[v][u]=w;
	}
	int d1=check(ouf);
	int d2=check(ans);
	if(d1<d2)quitf(_wa,"Participant range less than jury");
	
	quitf(_ok,"ok");
	return 0;
}