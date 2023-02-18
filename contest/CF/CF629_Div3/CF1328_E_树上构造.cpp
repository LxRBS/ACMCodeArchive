/**
 * 给一个树，q个询问，每次询问给若干个点，问：
 * 能否找到从根出发的一条路径，使得所有点要么在路径上，要么距离路径为1
 * 问题实际上等价于每个点要么在路径上要么它的父亲在路径上
 * 考虑深度最深的点t，从1到t必然是答案，只需验证这条路径即可
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
int const SIZE = 21;
#else 
int const SIZE = 200100;
#endif

#define fi first
#define se second
typedef pair<int, int> pii;
typedef vector<int> vi;

int N, M, Q;
vi G[SIZE];
pii Index[SIZE];
int Depth[SIZE];
int Parent[SIZE];
int TimeStamp = 0;

void dfs(int u, int parent){
    Parent[u] = parent;
    Depth[u] = Depth[parent] + 1;
    Index[u].fi = ++TimeStamp;
    for(auto v: G[u]){
        if(parent == v) continue;
        dfs(v, u);
    } 
    Index[u].se = ++TimeStamp;
}

inline bool isAncestor(int anc, int u){
    return Index[anc].fi <= Index[u].fi && Index[u].se <= Index[anc].se;
}

vi Question;

bool proc(){
    Question.clear();
    int t = 0, a, n = getInt();
    while(n--){
        Question.push_back(a = getInt());
        if(Depth[a] > Depth[t]) t = a;
    }

    for(auto &i: Question){
        if(i == t) continue;
        if(i!=1&&!isAncestor(Parent[i], t)) return false;
    }
    return true;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    N = getInt();
    M = getInt();
    for(int a,b,i=1;i<N;++i){
        a = getInt();
        b = getInt();
        G[a].push_back(b);
        G[b].push_back(a);
    }
    dfs(1, 0);
    for(int n,a,i=1;i<=M;++i){
        puts(proc() ? "YES" : "NO");
    }
	return 0;
}