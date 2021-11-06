#include <iostream>
#include <cstdio>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;

const int maxn = int(5e5)+5, maxlog = 20;

int n, l, tot, ans = 0, cur = 0, T[maxn][maxlog+1], intrie[maxn], strt[maxn], en[maxn], sig[maxn], H[maxn];
vector<int> graphT[maxn];

struct pnode {
	int e = -1;
	pnode* child[27]={NULL};
};

void insert(pnode* root, string& S, int idx, int cur)
{
	if(idx == int(S.size()))
	{
		root->e = cur;
		return;
	}

	int c = int(S[idx]-'a');
	if(!root->child[c]) root->child[c] = new pnode();
	insert(root->child[c], S, idx+1, cur);
}

void dfs0(pnode* root, int ht, int par)
{
	int node = cur++;
	strt[node] = node;
	if(root->e != -1) intrie[root->e] = node;
	H[node] = ht, T[node][0] = par;

	for(int i = 0;i < 27;i++)
	{
		if(root->child[i]) dfs0(root->child[i], ht+1, node);
	}
	en[node] = cur++;
}

void init()
{
	for(int j = 1;j <= maxlog;j++)
	{
		for(int i = 0;i < tot;i++)
		{
			if(T[i][j-1] != -1) T[i][j] = T[T[i][j-1]][j-1];
		}
	}
}

int LCA(int x, int y)
{
	if(H[x] > H[y]) swap(x, y);

	for(int i = maxlog;i >= 0;i--)
	{
		if(H[y]-(1<<i) >= H[x]) y = T[y][i];
	}

	if(x == y) return x;

	for(int i = maxlog;i >= 0;i--)
	{
		if(T[x][i] != T[y][i]) x = T[x][i], y = T[y][i];
	}
	return T[x][0];
}

void dfs1(int node, int par)
{
	for(auto it: graphT[node])
	{
		dfs1(it, node);
		sig[node] += sig[it];
	}

	if(sig[node] == l)
	{
		ans += H[node];
		if(par != -1) ans -= H[par];
	}
}

void solve()
{
	int k, x;
	scanf("%d%d", &k, &l);

	vector<pair<pair<int, int>, int>> eve;
	eve.push_back({{strt[0], 1}, 0});
	for(int i = 0;i < k;i++)
	{
		scanf("%d", &x);
		x--;
		int y = intrie[x];
		sig[y]++;
		eve.push_back({{strt[y], 1}, y});
	}

	sort(eve.begin(), eve.end());

	int len = int(eve.size());
	for(int i = 0;i < len-1;i++)
	{
		int lc = LCA(eve[i].second, eve[i+1].second);
		eve.push_back({{strt[lc], 1}, lc});
	}

	len = int(eve.size());
	for(int i = 0;i < len;i++)
	{
		int y = eve[i].second;
		eve.push_back({{en[y], 0}, y});
	}
	sort(eve.begin(), eve.end());
	eve.resize(int(unique(eve.begin(), eve.end())-eve.begin()));
	stack<int> S;

	for(auto it: eve)
	{
		if(it.first.second)
		{
			if(!S.empty()) graphT[S.top()].push_back(it.second);
			S.push(it.second);
		}
		else S.pop();
	}
	dfs1(0, -1);
	printf("%d\n", ans);

	ans = 0;
	for(auto it: eve) sig[it.second] = 0, graphT[it.second].clear();
}

int main(void)
{
	int q;
	scanf("%d%d", &n, &q);
	string S;
	pnode* root = new pnode();
	for(int i = 0;i < n;i++)
	{
		cin >> S;
		insert(root, S, 0, i);
	}

	dfs0(root, 0, -1);

	tot = cur;
	for(int i = 0;i < tot;i++)
	{
		for(int j = 1;j <= maxlog;j++) T[i][j] = -1;
	}
	init();

	while(q--) solve();
}