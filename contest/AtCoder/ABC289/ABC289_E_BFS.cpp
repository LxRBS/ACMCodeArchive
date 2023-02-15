/**
 * 无向图，每个节点有两种颜色。两个人分别从1和N出发，要到达N和1。
 * 要求是每一步两人必须去往不同颜色的格子。问最短多少步到达。
 * 做一个pair的队列，然后广搜即可。
 */
#include <bits/stdc++.h>
using namespace std;

char *__abc147, *__xyz258, __ma369[100000];
#define __hv007() ((__abc147==__xyz258) && (__xyz258=(__abc147=__ma369)+fread(__ma369,1,100000,stdin),__abc147==__xyz258) ? EOF : *__abc147++)
 
int getInt(){
	int sgn = 1;
	char ch = __hv007();
	while( ch != '-' && ( ch < '0' || ch > '9' ) ) ch = __hv007();
	if ( '-' == ch ) {sgn = 0;ch=__hv007();}
 
	int ret = (int)(ch-'0');
	while( '0' <= (ch=__hv007()) && ch <= '9' ) ret = ret * 10 + (int)(ch-'0');
	return sgn ? ret : -ret;
}

using llt = long long;
using vi = vector<int>;
using vll =vector<llt>;
using edge_t = tuple<int, int, int, int>;
using ve = vector<edge_t>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vpii = vector<pii>;

llt const MOD = 1E9+7LL;

int N, M;
vvi G0, G1;
vi W;
vvi Flag;
map<pii, int> Map;
int proc(){
	// Map.clear();
	Flag.assign(N + 1, vi(N + 1, 0));
    queue<pii> q;
	q.push({1, N});
	// Map[{1, N}] = 0;
	Flag[1][N] = 1;
	int k = 0, sz;
	while(sz = q.size()){
		if(0 == sz) break;
		++k;
		while(sz--){
            auto h = q.front(); q.pop();
            for(int i : G0[h.first])for(int j : G1[h.second]){
				if(N == i && 1 == j) return k;
				// auto it = Map.find({i, j});
				// if(it != Map.end()) continue;
				// it = Map.insert(it, {{i, j}, k});
				if(Flag[i][j]) continue;
				Flag[i][j] = 1;
				q.push({i, j});
			}
            for(int i : G1[h.first])for(int j : G0[h.second]){
				if(N == i && 1 == j) return k;
				// auto it = Map.find({i, j});
				// if(it != Map.end()) continue;
				// it = Map.insert(it, {{i, j}, k});
				if(Flag[i][j]) continue;
				Flag[i][j] = 1;
				q.push({i, j});
			}
		}
	}
	return -1;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    // ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int nofkase = getInt();
	while(nofkase--){
        N = getInt(); M = getInt();
		W.assign(N + 1, 0);
		G0.assign(N + 1, vi());
		G1.assign(N + 1, vi());
		for(int i=1;i<=N;++i) W[i] = getInt();
		for(int a,b,i=0;i<M;++i){
            a = getInt(); b = getInt();
			if(W[b] == 0) G0[a].push_back(b);
			else G1[a].push_back(b);
			if(0 == W[a]) G0[b].push_back(a);
			else G1[b].push_back(a);
		}
		printf("%d\n", proc());
	}
    return 0; 
}