#include <iostream>
#include <cstdio>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

typedef long long int lli;

const lli maxn = lli(5e5)+5, maxlog = 20;

string S[maxn];
pair<string, lli> tmp[maxn];
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

	if(x == y) return H[x];

	for(int i = maxlog;i >= 0;i--)
	{
		if(T[x][i] != T[y][i]) x = T[x][i], y = T[y][i];
	}
	return H[T[x][0]];
}

lli LCP(lli a, lli b)
{
	return LCA(intrie[a], intrie[b]);
}

int main(void)
{
	lli n, q;
	scanf("%lld%lld", &n, &q);

	for(lli i = 0;i < n;i++)
	{
		cin >> S[i];
		tmp[i] = {S[i], i};
	}
	sort(tmp, tmp+n), sort(S, S+n);

	pnode* root = new pnode();
	for(int i = 0;i < n;i++) insert(root, S[i], 0, i);

	dfs0(root, 0, -1);

	tot = cur;
	for(int i = 0;i < tot;i++)
	{
		for(int j = 1;j <= maxlog;j++) T[i][j] = -1;
	}
	init();

	lli ctr = 0;
	map<lli, lli> revmap;
	for(lli i = 0;i < n;i++) revmap[tmp[i].second] = ctr++;

	while(q--)
	{
		lli k, l, res = 0, idx;
		scanf("%lld%lld", &k, &l);
		vector<lli> X;
		for(lli i = 0;i < k;i++)
		{
			scanf("%lld", &idx);
			idx--;
			X.push_back(revmap[idx]);
		}

		sort(X.begin(), X.end());

		for(lli i = 0;i <= k-l;i++)
		{
			lli tot = LCP(X[i], X[i+l-1]), diffA = 0, diffB = 0;
			if(i+l < k) diffA = LCP(X[i], X[i+l]);
			if(i) diffB = LCP(X[i-1], X[i]);
			//cout << tot << " " << diffA << " " << diffB << "\n";

			res += tot-min(max(diffA, diffB), tot);
		}
		printf("%lld\n", res);
	}
}