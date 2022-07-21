#include <bits/stdc++.h>
#define maxn 200086
 
using namespace std;
 
int t, n;
set<int> v[maxn], w[maxn];
int fa[maxn], siz[maxn];
 
int find(int x){
	return x == fa[x] ? x : fa[x] = find(fa[x]);
}
 
int main(){
	scanf("%d", &t);
	for(int T = 1;T <= t;T++){
		scanf("%d", &n);
		for(int i = 1;i <= n;i++) v[i].clear(), w[i].clear(), fa[i] = i, siz[i] = 1;
		for(int i = 1;i <= n;i++){
			int k;
			scanf("%d", &k);
			while(k--){
				int x;
				scanf("%d", &x);
				v[x].insert(i);
				w[i].insert(x);
			}
		}
		queue<pair<int, int> > q;
		for(int i = 1;i <= n;i++) if(w[i].size() == 1) q.push({i, *w[i].begin()});
		while(!q.empty()){
			int x = find(q.front().first), y = find(q.front().second);q.pop();
			if(x == y) continue;
			if(v[x].size() > v[y].size()) swap(x, y), swap(w[x], w[y]);
			fa[x] = y, siz[y] += siz[x];
			for(auto i : v[x]){
				int to = find(i);
				if(to == y) continue;
				v[y].insert(to), w[to].erase(x), w[to].insert(y);
				if(w[to].size() == 1) q.push({to, *w[to].begin()});
			}
		}
		int ans = 0;
		for(int i = 1;i <= n;i++) ans = max(ans, siz[find(i)]);
		printf("Case #%d: %d\n", T, ans);
	}
}
/*
1
5
2 4 5
1 3
1 1
1 5
0
*/
