/**
 * 一棵树，每条边有权值。给定A和B两个点，要求从A走到B。
 * 每走过一条边，将手中的权值去异或边权。初始手中的权值为0，要求走到B恰好也为0
 * 问是是否可行。
 * 除此之外，还有一次teleport的机会，即从当前点瞬移到除B以外的任意点，手中权值不变
 * 从B做一次搜索，计算出Di，即从B到i点的权值。
 * 再从A出发做一次搜索，如果能够搜出某个值在Di中是存在的，则可行。
 * 深搜与广搜均可。
 * 因为有专门针对默认哈希做的hack，所以unordered_set会超时
 * 除非使用随机的自制哈希。但时间仍然比set慢 
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
int const SIZE = 1E5+13;
#endif

using vi = vector<int>;
using si = set<int>;

struct edge_t{
    int from;
    int to;
    int w;
}Edge[SIZE];

int N, A, B;
vi G[SIZE];

int DB[SIZE];
int DA[SIZE];
si Set;

void dfsB(int u, int p){
    for(auto e : G[u]){
        const auto & edge = Edge[e];
        int v = u ^ edge.from ^ edge.to;
        if(v == p) continue;
        Set.insert(DB[v] = DB[u] ^ edge.w);
        dfsB(v, u);
    }
}

bool dfsA(int u, int p){
    if(Set.count(DA[u])) return true;

    for(auto e : G[u]){
        const auto & edge = Edge[e];
        int v = u ^ edge.from ^ edge.to;
        if(v == p) continue;
        if(v == B) continue;
        DA[v] = DA[u] ^ edge.w;
        bool b = dfsA(v, u);
        if(b) return true;
    }
    return false;
}

bool proc(){
    Set.clear();

    DB[B] = 0;
    dfsB(B, 0);

    DA[A] = 0;
    bool b = dfsA(A, 0);
    return b;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r" ,stdin);
#endif
    int nofkase = getInt();
    while(nofkase--){
        N = getInt();
        A = getInt();
        B = getInt();
        for(int i=1;i<=N;++i) G[i].clear();
        for(int u,v,w,i=1;i<N;++i){
            Edge[i].from = u = getInt(); 
            Edge[i].to = v = getInt();
            Edge[i].w = getInt();
            G[u].push_back(i);
            G[v].push_back(i);
        }
        puts(proc()?"YES":"NO");
    }
    return 0;
}
