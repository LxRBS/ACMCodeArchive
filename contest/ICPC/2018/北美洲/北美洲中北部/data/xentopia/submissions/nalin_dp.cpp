#include <iostream>
#include <cstdio>
#include <vector>
#include <set>
using namespace std;

typedef long long int lli;

const lli maxn = lli(1e3)+5, inf = lli(1e18)+5;

lli n, s, t, D[maxn], Dt[maxn];
vector<vector<vector<lli>>> memo;
vector<pair<lli, pair<lli, lli>>> graph[maxn], graphT[maxn];

lli DP(lli node, lli k1, lli k2)
{
	if(k1 == 0 && k2 == 0) return Dt[node];
	else if(k1 < 0 || k2 < 0) return inf;
	else if(memo[node][k1][k2] != -1) return memo[node][k1][k2];
	else
	{
		lli res = inf;
		for(auto it: graphT[node])
		{
			if(it.second.second == 1) res = min(res, it.second.first+DP(it.first, k1-1, k2));
			else if(it.second.second == 2) res = min(res, it.second.first+DP(it.first, k1, k2-1));
		}
		return memo[node][k1][k2] = res;
	}
}

void dijkstra(lli node)
{
	set<pair<lli, lli>> Q;
	for(lli i = 0;i < n;i++) D[i] = inf;
	Q.insert({0, node});
	D[node] = 0;

	while(!Q.empty())
	{
		pair<lli, lli> top = *Q.begin();
		Q.erase(Q.begin());

		for(auto it: graph[top.second])
		{
			if(!it.second.second && D[it.first] > D[top.second]+it.second.first)
			{
				Q.erase({D[it.first], it.first});
				D[it.first] = D[top.second]+it.second.first;
				Q.insert({D[it.first], it.first});
			}
		}
	}

	for(lli i = 0;i < n;i++)
	{
		if(D[i] < inf)
		{
			for(auto it: graph[i])
			{
				if(it.second.second) graphT[node].push_back({it.first, {it.second.first+D[i], it.second.second}});
			}
		}
	}

	if(node == t)
	{
		for(lli i = 0;i < n;i++) Dt[i] = D[i];
	}
}

int main(void)
{
	lli m, k1, k2, u, v, x, c;
	scanf("%lld%lld%lld%lld", &n, &m, &k1, &k2);
	memo.clear(); memo.resize(n, vector<vector<lli>>(k1+2, vector<lli>(k2+2, -1)));

	while(m--)
	{
		scanf("%lld%lld%lld%lld", &u, &v, &x, &c);
		u--, v--;
		graph[u].push_back({v, {x, c}});
		graph[v].push_back({u, {x, c}});
	}
	scanf("%lld%lld", &s, &t);
	s--, t--;
	for(lli i = 0;i < n;i++) dijkstra(i);

	lli res = DP(s, k1, k2);
	if(res == inf) printf("-1\n");
	else printf("%lld\n", res);
}