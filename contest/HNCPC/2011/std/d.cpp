#include <vector> 
#include <list> 
#include <map> 
#include <set> 
#include <deque> 
#include <queue> 
#include <stack> 
#include <bitset> 
#include <algorithm> 
#include <functional> 
#include <numeric> 
#include <utility> 
#include <sstream> 
#include <iostream> 
#include <iomanip> 
#include <cstdio> 
#include <cmath> 
#include <cstdlib> 
#include <cctype> 
#include <string> 
#include <cstring> 
#include <ctime> 

using namespace std;

char a[15][15];
char a1[15][15];
char best[15][15];
vector<pair<int,int> > p;
int d[100];
int used[100];
int nn,n;

void search2(int x)
{
	int i,j,k,xx,yy,cnt,start,dx,dy;
	vector<int> q;
	if (x==nn)
	{
		memcpy(a1,a,sizeof(a1));
		memset(used,0,sizeof(used));
		q.clear();
		q.push_back(0);
		used[0]=1;
		for (i=0;i<q.size();i++)
		{
			xx=p[d[q[i]]].first;
			yy=p[d[q[i]]].second;
			for (j=0;j<nn;j++)
				if ((used[j]==0)&&(abs(p[d[j]].first-xx)+abs(p[d[j]].second-yy)==1))
				{
					used[j]=1;
					q.push_back(j);
				}
		}
		if (q.size()!=nn) return;
		memset(used,0,sizeof(used));
		for (i=0;i<nn;i++)
		{
			used[d[i]]=1;
			a1[p[d[i]].first][p[d[i]].second]='A';
		}
		cnt=1;
		for (i=0;i<p.size();i++)
			if (used[i]==0)
			{
				used[i]=1;
				a1[p[i].first][p[i].second]='A'+cnt;
				for (j=1;j<nn;j++)
				{
					dx=p[d[j]].first-p[d[0]].first;
					dy=p[d[j]].second-p[d[0]].second;
					xx=p[i].first+dx;
					yy=p[i].second+dy;
					for (k=0;k<p.size();k++)
						if ((used[k]==0)&&(p[k].first==xx)&&(p[k].second==yy))
							break;
					if (k==p.size()) return;
					used[k]=1;
					a1[xx][yy]='A'+cnt;
				}
				cnt++;
			}
		for (i=0;i<n;i++)
			for (j=0;j<n;j++)
			{
				if (best[i][j]<a1[i][j]) return;
				if (best[i][j]>a1[i][j])
				{
					memcpy(best,a1,sizeof(a1));
					return;
				}
			}
		return;
	}
	if (x==0) start=0;
	else start=d[x-1]+1;
	for (i=start;i<p.size();i++)
	{
		d[x]=i;
		search2(x+1);
	}
}

void search1(int x)
{
	int i,j,k,start,dx,dy,xx,yy;
	vector<int> aa;
	vector<int> q;
	if (x==nn)
	{
		memcpy(a1,a,sizeof(a));
		memset(used,0,sizeof(used));
		for (i=0;i<nn;i++)
		{
			used[d[i]]=1;
			a1[p[d[i]].first][p[d[i]].second]='A'+i;
		}
		aa.clear();
		aa.push_back(d[0]);
		for (i=0;i<p.size();i++)
			if (used[i]==0)
			{
				aa.push_back(i);
				used[i]=1;
				a1[p[i].first][p[i].second]='A'+0;
				for (j=1;j<nn;j++)
				{
					dx=p[d[j]].first-p[d[0]].first;
					dy=p[d[j]].second-p[d[0]].second;
					xx=p[i].first+dx;
					yy=p[i].second+dy;
					for (k=0;k<p.size();k++)
						if ((used[k]==0)&&(p[k].first==xx)&&(p[k].second==yy))
						{
							used[k]=1;break;
						}
					if (k==p.size()) return;
					a1[p[k].first][p[k].second]='A'+j;
				}
			}
		memset(used,0,sizeof(used));
		q.clear();
		q.push_back(0);
		used[0]=1;
		for (i=0;i<q.size();i++)
		{
			xx=p[aa[q[i]]].first;
			yy=p[aa[q[i]]].second;
			for (j=0;j<aa.size();j++)
				if ((used[j]==0)&&(abs(p[aa[j]].first-xx)+abs(p[aa[j]].second-yy)==1))
				{
					used[j]=1;
					q.push_back(j);
				}
		}
		if (q.size()!=aa.size()) return;
		for (i=0;i<n;i++)
			for (j=0;j<n;j++)
			{
				if (best[i][j]<a1[i][j]) return;
				if (best[i][j]>a1[i][j])
				{
					memcpy(best,a1,sizeof(a1));
					return;
				}
			}
		return;
	}
	if (x==0) start=0;
	else start=d[x-1]+1;
	for (i=start;i<p.size();i++)
	{
		d[x]=i;
		search1(x+1);
	}
}

int main()
{
	int i,j,cnt;
	double cl = clock();
	
	while (scanf("%d",&n)!=EOF)
	{
		if (n==0) break;
		for (i=0;i<n;i++)
			scanf("%s",a[i]);
		cnt=0;
		p.clear();
		for (i=0;i<n;i++)
			for (j=0;j<n;j++)
				if (a[i][j]=='*')
				{
					p.push_back(make_pair(i,j));
					cnt++;
				}
		memset(best,0,sizeof(best));
		for (i=0;i<n;i++)
			for (j=0;j<n;j++)
				best[i][j]='a';
		for (i=2;i<=cnt;i++)
			if (cnt%i==0)
			{
				j=cnt/i;
				if (i<=j)
				{
					nn=i;
					search1(0);
				}
				else
				{
					nn=j;
					search2(0);
				}
				if (best[0][0]!='a') break;
			}
		for (i=0;i<n;i++)
			printf("%s\n",best[i]);
		printf("\n");
	}
	
	cl = clock() - cl;
	fprintf(stderr, "Total Execution Time = %lf seconds\n", cl / CLOCKS_PER_SEC);
	
	return 0;
}

