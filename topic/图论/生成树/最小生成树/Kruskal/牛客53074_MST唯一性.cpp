/**
 * 给定一个图，保持原图MST的前提下，使得MST方案唯一
 * 问最少要删除多少条边
 * 只有那些边权相等的边有可能造成MST方案不唯一
 * 只需在Kruskal过程中记录一下即可
*/
#include <bits/stdc++.h>
using namespace std;

#ifndef ONLINE_JUDGE
int const SIZE = 13;
#else
int const SIZE = 200010;
#endif

int Father[SIZE];
void init(int n){for(int i=0;i<=n;++i)Father[i]=i;}
int find(int x){return x==Father[x]?x:Father[x]=find(Father[x]);}
void unite(int x, int y){Father[find(y)]=find(x);}

typedef long long llt;
typedef tuple<llt, int, int> t3t;
typedef vector<t3t> v3t;

int N, M;
v3t Edges;
unordered_map<llt, int> Cnt;

llt Kruskal(){
	init(N);
	sort(Edges.begin(), Edges.end());
 
    int u, v, cnt = N - 1;
    llt ans = 0;
    for(const auto &e: Edges){
		if(find(u = get<1>(e)) == find(v = get<2>(e))) continue;

		unite(u, v);
		ans += get<0>(e) * (Cnt[get<0>(e)] - 1);

		if(0 == --cnt) break;
	}	
	return ans;
}


int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif    
    while(2 == scanf("%d%d", &N, &M)){
        Edges.clear(); Edges.reserve(M);
		Cnt.clear();
		for(int a,b,w,i=0;i<M;++i){
            scanf("%d%d%d", &a, &b, &w);
            Edges.emplace_back(w, a, b);
			++Cnt[w];
		}
		printf("%lld\n", Kruskal());
	}
    return 0;
}
