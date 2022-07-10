/**
 * 无向图，均为普通边，对于从i到j的路径，定义难度=路径最大点权乘以最大边权
 * 定义ij点对的难度为ij之间所有路径的最小难度。
 * 对所有点对输出难度。N在500。
 * 比较明显的Floyd，不过需要变些形
 * 首先不能分别维护点权、边权和答案，因为点权和边权是相互匹配的 
 * 所以事先按点权排序，然后最外层循环从小到大遍历，
 * 这样可以保证每次加入的新路径的最大点权能够现算
 * 于是只需维护边权和答案。
 * 其中边权维护的是所有路径的最大边权的最小值。
 * 再加入两个剪枝即可，不加剪枝会超时。
 * 还有一个优化，因为是无向图，Dij=Dji，直接更新以后可能常数会更快
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
int const SIZE = 17;
#else
int const SIZE = 505;
#endif

using llt = long long int;
using Real = long double;
using vi = vector<llt>;
using vvi = vector<vi>;
using pii = pair<llt, llt>;
using vpii = vector<pii>;

template<>struct std::hash<pii>{
	inline size_t operator()(const pii&p)const{
		return p.first * 1331 + p.second;
	}
};

using lltarr = llt [SIZE][SIZE];

int N, M;
pii W[SIZE];
lltarr G, A, B, D;

/// DP的更新
void update(llt & a, llt b){
    if(-1 == a) a = b;
    else if(b != -1) a = min(a, b);
}

void proc(){
    /// 初始化，初始路径最大边权就是边本身
    for(int i=1;i<=N;++i) copy(G[i]+1, G[i]+N+1, A[i]+1);
    /// 初始路径最大点权，有边的话就是两点之一，无边的话就是-1
    for(int i=1;i<=N;++i){
        for(int j=1;j<=N;++j){
            if(-1 == G[i][j]) D[i][j] = -1;
            else D[i][j] = max(W[i].first, W[j].first) * G[i][j];
        }
    }

    sort(W+1, W+N+1);

    for(int i,j,k,_=1;_<=N;++_){
        llt wi, wj, wk;
        /// 相当于根据点权从小往大枚举点，这样可以精确定位路径的最大点权
        k = W[_].second;
        wk = W[_].first; 
        for(int __=1;__<=N;++__){
            i = W[__].second;
            wi = W[__].first;
            for(int ___=1;___<=N;++___){
                j = W[___].second;
                wj = W[___].first;
                
                /// 新路径不通则略过
                if(-1 == A[i][k] || -1 == A[k][j]) continue;

                /// i-k-j路径的最大点权肯定是三者中最大的
                llt dianquan = max(max(wi, wj), wk);
                /// i-k-j路径的最大边权显然是两段中较大的那个
                llt bianquan =  max(A[i][k], A[k][j]); 

                /// 如果新最大边权比原有最大边权还要大，可以直接忽略
                /// 因为点权是递增的，而所求为最小值
                /// 这两个continue都要有，否则会超时
                if(bianquan > A[i][j] && -1 != A[i][j]) continue;       
              
                /// 新路径的解
                llt ans = bianquan * dianquan;
                /// dp
                update(A[i][j], bianquan);
                update(D[i][j], ans);
            }
        }
    }
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    N = getInt(); M = getInt();
    for(int i=1;i<=N;++i) W[W[i].second = i].first = getInt();

    memset(G, -1, sizeof(G));
    for(int a,b,w,i=1;i<=M;++i){
        a = getInt(); b = getInt(); w = getInt();
        G[a][b] = G[b][a] = w;
    }
    for(int i=1;i<=N;++i){
        assert(-1 == G[i][i]);
        G[i][i] = 0;
    }

    proc();
    for(int i=1;i<=N;++i){
        printf("%lld", D[i][1]);
        for(int j=2;j<=N;++j) printf(" %lld", D[i][j]);
        puts("");
    }
    return 0;
}

