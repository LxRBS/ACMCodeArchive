#include <bits/stdc++.h>
using namespace std;
#define rep(i,h,t) for (int i=h;i<=t;i++)
#define dep(i,t,h) for (int i=t;i>=h;i--)
#define ll long long
const int N=5e5;
int n,m,s,k;
ll dis[N][2];
int gg[N];
bool vis[N][2];
struct re{
	ll a,b,p;
	bool operator <(const re x) const{
		return b>x.b;
	}
};
vector<re> ve[N];
priority_queue<re> Q;
int main()
{
    ios::sync_with_stdio(false);
	int T;
	cin>>T;
	int cnt=0; 
	while (T--)
	{ 
		cin>>n>>m>>s>>k;
		rep(i,1,m)
		{
			int x,y,z,zz;
			cin>>x>>y>>z>>zz;
			ve[x].push_back({y,z,zz});	
		}
		set<int> S;
		rep(i,1,n)
		  if (i!=s) S.insert(i);
		rep(i,1,n) dis[i][0]=dis[i][1]=1e18,vis[i][0]=vis[i][1]=0;
		dis[s][0]=0;
		Q.push({s,0,0});
		while (!Q.empty())
		{
			cnt++;
			int x=Q.top().a; int yy=Q.top().p,y; Q.pop();
			if(yy==0) S.erase(x);
			if (yy==1)
			{
				for (auto v:ve[x]) gg[v.a]=cnt;
				vector<int> ve; 
				for (auto v:S)
				  if (gg[v]!=cnt) 
				  {
				    dis[v][0]=dis[x][yy];
				    Q.push({v,dis[v][0],0}); 
				    ve.push_back(v);
				  }
				for (auto v:ve) S.erase(v);
//				cerr<<S.size()<<endl; 
		    }
			if (yy==1) y=-k; else y=0;
			if (vis[x][yy]) continue; vis[x][yy]=1;
			for (auto v:ve[x])
			{
				int k=v.p;
				if (dis[v.a][k]>dis[x][yy]+v.b+y)
				{
					dis[v.a][k]=dis[x][yy]+v.b+y;
					Q.push({v.a,dis[v.a][k],k});
				}
			}
		}
		rep(i,1,n) ve[i].clear();
		rep(i,1,n) 
		if (min(dis[i][0],dis[i][1])!=1e18) cout<<min(dis[i][0],dis[i][1])<<" ";
		else cout<<-1<<" ";
		cout<<"\n";
	} 
}
/*
2
5 4 1 1
1 2 4 0
1 3 5 0
3 4 3 1
4 5 3 0

5 3 1 1
1 2 4 0
1 3 5 0
3 4 3 1
*/
