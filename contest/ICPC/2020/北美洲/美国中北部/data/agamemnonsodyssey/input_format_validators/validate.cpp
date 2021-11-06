#include <iostream>
#include <cstdio>
#include <vector>
#include <set>
using namespace std;

const int MAXN = 200000;
const int MAXK = 1000000000;
const int MAXW = 1000000000;

int visited[MAXN];
vector<pair<int, int>> graph[MAXN];

bool dfs(int node, int par)
{
	visited[node] = 1;
	for(auto it: graph[node])
	{
		if(it.first == par) continue;
		if(visited[it.first] || !dfs(it.first, node)) return false;
	}
	return true;
}

int main(void)
{
	int n, k;
	scanf("%d%d", &n, &k);
	if(!(1 <= n && n <= MAXN))
	{
		cerr << "n out of bounds\n";
		return 1;
	}
	if(!(1 <= k && k <= MAXK))
	{
		cerr << "k out of bounds\n";
		return 2;
	}

	for (int i = 1;i < n;i++)
	{
		int u, v, c;
		scanf("%d%d%d", &u, &v, &c);
		if(!(1 <= u && u <= n) || !(1 <= v && v <= n))
		{
			cerr << "node labels out of bounds\n";
			return 3;
		}
		if(!(1 <= c && c <= MAXW))
		{
			cerr << "edge weight out of bounds\n";
			return 4;
		}

		u--, v--;
		graph[u].push_back({v, c});
		graph[v].push_back({u, c});
	}

	if(!dfs(0, -1))
	{
		cerr << "tree has cycle\n";
		return 5;
	}
	for(int i = 0;i < n;i++)
	{
		if(!visited[i])
		{
			cerr << "tree not connected\n";
			return 6;
		}
	}

    int blah1, blah2;
    if (cin >> blah1 >> blah2) {
        cerr << "input too long\n";
        return 7;
    }

	cerr << "OK.\nn, k: " << n << " " << k << "\n";
    return 42;
}