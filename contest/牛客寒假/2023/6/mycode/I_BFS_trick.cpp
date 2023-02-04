/**
 * 给一个无向图，从1走到N
 * 每一次可以摧毁一条边并把当前要走的边的权值改为1
 * 问最小代价是多少
 * 显然要走的边不能摧毁，但是走过的边和其他无关的边都可以摧毁
 * 因此唯一的问题就是第一条边是否能够找出多余的边摧毁并改为1
 * 不用管权值，就跑一个层次图看最少几条边到N。假设是k
 * 如果有多余的边就是k，否则就是第一条边的权值加k减一
 * 当然也有可能不连通的情况
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
int const SIZE = 1E6+10;
#endif

using llt = long long;
using vi = vector<int>;
using pii = pair<int, int>;
using vi = vector<int>;
using vvi = vector<vi>;
using vpii = vector<pii>;
using t3t = tuple<int, int, int>;
using EdgeListTy = vector<t3t>;

int N, M;
vvi G;
EdgeListTy Edges;

llt proc(){
    if(1 == N) return 0;

    vi pre(N + 1, -1);
    queue<int> q;
    q.push(1);

    int k = 0;
    int sz = 0;
    while(sz = q.size()){
        ++k;
        while(sz--){
            auto h = q.front(); q.pop();
            for(auto i : G[h]){
                const auto & e = Edges[i];
                auto one = get<0>(e);
                auto two = get<1>(e);
                auto v = one ^ two ^ h;                
                if(-1 != pre[v] || 1 == v) continue;

                pre[v] = i;
                if(v == N) goto L;
                q.push(v);
            }
        }
        continue;
        L: break;
    }
    if(-1 == pre[N]) return -1;
    if(k < M) return k;
    return get<2>(Edges[G[1][0]]) + k - 1;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    // ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    N = getInt();
    M = getInt();
    G.assign(N + 1, {});
    for(int a,b,w,i=0;i<M;++i){
        a = getInt();
        b = getInt();
        w = getInt();        
        G[a].emplace_back(Edges.size());
        G[b].emplace_back(Edges.size());
        Edges.emplace_back(a, b, w);
    }
    printf("%lld\n", proc());
    return 0;
}