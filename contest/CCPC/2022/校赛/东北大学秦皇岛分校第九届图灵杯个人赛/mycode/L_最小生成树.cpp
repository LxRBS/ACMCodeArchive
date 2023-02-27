/**
 * 三维空间N个点，问全连通用的最短线路长度是多少。
 * 最小生成树，N在2000
 * 因此边的数量是O(N^2), Kruskal算法O(N^2log(N^2))
 * 也可以用Prim算法，O(N^2)
 */
#include <bits/stdc++.h>
using namespace std;

char *__abc147, *__xyz258, __ma369[100000];
#define __hv007() ((__abc147==__xyz258) && (__xyz258=(__abc147=__ma369)+fread(__ma369,1,100000,stdin),__abc147==__xyz258) ? EOF : *__abc147++)
 
using llt = long long; 
llt getInt(){
	int sgn = 1;
	char ch = __hv007();
	while( ch != '-' && ( ch < '0' || ch > '9' ) ) ch = __hv007();
	if ( '-' == ch ) {sgn = 0;ch=__hv007();}
 
	llt ret = (llt)(ch-'0');
	while( '0' <= (ch=__hv007()) && ch <= '9' ) ret = ret * 10LL + (llt)(ch-'0');
	return sgn ? ret : -ret;
}



#ifndef ONLINE_JUDGE
int const SIZE = 21;
#else
int const SIZE = 2e5+5;
#endif


using vi = vector<int>;
using vll =vector<llt>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vpii = vector<pii>;

llt const MOD = 998244353LL;

using t3t = tuple<llt, llt, llt>;
using vt3t = vector<t3t>;

int N;
vt3t P;
vector<vll> A;
vt3t B;

inline llt dist2(int idx, int jdx){
	llt x = get<0>(P[idx]) - get<0>(P[jdx]);
	llt y = get<1>(P[idx]) - get<1>(P[jdx]);
	llt z = get<2>(P[idx]) - get<2>(P[jdx]);
	return x * x + y * y + z * z;
}

vi Father;
void init(int n){
	Father.assign(n + 1, 0);
	for(int i=1;i<=n;++i) Father[i] = i;
}
int find(int x){
	return x == Father[x] ? x : Father[x] = find(Father[x]);
}
void unite(int x, int y){
	Father[find(y)] = find(x);
}

llt proc(){
    sort(B.begin(), B.end()); 
	init(N);

    int n = N - 1;
	llt ans = 0;
	for(const auto & p : B){
		int u = get<1>(p), v = get<2>(p);
		if(find(u) == find(v)) continue;
		
		unite(u, v);
		ans += ceil(sqrt(get<0>(p)));
		if(0 == --n) break;
	}
	return ans;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	// int nofkase; cin >> nofkase;
    N = getInt();
	P.assign(N, {});
	A.assign(N, vll(N, 0LL));
	B.reserve(N * N / 2 + 10);
	for(int x,y,z,i=0;i<N;++i){
        x = getInt(); y = getInt(); z = getInt();
		P[i] = {x, y, z};
		for(int j=0;j<i;++j){
			B.push_back({A[i][j] = A[j][i] = dist2(i, j), i, j});
		}
	}
	cout << proc() << endl;
    return 0; 
}