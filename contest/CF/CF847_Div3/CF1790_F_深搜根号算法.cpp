/**
 * 给一个树，初始有一个节点是黑的，其余全白
 * 然后再给N-1个点的顺序，按此顺序依次将点涂黑
 * 每一次涂黑以后，问此时树上最近的黑点对的距离是多少
 * 显然这个答案是不减的，因此弄一个全局变量来回答。
 * Di记录i点到某个黑点的最近距离。对每次涂黑的点u，令D[u]=0，并开始深搜
 * 对每个v，D[v]是距离以前黑点的最近距离，D[u] + 1是新黑点的距离
 * 因此D[v] + D[u] + 1就是经过v的最近黑点对的距离，可以与全局变量比较并更新答案
 * 有两个剪枝。如果D[v] <= D[u] + 1就不要搜了，这说明新黑点距离v点不是最近的，并且v后面的点也没有必要搜索
 * 如果D[v] >= Ans 也不用搜，因为以后就要有答案也不会是v后面的黑点与当前黑点的贡献，因此v后面的点针对当前黑点的D也没有必要再计算。
 * 前根号N个操作就能令Ans降到根号N级别。对于后续操作，均摊搜索的次数也是根号N。因此最后是O(Nsqrt(N))。
 * 1900ms。这是标程的解法。AC列表中发现一个NlogN的做法，只需109ms。似乎也不是NlogN。
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
int const SIZE = 33;
#else
int const SIZE = 1E6+10;
#endif

using llt = long long;
using vll = vector<llt>;
using vi = vector<int>;
using vvi = vector<vi>;

int N, Root;
vvi G;
vi Order;
vi D;
int Ans;

void dfs(int u, int p){
    for(int v : G[u]){
        if(v == p) continue;
        D[v] = D[u] + 1;
        dfs(v, u);
    }
    return;
}

int proc(int node){
    function<void(int, int)> __dfs = [&__dfs](int u, int p){
        if(D[u] >= Ans) return;
        for(int v : G[u]){
            if(v == p) continue;
            auto tmp = D[v] + D[u] + 1;
            if(Ans > tmp){
                Ans = tmp;
            }
            if(D[v] > D[u] + 1){
                D[v] = D[u] + 1;
                __dfs(v, u);
            }
        }
        return;
    };
    D[node] = 0;
    __dfs(node, 0);
    return Ans;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int nofkase = getInt();
    while(nofkase--){
        N = getInt(); Root = getInt();
        G.assign(N + 1, vi());
        Order.assign(N - 1, 0);
        for(int & i : Order) i = getInt();
        for(int a,b,i=1;i<N;++i){
            a = getInt(); b = getInt();
            G[a].push_back(b);
            G[b].push_back(a);
        }
        D.assign(N + 1, 0);
        dfs(Root, 0);
        Ans = 2000000000;
        for(int i : Order){
            printf("%d ", proc(i));
        }
        printf("\n");
    }
    return 0;
}