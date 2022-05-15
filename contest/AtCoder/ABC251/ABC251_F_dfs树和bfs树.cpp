/**
 * 给定一个图，求两种支撑树A和B。
 * A：每一条非树边(u,v)，必然为祖孙关系
 * B：每一条非树边(u,v)，必然互不为祖先
 * A其实就是dfs树，B就是bfs树
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
int const SIZE = 2e5+5;
#endif
 
using llt = long long;
using Real = long double;
using vi = vector<int>;

int N, M;
vi G[SIZE]; 

bool F[SIZE];
void proc1(){
    function<void(int,int)> dfs = [&](int u, int p){
        for(int i: G[u]){
			if(F[i]) continue;
			F[i] = 1;
			printf("%d %d\n", u, i);
			dfs(i, u);
		}
	};
	F[1] = 1;
	dfs(1, 0);
}

void proc2(){
	memset(F, 0, sizeof(F));
    queue<int> q;
	q.push(1); F[1] = 1;
	while(!q.empty()){
		int h = q.front(); q.pop();
		for(int i: G[h]){
			if(F[i]) continue;
			F[i] = 1;
			q.push(i);
			printf("%d %d\n", h, i);
		}
	}
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    N = getInt(); M = getInt();
	for(int a,b,i=0;i<M;++i){
        a = getInt(); b = getInt();
		G[a].push_back(b);
		G[b].push_back(a);
	}
	proc1(); proc2();
    return 0;
}
