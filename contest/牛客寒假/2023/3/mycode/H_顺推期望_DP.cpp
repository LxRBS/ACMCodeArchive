/**
 * 初始字符串为空，每次等概率的3种操作之一：
 * 1 尾部添加 red
 * 2 尾部添加 edr
 * 3 将当前字符串重复10次
 * 问K次操作之后，字符串中red的数量期望是多少。
 * 由于有重复操作，显然字符串的开头与结尾对重复之后的red数量均有影响，因此一共有5种状态，状态4表示初态，即空字符串
 * 00 表示 red开头red结尾
 * 01 表示 red开头edr结尾
 * 10 表示 edr开头red结尾
 * 11 表示 edr开头edr结尾
 * 令 P[i][st] 表示第i轮过后恰好到达st状态的概率
 * 令 D[i][st] 表示第i轮过后能到st状态的red的期望
 * 考虑D[i][0]，显然由三部分贡献，首先考虑[i-1, 1]对[i, 0]的贡献
 * 令 D[i-1][1] = SIGMA{Xj * Pj, j表示所有在第i-1轮落在1的方案}
 * 则 该部分对D[i][0]的贡献为 SIGMA{(Xj + 1) * Pj * 1/3，此时j表示了所有第i-1轮落在1且第i轮落在0的方案}
 * 就等于 (SIGMA{Xj * Pj} + SIGMA{Pj}) * 1/3
 * 注意到前一部分就是 D[i-1][1]，而后一部分是所有到达[i-1, 1]的概率，就是P[i-1][1]
 * 因此这一部分的贡献就是 D[i-1][1] + P[i-1][1]
 * 再考虑 [i-1, 0]的贡献， D[i-1][0] = SIGMA{Xj * Pj}，于是对[i, 0]的贡献为
 * SIGMA{Xj * 10 * Pj} * 1/3 + SIGMA{(Xj + 1) * Pj} * 1/3 = (10D[i-1][0] + D[i-1][0] + P[i-1][0]) * 1/3
 * 最后考虑[i-1, 4]的贡献，这一部分比较简单，因为 D[i-1][4] = 0，所以这一部分贡献为 P[i-1][4] * 1/3
 * 综上 D[i][0] = (D[i-1][1] + P[i-1][1]) + (P[i-1][4]) + (10D[i-1][0] + D[i-1][0] + P[i-1][0]) * 1/3
 * 类似的可以推出其他状态的转移方程。
 * 注意这是顺推，因此比倒推要难一些。此题存在乘法，所以倒推更难。
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
int const SIZE = 26;
#else
int const SIZE = 2800;
#endif
 
using llt = long long;
using Real = long double;
using vi = vector<int>; 
using vll = vector<llt>;

llt const MOD = 1E9+7;

llt powerMod(llt a,llt n){
    llt ret = 1;
    a %= MOD;

    while( n ){
        if ( n & 1 ) ret = ret * a % MOD;
        n >>= 1;
        a = a * a % MOD;
    }
    return ret;
}
inline llt inv(llt a){return powerMod(a, MOD-2);}

struct mint{

llt value;
mint(llt v=0):value((v%MOD+MOD)%MOD){}

const mint operator + (const mint & r)const{return {(value+r.value)%MOD};}
const mint operator - (const mint & r)const{return {(value-r.value+MOD)%MOD};}
const mint operator * (const mint & r)const{return mint(value * r.value % MOD);}

const mint operator + (llt r)const{return *this + mint(r);}
const mint operator * (llt r)const{return *this * mint(r);}

const mint operator += (const mint & r){
	(value += r.value) %= MOD;
	return *this;
}

};

mint const ONE_THIRD = mint(powerMod(3LL, MOD - 2LL));


llt K;
/// 00 表示 red red
/// 01 表示 red edr
/// 10 表示 edr red
/// 11 表示 edr edr
vector<array<mint, 5>> P; // P[i][st] 表示恰好i次操作到达st的概率
vector<array<mint, 5>> D;

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    K = getInt();
	P.assign(K + 1, {});
	D.assign(K + 1, {});

    P[0][4] = 1;
	for(int i=1;i<=K;++i){
        P[i][4] = P[i-1][4] * ONE_THIRD;
		P[i][0] = (P[i-1][4] + P[i-1][0] * 2LL + P[i-1][1]) * ONE_THIRD;
        P[i][3] = (P[i-1][4] + P[i-1][3] * 2LL + P[i-1][2]) * ONE_THIRD;
		P[i][1] = (P[i-1][0] + P[i-1][1] * 2LL) * ONE_THIRD;
		P[i][2] = (P[i-1][3] + P[i-1][2] * 2LL) * ONE_THIRD;

		D[i][0] = (D[i-1][0] * 10LL + (D[i-1][0] + P[i-1][0]) + (D[i-1][1] + P[i-1][1]) + P[i-1][4]) * ONE_THIRD;
		D[i][3] = ((D[i-1][3] * 10LL + P[i-1][3] * 9) + (D[i-1][3] + P[i-1][3]) + (D[i-1][2])) * ONE_THIRD;
		D[i][1] = (D[i-1][1] * 10LL + (D[i-1][0]) + (D[i-1][1] + P[i-1][1])) * ONE_THIRD;
		D[i][2] = (D[i-1][2] * 10LL + (D[i-1][3] + P[i-1][3]) + (D[i-1][2] + P[i-1][2])) * ONE_THIRD;
	}

    auto ans = (D[K][0] + D[K][1] + D[K][2] + D[K][3]);
	cout << ans.value << endl;
    return 0;
}