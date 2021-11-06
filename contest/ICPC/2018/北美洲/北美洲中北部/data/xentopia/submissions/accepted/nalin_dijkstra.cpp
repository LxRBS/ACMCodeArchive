#include <iostream>
#include <cstdio>
#include <vector>
#include <set>
using namespace std;

typedef long long int lli;

const lli maxn = 505, inf = lli(1e18)+5;

vector<vector<vector<lli>>> D;
vector<pair<lli, pair<lli, lli>>> graph[maxn];

int main(void)
{
	lli n, m, k1, k2, s, t, u, v, x, c;
	scanf("%lld%lld%lld%lld", &n, &m, &k1, &k2);
	while(m--)
	{
		scanf("%lld%lld%lld%lld", &u, &v, &x, &c);
		u--, v--;
		graph[u].push_back({v, {x, c}});
		graph[v].push_back({u, {x, c}});
	}

	scanf("%lld%lld", &s, &t);
	s--, t--;

	set<pair<lli, pair<lli, pair<lli, lli>>>> Q;

	D.clear(); D.resize(n, vector<vector<lli>>(k1+2, vector<lli>(k2+2, inf)));
	D[s][k1][k2] = 0;
	Q.insert({D[s][k1][k2], {s, {k1, k2}}});

	while(!Q.empty())
	{
		pair<lli, pair<lli, pair<lli, lli>>> top = *Q.begin();
		Q.erase(Q.begin());

		for(auto it: graph[top.second.first])
		{
			pair<lli, pair<lli, pair<lli, lli>>> x;
			x.first = inf;
			lli dist = it.second.first+D[top.second.first][top.second.second.first][top.second.second.second];
			if(it.second.second == 0)
			{
				x = {dist, {it.first, top.second.second}};
			}
			if(it.second.second == 1 && top.second.second.first)
			{
				x = {dist, {it.first, {top.second.second.first-1, top.second.second.second}}};
			}
			if(it.second.second == 2 && top.second.second.second)
			{
				x = {dist, {it.first, {top.second.second.first, top.second.second.second-1}}};
			}

			if(x.first < D[x.second.first][x.second.second.first][x.second.second.second])
			{
				Q.erase({D[x.second.first][x.second.second.first][x.second.second.second], x.second});
				D[x.second.first][x.second.second.first][x.second.second.second] = x.first;
				Q.insert(x);
			}
		}
	}

	if(D[t][0][0] == inf) printf("-1\n");
	else printf("%lld\n", D[t][0][0]);
}