/**
 * 初始字符串为空，每次等概率的3种操作之一：
 * 1 尾部添加 red
 * 2 尾部添加 edr
 * 3 将当前字符串重复10次
 * 问K次操作之后，字符串中red的数量期望是多少。
 * K次操作后得到的可能的结果总数显然是3^K(里面有重复，但是不影响)
 * 如果能计算出所有可能中的red出现的总次数，再除以3^K即可。
 * 由于有重复操作，显然字符串的开头与结尾对重复之后的red数量均有影响，因此一共有5种状态，状态4表示初态，即空字符串
 * 00 表示 red开头red结尾
 * 01 表示 red开头edr结尾
 * 10 表示 edr开头red结尾
 * 11 表示 edr开头edr结尾
 * 令 C[i][st] 表示第i轮过后恰好到达st状态的方案总数
 * 令 D[i][st] 表示第i轮过后能到st状态的所有字符串中的red数量
 * C[i]可以用自动机或者DP由C[i-1]推出，以C[i][0]为例:
 * C[i][0] = C[i-1][4] + C[i-1][0] * 2 + C[i-1][1];
 * 再考虑D[i]，以D[i][0]为例：
 * 首先可以重复10次，因此 D[i][0] += D[i-1][0] * 10;
 * 然后就只有操作1一种方法可以导致状态0，而操作1对每一个字符串都会增加1个red
 * 因此，如果是从状态1经过操作1到达了状态0，则状态1此时一共有C[i-1][1]个字符串，因此新增的red数量就是C[i-1][1]
 * 再加上此时状态1本有的red数量，所以 D[i][0] += D[i-1][1] + C[i-1][1]
 * 其余以此类推。
 * 最后 SIGMA{D[K][0,1,2,3]}是所有可能的red总数，再除以3^K即可。
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

llt const ONE_THIRD = powerMod(3LL, MOD - 2LL);


llt K;
/// 00 表示 red red
/// 01 表示 red edr
/// 10 表示 edr red
/// 11 表示 edr edr
vector<array<mint, 5>> C; // C[i][st] 表示恰好i次操作到达st的不同方案总数
vector<array<mint, 5>> D;

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    K = getInt();
	C.assign(K + 1, {});
	D.assign(K + 1, {});

    C[0][4] = 1;
	for(int i=1;i<=K;++i){
        C[i][4] = C[i-1][4];
		C[i][0] = C[i-1][4] + C[i-1][0] * 2LL + C[i-1][1];
        C[i][3] = C[i-1][4] + C[i-1][3] * 2LL + C[i-1][2];
		C[i][1] = C[i-1][0] + C[i-1][1] * 2LL;
		C[i][2] = C[i-1][3] + C[i-1][2] * 2LL;

		D[i][0] = D[i-1][0] * 10LL + (D[i-1][0] + C[i-1][0]) + (D[i-1][1] + C[i-1][1]) + C[i-1][4];
		D[i][3] = (D[i-1][3] * 10LL + C[i-1][3] * 9) + (D[i-1][3] + C[i-1][3]) + (D[i-1][2]);
		D[i][1] = D[i-1][1] * 10LL + (D[i-1][0]) + (D[i-1][1] + C[i-1][1]);
		D[i][2] = D[i-1][2] * 10LL + (D[i-1][3] + C[i-1][3]) + (D[i-1][2] + C[i-1][2]);
	}

    auto ans = D[K][0] + D[K][1] + D[K][2] + D[K][3];
	auto tmp = mint(powerMod(ONE_THIRD, K));
	cout << (ans * tmp).value << endl;
    return 0;
}