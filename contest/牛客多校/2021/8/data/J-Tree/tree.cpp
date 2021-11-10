#include <bits/stdc++.h>

const int maxn = 500111;

std::vector<int> g[maxn];
int n, s1, s2;

bool in_path[maxn];
int fa[maxn], dep[maxn];

void dfs(int x)
{
	dep[x] = 0;
	for(auto v : g[x]) if(v != fa[x] && !in_path[v])
	{
		fa[v] = x;
		dfs(v);
		dep[x] = std::max(dep[x], dep[v] + 1);
	}
}

int dp[maxn], maxL[maxn], maxR[maxn];
int main()
{
	scanf("%d%d%d", &n, &s1, &s2);
	for(int i=1, u, v; i<n; i++)
	{
		scanf("%d%d", &u, &v);
		g[u].push_back(v);
		g[v].push_back(u);
	}
	
	dfs(s1);
	std::vector<int> path;
	int v = s2;
	while(v != s1)
	{
		path.push_back(v);
		v = fa[v];
	}
	path.push_back(s1);
	std::reverse(path.begin(), path.end());
	
	for(auto v : path) in_path[v] = 1;
	for(auto v : path) dfs(v);
	
	int mid = (path.size() - 1) / 2;
	
	dp[(int)path.size() - 1] = 0x3f3f3f3f;
	memset(maxL, 0xf3, sizeof(maxL));
	memset(maxR, 0xf3, sizeof(maxR));
	
	//for(int i=0; i<(int)path.size(); i++) printf("%d ", dep[path[i]]); puts("");
	for(int i=(int)path.size() - 2; i>=0; i--)
	{
		int L = (i + 1) / 2, R = (int)path.size() - 1 - i / 2;
		if(i % 2 == 0)
		{
			maxR[i] = maxR[i + 2];
			maxR[i] = std::max(maxR[i], dep[path[R]] - R);
			maxR[i] = std::max(maxR[i], dep[path[L+1]] - L - 1);
			dp[i] = std::max(1 - dp[i+1], dep[path[L]] - (maxR[i] + R));
		}
		else
		{
			maxL[i] = maxL[i + 2];
			maxL[i] = std::max(maxL[i], dep[path[R-1]] + R - 1);
			maxL[i] = std::max(maxL[i], dep[path[L]] + L);
			dp[i] = std::max(1 - dp[i+1], dep[path[R]] - (maxL[i] - L));
		}
	}
	
	printf("%d\n", dp[0]);
	return 0;
}