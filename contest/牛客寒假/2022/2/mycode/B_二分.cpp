/**
 *  N张攻击牌，M张回复牌，初始体力为1，第i个回合打出攻击则伤害为i且体力减1，打出回复则体力加1。
 *  有K个询问，每次询问是否能恰好造成伤害X。
 *  考虑使用了x张攻击牌M张回复牌的情况，，其中显然x<=M+1
 *  考虑牌型ABABAB......B，则其伤害为x^2
 *  再考虑牌型BB.....BAA..A，其伤害为 x * (M + 1 + M + x) / 2
 *  发现[x^2, x * (M + 1 + M + x) / 2]区间内的伤害都能达成
 *  因为每一种牌型都至少可以找到一个A将其往后移一格。
 *  这个区间显然是根据x单调的。于是二分。
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
	while( '0' <= (ch=__hv007()) && ch <= '9' ) ret = ret * 10 + (llt)(ch-'0');
	return sgn ? ret : -ret;
}
 
#ifndef ONLINE_JUDGE
int const SIZE = 23;
#else
int const SIZE = 2E5+10;
#endif


using vi = vector<int>;
using si = set<int>;
using vvi = vector<vi>;
using msi = map<int, si>;
using pii = pair<int, int>;
using vpii = vector<pii>;

llt N, M, K, X;
llt Limit;

bool proc(){
    llt left = 0, right = N, mid;
	do{
        mid = (left + right) >> 1;
		llt s = mid * mid;
		if(X < s) {
			right = mid -1; continue;
		}
		llt e = mid * (mid + 1 + M + M) / 2LL;
		if(X > e) {
			left = mid + 1; continue;
		}
		return true;
	}while(left <= right);
	return false;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    N = getInt(); M = getInt();
	K = getInt();
	if(N > M + 1) N = M + 1;
	Limit = N * (M + 1 + N + M) / 2LL;
	for(int i=0;i<K;++i){
		X = getInt();
		puts(proc() ? "YES" : "NO");
	}
    return 0;
}


