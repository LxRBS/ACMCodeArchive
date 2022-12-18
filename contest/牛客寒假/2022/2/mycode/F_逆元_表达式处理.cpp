/**
 * 给一个只有加乘的表达式，再给定Q次操作
 * 每次操作把表达式的第x个数永久改为y，问每次修改后的表达式的值是多少
 * 预处理出所有的Term即可，如果是加数，则一个数是一个Term，如果是乘法，则乘法结果是一个Term
 * 然后求出表达式的初始值。然后根据每次操作的变化求值即可。
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
int const SIZE = 23;
#else
int const SIZE = 2E5+10;
#endif

using llt = long long; 
using vi = vector<int>;
using si = set<int>;
using vvi = vector<vi>;
using msi = map<int, si>;
using pii = pair<int, int>;
using vpii = vector<pii>;

llt const MOD = 1000000007LL;

llt exEuclid(llt a,llt b,llt&x,llt&y){
    llt x0 = 1, y0 = 0;
    llt x1 = 0, y1 = 1;
    x = 0; y = 1;
    llt r = a % b;
    llt q = ( a - r ) / b;
    while( r ){
        x = x0 - q * x1;
        y = y0 - q * y1;
        x0 = x1; y0 = y1;
        x1 = x; y1 = y;
        a = b; b = r; r = a % b;
        q = ( a - r ) / b;
    }
    return b;
}

inline llt inv(llt a,llt p){
    llt x,y;
    llt r = exEuclid(a,p,x,y);
    if ( r != 1 ) return 0;
    x = x % p;
    if ( x < 0 ) x += p;
    return x;
}

int N, Q;
string S;
vector<llt> Term;
vi Pos;
vi A;
llt Ans;

void proc(){
	int x;
    llt y;
	cin >> x >> y;
    int z = Pos[--x];
    
	llt beishu = Term[z] * inv(A[x], MOD) % MOD;
    llt delta = beishu * ((y - A[x]) % MOD + MOD) % MOD;
	Term[z] = beishu * (A[x] = y) % MOD;
	cout << ((((Ans += delta) %= MOD) += MOD) %= MOD) << endl;
	return;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cin >> N >> Q >> S;
	Pos.assign(N, -1);
	llt v; cin >> v;
	Term.push_back(v);
	A.push_back(v);
	Pos[0] = 0;
    for(int i=0;i<N-1;++i){
		cin >> v;
		A.push_back(v);
		if(S[i] == '+') Term.push_back(v);
		else (Term.back() *= v) %= MOD;
		Pos[i+1] = Term.size() - 1;
	}

	Ans = 0;
	for(auto v : Term) (Ans += v) %= MOD;
    
	for(int i=0;i<Q;++i){
		proc();
	}
    return 0;
}
