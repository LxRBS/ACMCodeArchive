/**
 * 给定一棵树，N个节点，再给定N个权值，每次为其中一个节点赋权，并将该节点子树的现有权值累加
 * 求累加值最大是多少
 * 简单推理就能发现，必须从树叶往上放，且尽可能把大数放在下面
 * 再验算一下即可发现，对一组权值而言，相同深度的节点，如何放其实不影响答案
 * 最后，单个权值对答案的影响其实就是本身乘以深度，深度从1开始。
 * 因此将权值从大到小排序，将深度从大到小排序，相乘相加即可。
 */
#include <bits/stdc++.h>
using namespace std;
 
char *__abc147, *__xyz258, __ma369[1000000];
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
int const SIZE = 110;
#endif

using llt = long long;
using vi = vector<int>;
using vvi = vector<vi>;

int N;
vvi G;
vi W;
vi Depth;

void dfs(int u, int depth){
    Depth[u - 1] = depth;
    for(int v : G[u]){
        dfs(v, depth + 1);
    }
}

llt proc(){
    Depth.assign(N, 0);
    dfs(1, 1);
    sort(W.begin(), W.end(), greater<int>());
    sort(Depth.begin(), Depth.end(), greater<int>());
    llt ans = 0;
    for(int i=0;i<N;++i){
        ans += (llt)Depth[i] * (llt)W[i]; 
    }
    return ans;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    G.assign((N = getInt()) + 1, vi());
    for(int i=2;i<=N;++i){
        G[getInt()].push_back(i);
    }
    W.assign(N, 0);
    for(int & i : W) i = getInt();
    printf("%lld\n", proc());
    return 0;
}


