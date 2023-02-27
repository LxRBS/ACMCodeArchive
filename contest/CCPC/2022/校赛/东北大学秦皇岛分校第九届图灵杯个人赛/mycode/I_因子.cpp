/**
 * 给定一个数组A，可以选择一个区间[L, R]，使得AL减一，AR加一
 * 然后求出[1, N]的gcd。问任意操作，不同的gcd总数是多少
 * 显然有 gcd = k * SIGMA{A[1..N]} 说明gcd是总和的因子
 * 而操作是不改变总和的，因此直接求一个因子即可。
 * O(sqrt(500*1E6))
 */
#include <bits/stdc++.h>
using namespace std;

#include <bits/extc++.h>
using namespace __gnu_pbds;

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
int const SIZE = 2e5+5;
#endif

using llt = long long;
using vi = vector<int>;
using vll =vector<llt>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vpii = vector<pii>;

llt const MOD = 998244353LL;

int N;
vi A;

int proc(){
	int s = 0;
	for(int i : A) s += i;
	int ans = 0;
	for(llt i=1;i*i<=s;++i){
        if(0 == s % i){
			ans += 2;
			if(i * i == s) --ans;
		}
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
    A.assign(N, 0);
	for(int & i : A) i = getInt();
	cout << proc() << endl;
    return 0; 
}