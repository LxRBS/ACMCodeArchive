/**
 * 给定一棵树，节点染有黑白两色，问有多少个子树是平衡的，即
 * 黑白两色节点数量相等。
 * 令Di为i子树黑白数量之差，则数一数Di等于零的数量即可
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

char getChar(){
    char ch = __hv007();
    while(ch != 'W' && ch != 'B') ch = __hv007();
    return ch;
}

#ifndef ONLINE_JUDGE
int const SIZE = 14;
#else
int const SIZE = 4E3+13;
#endif

using vi = vector<int>;

int N;
vi G[SIZE];
char A[SIZE];
int D[SIZE];
int Ans;

void dfs(int u){
    D[u] = 'W' == A[u] ? 1 : -1;
    for(int v : G[u]){
        dfs(v);
        D[u] += D[v];
    }
    if(0 == D[u]) ++Ans;
}

int proc(){
    Ans = 0;
    dfs(1); 
    return Ans;    
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    int nofkase = getInt();
    while(nofkase--){
        N = getInt(); 
        for(int i=1;i<=N;++i) G[i].clear();
        for(int i=2;i<=N;++i) G[getInt()].push_back(i);
        for(int i=1;i<=N;++i) A[i] = getChar();
        printf("%d\n", proc());
    }
    return 0;
}

