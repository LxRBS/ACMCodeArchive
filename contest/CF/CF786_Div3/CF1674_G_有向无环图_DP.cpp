/**
 * 给定一个有向无环图，要求删掉一些边，满足如下三个条件：
 * 1 所有点的入度要么为0，要么比初始值小
 * 2 所有点的出度要么为0，要么比初始值小
 * 3 某个子图中任意两点u和v，要么u到v有路径，要么v到u有路径
 * 求这个最大的子图的定点数量
 * 由于原图是有向无环图，所以第3个条件实际上说明子图就是一条路径
 * 在此基础上，除了路径的两个端点，中间的点必须至少是两出度两入度的
 * 令Du为以u开头满足条件的路径长度，如果Out[u] <= 1, 则D[u] = 1
 * 否则 D[u] = max{D[v] + 1, v是u的后继且In[v]>1}
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
int const SIZE = 23;
#else
int const SIZE = 2E5+10;
#endif

using llt = long long; 
using vi = vector<int>;
using si = set<int>;
using vvi = vector<vi>;
using msi = map<int, si>;
using pii = pair<int, int>;
using vpii = vector<pii>;

vi InDeg, OutDeg;
vvi G;
int N, M;
vi D;

int dp(int u){
    if(D[u]) return D[u];
	if(OutDeg[u] <= 1) return D[u] = 1;

	int & ans = D[u];
	ans = 1; // 至少是1
	for(auto v : G[u]){
		if(InDeg[v] == 1) continue;
		ans = max(ans, dp(v) + 1);
	}
	return ans;
}

int proc(){
    D.assign(N+1, 0);
	int ans = 1;
	for(int i=1;i<=N;++i){
		ans = max(ans, dp(i));
	}
	return ans;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    G.assign((N=getInt())+1, vi());
	M = getInt();
	InDeg.assign(N+1, 0);
	OutDeg.assign(N+1, 0);
	for(int a,b,i=0;i<M;++i){
		a = getInt(); b = getInt();
		G[a].push_back(b);
		++OutDeg[a];
		++InDeg[b];
	}
	printf("%d\n", proc());
    return 0;
}
