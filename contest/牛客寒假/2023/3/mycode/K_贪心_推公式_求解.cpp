/**
 * 给定数组A，ai表示有ai个质数i，质数i表示第i个质数。
 * 令TOTAL = SIMGA{ai}, 为当前拥有的质数的总数量
 * 将这TOTAL个质数排成一个新数组，定义fi为该数组前i个元素的乘积的因子数量
 * 问如何排列可以使得SIMGA{fi, i=1...TOTAL}最大，求这个最大值
 * 简单判断一下即可知道要尽量排列不同的质数。即相同的质数尽可能不要连着放。
 * 将数组A排序得到a1,a2,...,an，按如下原则拜访：
 * 将[p1p2...pn]重复摆放a1次
 * 将[p2...pn]重复拜访a2-a1次
 * ...
 * 将[pn]重复拜访an-a[n-1]次
 * 注意到A数组排序以后，质数p的指标已经发生了变化，但是本题其实不关心p的具体取值，因此不必调整指标
 * 假设到了第t组摆放，此时需要将[pt...pn]重复摆放a[t]-a[t-1]次，每次需要摆放(n-t+1)个数，记作s
 * 考虑其中某次摆放，假设这个次数在总次数中排第b次，则此次摆放贡献的数值为：
 * factor * (b^(s-1)*(b+1) + b^(s-2) * (b+1)^2 + ... + (b+1)^s)
 * 后面显然是一个等比数列，公比为(b+1)/b，可以O(1)求和
 * 前面的factor是之前已经用完的数，为(a1+1)*(a2+1)*...*(a[t-1]+1)
 * 总循环次数为O(max(ai)*等比数列求和)
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

llt value; // value始终非负
mint(llt v=0):value((v%MOD+MOD)%MOD){}

const mint operator + (const mint & r)const{return {(value+r.value)%MOD};}
const mint operator - (const mint & r)const{return {(value-r.value+MOD)%MOD};}
const mint operator * (const mint & r)const{return mint(value * r.value % MOD);}

const mint operator + (llt r)const{return *this + mint(r);}
const mint operator * (llt r)const{return *this * mint(r);}
const mint operator / (llt r)const{return *this * mint(inv((r%MOD+MOD)%MOD));}

/// 不用^重载乘方，因为^优先级比+-*/低，容易造成误解，[]的优先级比较高
const mint operator [] (llt n)const{return mint(powerMod(this->value, n));}

const mint operator += (const mint & r){
	(value += r.value) %= MOD;
	return *this;
}

};

int N;
vi A;

inline mint sum(const mint & a1, const mint & q, int n){
	return a1 * (q[n] + mint(-1LL)) / (q.value - 1LL);
}

llt proc(){
	sort(A.begin(), A.end());
	mint ans = 0;
	llt base = 1;
	llt factor = 1LL;
	for(int m,i=1,last=N;i<=N;++i,--last){		
        m = A[i] - A[i-1];
		// printf("%d: repeat %d times with factor %lld\n", i, m, factor);
		mint tmp(factor);
        for(int j=1;j<=m;++j){
			// printf("a1 = (%lld^%d)*(%lld^%d), an = (%lld^%d)\n", base, last-1, base+1, 1, base+1, last);
			ans += sum(mint(base+1)*mint(base)[last-1], mint(base+1)/base, last) * tmp;
			++base;
		}
		(factor *= A[i] + 1) %= MOD;
	}
	return ans.value;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    A.assign((N = getInt())+1, 0);
	for(int i=1;i<=N;++i) A[i] = getInt();
	cout << proc() << endl;
    return 0;
}