/**
 * 本质上就是给定一个图，对每个点i，最多有M条边，且边的终点必然是[i+1, i+M]之间
 * M在10
 * 现在问：对 k = 2,3,...,N-1 去掉k，从1到N的最短路是多少。即要回到 N-2 次
 * 令Ui记录从1到i的最短路，Vi记录从i到N的最短路，
 * 对每个k点，考察 i = k+1,...,k+M-1，再令j为i的入点且大于k，则可肯定
 * 所有不经过k的方案必然是某个(j, i)之一
 * 计算一下 min{Uj + Vi + 1} 即可
 * O(N*M^2)
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



#ifndef ONLINE_JUDGE
int const SIZE = 21;
#else
int const SIZE = 66;
#endif

using llt = long long;
using vi = vector<int>;
using vll =vector<llt>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vpii = vector<pii>;

llt const MOD = 998244353LL;
int const INF = INT32_MAX;

int N, M;
vvi G, Ig;

vi U, V;

void calc(const vvi & g, vi & d, int s){
    d.assign(N + 1, INF);
	d[s] = 0;

	queue<int> q;
	q.push(s);

	int sz = 0, k = 0;
	while(sz = q.size()){
		++k;
		while(sz--){
			auto h = q.front(); q.pop();
			for(int i : g[h]){
				if(d[i] != INF) continue;

				d[i] = k;
				q.push(i);
			}
		}
	}
	return;
}

int proc(int idx){
	int ans = INF;
	for(int i=idx+1;i<=min(idx+M-1, N);++i){
		for(int j : Ig[i]){
            if(j >= idx) break;
			if(U[j] != INF && V[i] != INF){
				ans = min(ans, U[j] + V[i]);
			}
		}
	}
    return ans == INF ? -1 : ans + 1;
}

void proc(){
    calc(G, U, 1);
	calc(Ig, V, N);

	for(int i=2;i<N;++i){
		printf("%d ", proc(i));
	}
	printf("\n");
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	// int nofkase; scanf("%d", &nofkase);
    cin >> N >> M;
	G.assign(N + 1, vi());
	Ig.assign(N + 1, vi());
	for(int i=0;i<N;++i){
		string s; cin >> s;
		for(int j=0;j<M;++j){
			if('1' == s[j]){
                G[i + 1].push_back(i + 1 + j + 1);
				Ig[i + 1 + j + 1].push_back(i + 1);
			}
		}
	}
	proc();
    return 0; 
}