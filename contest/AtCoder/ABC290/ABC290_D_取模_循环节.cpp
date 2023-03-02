/**
 * 给定N、D、K，表示一共有[0, N-1]的N个格子
 * 初始令标记第0格，然后重复N-1次
 * 令上一个标记的格子下标为A，则令 x = (A + D) % N
 * 从x开始加1，碰到的第一个未标记的格子，标记之。
 * 问第K次标记的格子是哪一个
 * 考虑加1之前的轮次，序列为 0, D, 2D, ..., uD
 * 如果要加1，则必然有 uD % N = vD % N，因此 (u - v)D是N的倍数
 * u显然应该是第一个满足条件的，因此应该对D和N取gcd
 * 令 D = dg, N = ng, 则 u - v = n, 所以循环节长度就是 N/g
 * 每过一个循环节就要加1，因此用 K/(N/g)，看有多少偏移量，最后再看再该循环节中还要往前走几步
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
	while( ch != 'o' && ch != 'x' ) ch = __hv007();
	return ch;
}

#ifndef ONLINE_JUDGE
int const SIZE = 21;
#else
int const SIZE = 2e5+5;
#endif

using llt = long long;
using vi = vector<int>;
using vll =vector<llt>;
using edge_t = tuple<int, int, int, int>;
using ve = vector<edge_t>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vpii = vector<pii>;

llt const MOD = 998244353LL;

llt N, D, K;

llt proc(){
    if(1 == D) return K - 1;
	if(0 == D % N) return K - 1;
	D = D % N;	
	auto g = __gcd(D, N);
	if(1 == g){
		return (K - 1) * D % N;
	}
    
	K -= 1;
	auto jie = N / g;
	auto c = K  / jie;
	auto left = K % jie;
	auto ans = (left * D + c) % N;
	return ans;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int nofkase = getInt();
    while(nofkase--){
        N = getInt();
		D = getInt();
		K = getInt();
		printf("%lld\n", proc());
	}
	return 0; 
}