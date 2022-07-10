/**
 * N个节点的树，每个节点有一个ai，表示该节点可以在ai时间完成作业
 * 还有一种方法可以完成作业，i可以去j，等j完成作业后，可以抄j的作业并返回，i必须返回家才认为作业完成
 * 此时i完成作业的时间就是j的时间加上i从j返回家的时间
 * 有三类操作：
 * 1. 修改i的ai
 * 2. 修改i、j家的距离
 * 3. 问每个人最早完成作业的时间，其中3操作不超过200个
 * N在1E5 
 * 考虑树型DP，设Di为如果只考虑儿子和自身所需的最短时间，显然
 * Di = min(Ai, min{Dj+Wij})，其中j是i的儿子
 * 现在只需要考虑父节点即可。本来是考虑需要建立第二小DP，因为儿子和父亲不能互相计算
 * 但这里其实不需要，考虑p的某个儿子i，根据Dp的生成规则，必然有
 * Dp >= Di + Wip
 * 所以现在如果满足 Dp + Wip > Di，可以肯定p的答案不是由儿子i计算的，于是可以反过来用p的数值来计算i
 * 因此只需要以1为根，搜两遍，做两边树型DP即可。
 * 第一遍搜完，D1肯定是正确答案，所以直接搜第二遍更新即可。
 * 题解说换根，其实不能换根。
 * CF上可以直接过，牛客上卡了一点，初始化时需要使用copy，而不能逐个赋值。
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
int const SIZE = 11;
#else
int const SIZE = 1E5+7;
#endif

using llt = long long;
using pii = pair<int, int>;
using vpii = vector<pii>;


vpii G[SIZE];
int N, Q;
int A[SIZE];
llt W[SIZE];

llt B[SIZE];

/// 此时B保存的是抄儿子作业的最小值
void dfs(int u, int p){
    // B[u] = A[u]; /// 牛客上用这个初始化就会T
    for(const pii & e: G[u]){
        if(e.first == p) continue;
        
        dfs(e.first, u);

        B[u] = min(B[u], B[e.first] + W[e.second]);
    }
}

/// B保存答案
void dfs2(int u, int p){
    for(const pii & e: G[u]){
        if(e.first == p) continue;
        /// 说明u是从别的地方弄来的最小值
        B[e.first] = min(B[e.first], B[u] + W[e.second]);
        dfs2(e.first, u);
    }
}

llt proc(){
    copy(A+1, A+N+1, B+1);
    dfs(1, 0);
    dfs2(1, 0);
    llt ans = 0;
    for(int i=1;i<=N;++i) ans ^= B[i];
    return ans;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    N = getInt(); Q = getInt();
    for(int i=1;i<=N;++i) A[i] = getInt();
    for(int a,b,w,i=1;i<N;++i){
        a = getInt(); b = getInt(); W[i] = getInt();
        G[a].emplace_back(b, i);
        G[b].emplace_back(a, i);
    } 

    for(int op, q=1;q<=Q;++q){
        if(1 == (op=getInt())){
            int i = getInt();
            A[i] = getInt();
        }else if(2 == op){
            int i = getInt();
            W[i] = getInt();
        }else{
            cout << proc() << endl;
        }
    }
    return 0;
}