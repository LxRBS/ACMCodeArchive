/**
 * 给一个树，初始有一个节点是黑的，其余全白
 * 然后再给N-1个点的顺序，按此顺序依次将点涂黑
 * 每一次涂黑以后，问此时树上最近的黑点对的距离是多少
 * 首先将第一个节点作为树根搜一遍，得到每个节点的父节点，以及初始深度Di
 * 搜索时，只向上搜索，这样每次最多搜索一条树链。
 * 对当前黑点u，首先令d=0，每向上一步，令d++。
 * 对路过的每一个祖先v，根据d + D[v]更新答案
 * 再根据d更新D[v]，这样D[v]始终保存v所在的某条树链上的最近的黑点距离
 * Dv不一定要保存距离v最近的黑点距离，只需保存树链信息即可。
 * 因为对每一个新点，均会向上搜索。假设距离v最近的黑点不是树链上的点，而是v的某个兄弟子树节点
 * 则在搜索过程中一定会经过v与最近黑点的最近公共祖先，那个节点上一定保存了这个兄弟黑点的信息（如果该信息是有用的）
 * 同样有一个剪枝，当d >= Ans时，可以不再向上搜索了。因为这个信息不会再对路过此节点的别的兄弟的搜索产生新答案。
 * 每次搜索只搜一条树链，复杂度是多少？
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
vi Father;
int Ans;

void dfs(int u, int p){
    Father[u] = p;
    for(int v : G[u]){
        if(v == p) continue;
        D[v] = D[u] + 1;
        dfs(v, u);
    }
    return;
}

int proc(int node){
    if(1 == Ans) return 1;
    int d = 0;
    while(d < Ans){
        Ans = min(Ans, d + D[node]);
        D[node] = min(D[node], d);
        ++d;
        node = Father[node];
    }
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
        Father.assign(N + 1, 0);
        dfs(Root, 0);
        Ans = 2000000000;
        for(int i : Order){
            printf("%d ", proc(i));
        }
        printf("\n");
    }
    return 0;
}