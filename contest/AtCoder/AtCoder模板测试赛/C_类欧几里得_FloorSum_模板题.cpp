#include <bits/stdc++.h>
using namespace std;

namespace IO{

char *__abc147, *__xyz258, __ma369[1000000];
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

llt getLL(){
	int sgn = 1;
	char ch = __hv007();
	while( ch != '-' && ( ch < '0' || ch > '9' ) ) ch = __hv007();
	if ( '-' == ch ) {sgn = 0;ch=__hv007();}
 
	llt ret = (int)(ch-'0');
	while( '0' <= (ch=__hv007()) && ch <= '9' ) ret = ret * 10LL + (llt)(ch-'0');
	return sgn ? ret : -ret;    
}

char getChar(function<bool(char)> ok){
    char ch = __hv007();
    while(!ok(ch)) ch = __hv007();
    return ch;
}

}

namespace SHULUN{

using llt = long long;
using int128 = __int128_t;

/// T需要支持加法和乘法运算,注意不满足交换律, p是乘数，q是分母，r是加数
/// n是累加上限，即累加从1到n，su是U事件的信息，sr是r事件的信息
template<typename T>
T __dfs_uniEuclid(llt p, llt q, llt r, llt n, T su, T sr){
    if(r >= q) {
		return su * (r / q) + __dfs_uniEuclid(p, q, r % q, n, su, sr);
	}
	if(p >= q){
		return __dfs_uniEuclid(p % q, q, r, n, su, su * (p / q) + sr);
	}
	llt k = (static_cast<int128>(p) * n + r) / q; // 乘法可能超
	if(0 == k){
		return sr * n;
	}

	auto ans = sr * ((q - r - 1) / p);
	ans += su;
	ans += __dfs_uniEuclid(q, p, (q - r - 1) % p, k - 1, sr, su);
    ans += sr * (n - (static_cast<int128>(k) * q - r - 1) / p);
	return ans;
}

/// T需要支持加法和乘法运算,注意不满足交换律, 
/// T需要提供sr和su的构造方法
/// p是乘数，q是分母，r是加数
/// n是累加上限，即累加从1到n
/// q必须不为0，如果n为0或者p为0，要在外面单独计算
/// 构造不同的T，就可以支持不同的求和式
template<typename T>
T uniEuclid(llt p, llt q, llt r, llt n){
	assert(p && q && n);
	// T sr(1, 0, 0); // 表示x=0与f相交的情况
	// T su(0, 1, 0); // 表示y=1与f相交的情况
    // auto ans = __dfs_uniEuclid(p, q, r, n, su, sr);
	// return ans;
	// return __dfs_uniEuclid(p, q, r, n, T(0, 1, 0), T(1, 0, 0));
    return __dfs_uniEuclid(p, q, r, n, T::su(), T::sr());
}


struct px_plus_r_divide_by_q{

/// floor((pi + r) / q)
/// 与uniEuclid配合使用，即可求出 SUM{floor(i), i=1...n}

using INT = llt; // 不取模就直接用longlong
// using INT = SHULUN::modint<>;

/// 分别表示x的整点数量，y的整点数量，s即表示结果的和
INT x, y, s;

px_plus_r_divide_by_q() = default;
px_plus_r_divide_by_q(llt xx, llt yy, llt ss):x(xx),y(yy),s(ss){}

static px_plus_r_divide_by_q sr(){return px_plus_r_divide_by_q(1, 0, 0);}
static px_plus_r_divide_by_q su(){return px_plus_r_divide_by_q(0, 1, 0);}

px_plus_r_divide_by_q & operator += (const px_plus_r_divide_by_q & r){
	/// this->y表示左边段的y整点数量, r.x表示右边x的整点数量
	/// 相乘恰好表明右边段下方矩形的整点数量
	this->s += r.s + this->y * r.x;	
	this->x += r.x; // 两段的整点数量相加
	this->y += r.y;
	return *this;
}

const px_plus_r_divide_by_q operator + (const px_plus_r_divide_by_q & r) const {
    auto tmp(*this);
	return tmp += r;
}

px_plus_r_divide_by_q & operator *= (llt n){
	if(0 == n) {x = y = s = INT(0); return *this;}
	if(1 == n) return *this;
	n -= 1;
	auto tmp(*this);
	while(n){
		if(n & 1) *this += tmp;
		tmp += tmp;
		n >>= 1; 
	}
	return *this;
}

const px_plus_r_divide_by_q operator * (llt n) const {
	auto tmp(*this); return tmp *= n;
}


};


}

using llt = long long;

llt N, P, R, Q;

llt proc(){
	if(0 == N) return R / Q;
	if(0 == P) return R / Q * (N + 1);
	auto ans = SHULUN::uniEuclid<SHULUN::px_plus_r_divide_by_q>(P, Q, R, N);
	return ans.s + R / Q;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    // ios::sync_with_stdio(0); 
    // cin.tie(0); cout.tie(0);
    using namespace IO;
    int nofkase = getInt();
	while(nofkase--){
	    N = getInt() - 1;
		Q = getInt();
		P = getInt();
		R = getInt();
		
		printf("%lld\n", proc());
	}
	return 0;
}
