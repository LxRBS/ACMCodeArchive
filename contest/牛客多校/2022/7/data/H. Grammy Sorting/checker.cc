#include <bits/stdc++.h>
#include "testlib.h"

using namespace std;

int n,A,B;
vector<vector<int>> G;
int check(InStream &in,vector<int> p)
{
	int m=in.readInt(-1,10000);
	if(m==-1)return -1;
	for(int tt=1;tt<=m;tt++)
	{
		int k=in.readInt(1,n);
		vector<int> a(n+5);
		for(int i=1;i<=k;i++)
		{
			a[i]=in.readInt(1,n);
		}
		if(a[1]!=A)in.quitf(_wa,"a_1 != A at operation #%d",tt);
		for(int i=1;i<k;i++)
		{
			if(not G[a[i]][a[i+1]])
				in.quitf(_wa,"not a path at operation #%d",tt);
		}
		int t=p[a[1]];
		for(int i=1;i<k;i++)
		{
			p[a[i]]=p[a[i+1]];
		}
		p[a[k]]=t;
	}
	vector<int> id(n+5),od(n+5);
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			if(G[i][j] and p[i]<p[j])
			{
				id[j]++;od[i]++;
			}
		}
	}
//	for(int i=1;i<=n;i++)cerr<<i<<' '<<p[i]<<endl;
	for(int i=1;i<=n;i++)
	{
//		cerr<<i<<' '<<id[i]<<' '<<od[i]<<endl;
		if(i!=A and id[i]==0)in.quitf(_wa,"vertex %d cannot be reached from A",i);
		if(i!=B and od[i]==0)in.quitf(_wa,"vertex %d cannot reach B",i);
	}
	return m;
}

int main(int argc, char* argv[])
{
	registerTestlibCmd(argc, argv);
	
	n=inf.readInt();
	int m=inf.readInt();
	A=inf.readInt(),B=inf.readInt();
	G.resize(n+5);
	vector<int> p;
	p.resize(n+5);
	for(int i=1;i<=n;i++)
	{
		G[i].resize(n+5);
		p[i]=inf.readInt();
	}
	for(int i=1;i<=m;i++)
	{
		int u,v;
		u=inf.readInt();
		v=inf.readInt();
		G[u][v]=G[v][u]=1;
	}
	int d1=check(ouf,p);
	int d2=check(ans,p);
	if(d1==-1 and d2!=-1)quitf(_wa,"Jury has answer but participant has not.");
	if(d2==-1 and d1!=-1)quitf(_fail,"Participant has answer but jury has not.");
	
	quitf(_ok,"ok");
	return 0;
}