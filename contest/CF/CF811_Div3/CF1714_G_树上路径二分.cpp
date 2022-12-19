/**
 * 给一个树，以1为根。每条边有a/b两类权值
 * 对每一个节点v，令Av是从1到v路径上a类权值之和，Bv是b类权值之和
 * 要求在1到v的路径上找到一个点i，使得Av>=Bi，且1到i的距离最远，输出这个距离
 * 权值都是正的，因此B数组是递增的，二分即可。
 * 树上路径二分，深搜中维持一个深搜栈，在栈上二分即可。
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
using vll = vector<llt>;
using si = set<int>;
using vvi = vector<vi>;
using msi = map<int, si>;
using pii = pair<int, int>;
using vpii = vector<pii>;
using t3t = tuple<int, int, int>;

int N;
vi A, B;
vvi G;
vi Ans;
vll Stack;

void dfs(int u, int p, llt sum){
    for(int v : G[u]){
		if(v == p) continue;

        llt target = sum + A[v];
		Stack.push_back(Stack.back() + B[v]);
		int p = upper_bound(Stack.begin(), Stack.end(), target) - Stack.begin();
        Ans[v] = --p;
		dfs(v, u, target);
		Stack.pop_back();
	}
	return;
}

void proc(){
    Ans.assign(N+1, 0);
	Stack.clear();
	Stack.reserve(N+1);
	Stack.push_back(0);
	dfs(1, 0, 0);
	assert(1 == Stack.size());
	for(int i=2;i<=N;++i) printf("%d ", Ans[i]);
	printf("\n");
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    int nofkase = getInt();
	while(nofkase--){
	    A.assign((N=getInt())+1, 0);
		B.assign(N+1, 0);
		G.assign(N+1, vi());
		for(int p,a,b,i=2;i<=N;++i){
            p = getInt();
			A[i] = getInt();
			B[i] = getInt();
            G[i].push_back(p);
			G[p].push_back(i);
		}
		proc();
	}
    return 0;
}


