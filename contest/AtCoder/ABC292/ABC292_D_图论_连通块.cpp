/**
 * 给一个无向图，问是否每个连通块都满足点数量等于边数量
 * 对每一个连通块，判断一下即可。
 * 广搜和深搜都可以。这里用了BFS
 */
#include <bits/stdc++.h>
using namespace std;

#include <bits/extc++.h>
using namespace __gnu_pbds;

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

int N, M;
vvi G;
vi Flag;

bool proc(int u){
	Flag[u] = 1;
	queue<int> q;
	q.push(u);
	vi vec;
	
	while(!q.empty()){
        auto h = q.front(); q.pop();
		vec.push_back(h);

		for(int v : G[h]){
			if(Flag[v]) continue;
			Flag[v] = 1;
			q.push(v);
		}
	}

	int nodesize = vec.size();
	int edgesize = 0;
	for(int i : vec){
		edgesize += G[i].size();
	}
	return nodesize + nodesize == edgesize;
}

bool proc(){
	Flag.assign(N + 1, 0);
	for(int i=1;i<=N;++i){
		if(Flag[i]) continue;
		auto b = proc(i);
		if(!b) return false;
	}
	return true;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	// int nofkase; scanf("%d", &nofkase);
    // int nofkase = getInt();
    N = getInt(); M = getInt();
	G.assign(N + 1, vi());
	for(int a,b,i=0;i<M;++i){
        a = getInt(); b = getInt();
		G[a].push_back(b);
		G[b].push_back(a);
	}
	puts(proc()?"Yes":"No");
    return 0; 
}