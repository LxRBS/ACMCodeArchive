/**
 * 戈丁一个图，问这个图是否恰好是一条路径的形状
 * 首先看边数，必须是N-1。然后统计度数，必须是两个1度和若干个2度
 * 除此之外如果只有一个连通块就Yes，否则就No。
 * 可以用并查集，也可以从度数为1的点做一个搜索。
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
int const SIZE = 13;
#else
int const SIZE = 2E5+10;
#endif

using llt = long long;
using vi = vector<int>;
using si = set<int>;
using vvi = vector<vi>;
using msi = map<int, si>;

int N;
int M;
vvi G;
vi Deg;

bool proc(){
    if(M != N - 1) return false;

	int u = 0;
	int c = 0;
	for(int i=1;i<=N;++i){
		if(1 == Deg[i]) u = i, ++c;
		else if(2 == Deg[i]) ;
        else return false;
	}
	if(c != 2) return false;

    vi flag(N + 1, 0);
    queue<int> q;
	q.push(u); flag[u] = 1;
	while(!q.empty()){
		auto h = q.front(); q.pop();
		for(auto v : G[h]){
			if(flag[v]) continue;
			flag[v] = 1;
			q.push(v);
		}
	}
	for(int i=1;i<=N;++i)if(0==flag[i])return false;
	return true;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    // ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    N = getInt(); M = getInt();
	G.assign(N+1, vi());
	Deg.assign(N+1, 0);
	for(int a,b,i=0;i<M;++i){
        a = getInt(); b = getInt();
		G[a].push_back(b);
		G[b].push_back(a);
		++Deg[a]; ++Deg[b];
	}
	puts(proc()?"Yes":"No");
    return 0;
}