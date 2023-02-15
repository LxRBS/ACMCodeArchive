/**
 * 给定10个允许的步数，再给定若干个不准走的点。问能否从0走到X。
 * DP即可。
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

using llt = long long;
using vi = vector<int>;
using vll =vector<llt>;
using edge_t = tuple<int, int, int, int>;
using ve = vector<edge_t>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vpii = vector<pii>;

llt const MOD = 1E9+7LL;

int N, M;
vi A;
vi B;
int X;
vi D;

int dfs(int pos){
	if(D[pos]) return D[pos];
	if(B[pos]) return D[pos] = -1;
	for(int i=0;i<N;++i){
		if(pos >= A[i]){
			auto tmp = dfs(pos - A[i]);
			if(1 == tmp) return D[pos] = 1; 			
		}
	}
	return D[pos] = -1;
}

bool proc(){
	D.assign(X + 1, 0);
	D[0] = 1;
    return dfs(X) == 1;    
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    // ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    N = getInt();
	A.assign(N, 0);
	for(int & i : A) i = getInt();
	M = getInt();
    B.assign(100000+1, 0);
	for(int i=0;i<M;++i) B[getInt()] = 1;
    X = getInt();
    puts(proc() ? "Yes" : "No");
	return 0; 
}