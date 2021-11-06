#include <iostream>
#include <cstdio>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

const int maxn = int(5e5)+5;

string S[maxn];
pair<string, int> tmp[maxn];
map<pair<int, int>, int> mp;

int LCP(int a, int b)
{
	if(mp.find({a, b}) != mp.end()) return mp[{a, b}];
	int l = min(int(S[a].size()), int(S[b].size()));

	for(int i = 0;i < l;i++)
	{
		if(S[a][i] != S[b][i]) return i;
	}

	return mp[{a, b}] = l;
}

int main(void)
{
	int n, q;
	scanf("%d%d", &n, &q);

	for(int i = 0;i < n;i++)
	{
		cin >> S[i];
		tmp[i] = {S[i], i};
	}
	sort(tmp, tmp+n), sort(S, S+n);
	int ctr = 0;
	map<int, int> revmap;
	for(int i = 0;i < n;i++) revmap[tmp[i].second] = ctr++;

	while(q--)
	{
		int k, l, res = 0, idx;
		scanf("%d%d", &k, &l);
		vector<int> X;
		for(int i = 0;i < k;i++)
		{
			scanf("%d", &idx);
			idx--;
			X.push_back(revmap[idx]);
		}

		sort(X.begin(), X.end());

		for(int i = 0;i <= k-l;i++)
		{
			int tot = LCP(X[i], X[i+l-1]), diffA = 0, diffB = 0;
			if(i+l < k) diffA = LCP(X[i], X[i+l]);
			if(i) diffB = LCP(X[i-1], X[i]);

			res += tot-min(max(diffA, diffB), tot);
		}
		printf("%d\n", res);
	}
}