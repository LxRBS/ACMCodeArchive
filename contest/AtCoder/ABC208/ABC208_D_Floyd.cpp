/**
 * 给一个有向图，定义f(i, j, k)是从i到j的路径，且处ij以外，中间的节点编号最大不超过k，这样的路径的最小权值
 * 求 SIGMAf(i, j, k) 对ijk全部从1到N
 * 标准的Floyd， N在400， 空间都不用优化
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
int const SIZE = 810;
#endif

using llt = long long;
using pii = pair<int, int>;
using vpii = vector<pii>;
using vi = vector<int>;
using vvi = vector<vi>;


int const INF = 1000000000;


int N, M;
vvi G;
vector<vvi> D;

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    // ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    N = getInt(); M = getInt();
    G.assign(N + 1, vi(N + 1, INF));
    for(int a,b,c,i=0;i<M;++i){
        a = getInt(); b = getInt(); c = getInt();
        G[a][b] = c;
    }

    D.assign(N + 1, vvi(N + 1, vi(N + 1, INF)));
    D[0].swap(G);
    for(int i=1;i<=N;++i) D[0][i][i] = 0;

    llt ans = 0;
    auto f = [&ans](int v){if(v < INF) ans += v;};

    for(int k=1;k<=N;++k){
        auto * dk = D[k].data();
        auto * dkp = D[k-1].data();
        for(int i=1;i<=N;++i){
            auto * dki = (dk +i)->data();
            auto * dkpi = (dkp + i)->data();
            for(int j=1;j<=N;++j){
                f(*(dki + j) = min(*(dkpi + j), *(dkpi + k) + (*(dkp + k))[j]));                
            }
        }
    }
    cout << ans << endl;
    return 0;
}