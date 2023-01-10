/**
 * 给定无向图，问从1开始的简单路径一共有多少条，假设答案为K，输出min(K, 1E6)
 * 由于最多到1E6，直接DFS即可 * 
 */
#include <bits/stdc++.h>
using namespace std;
 
char *__abc147, *__xyz258, __ma369[1000000];
#define __hv007() ((__abc147==__xyz258) && (__xyz258=(__abc147=__ma369)+fread(__ma369,1,100000,stdin),__abc147==__xyz258) ? EOF : *__abc147++)

using llt = long long;
llt getInt(){
	int sgn = 1;
	char ch = __hv007();
	while( ch != '-' && ( ch < '0' || ch > '9' ) ) ch = __hv007();
	if ( '-' == ch ) {sgn = 0;ch=__hv007();}
 
	llt ret = (llt)(ch-'0');
	while( '0' <= (ch=__hv007()) && ch <= '9' ) ret = ret * 10 + (llt)(ch-'0');
	return sgn ? ret : -ret;
}
 
#ifndef ONLINE_JUDGE
int const SIZE = 23;
#else
int const SIZE = 3500000;
#endif

using vi = vector<int>;
using vvi = vector<vi>;

int N, M;
vvi G;

int Ans = 0;
vi Flag;

void dfs(int u){
    for(int v : G[u]){
		if(Flag[v]) continue;
		if(++Ans >= 1000000) return;

		Flag[v] = 1;
		dfs(v);
		Flag[v] = 0;
		if(Ans >= 1000000) return;
	}
}

int proc(){
    Flag.assign(N+1, 0);
	Ans = Flag[1] = 1;
	dfs(1);
	return Ans;    
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    G.assign((N=getInt())+1, vi());
	M = getInt();
	for(int a,b,i=0;i<M;++i){
        a = getInt(); b = getInt();
		G[a].push_back(b);
		G[b].push_back(a);
	}
	printf("%d\n", proc());
    return 0;
}


