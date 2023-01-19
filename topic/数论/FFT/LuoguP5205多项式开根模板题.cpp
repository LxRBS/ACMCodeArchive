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

using llt = long long;
/// 解二次同余方程的Cipolla算法
namespace Cipolla{

using llt = long long;

llt powerMod(llt a, llt n, llt mod){
	llt ret = 1;
	a %= mod;
	while(n){
		if(n & 1) ret = ret * a % mod;
		n >>= 1;
		a = a * a % mod;
	}
	return ret;
}

/// 仿复数运算
using complex_t = pair<llt, llt>;

complex_t mul(const complex_t & a, const complex_t & b, llt const i2, llt p){
    return make_pair
	(
		(a.first*b.first%p+i2*a.second%p*b.second%p)%p,
		(a.first*b.second%p+a.second*b.first%p)%p
    );
}

complex_t powerMod(complex_t a,llt n,llt const i2,llt p){
    complex_t ans = make_pair(1,0);
    while(n){
        if(n&1) ans = mul(ans,a,i2,p);
        a = mul(a,a,i2,p);
        n>>=1;
    }
    return ans;
}

/**
 * @brief 勒让德符号，判断a是否为p的二次剩余
 * @param a 
 * @param p 正奇数
 * @return int 是返回1，否返回-1
 */
int Legendre(llt a, llt p){
    a %= p;
	if(0 == a || 1 == a) return 1;
	if(-1 == a)switch(p % 4){
		case 1:return 1; case 3: return -1; default: return 0;
	}
	if(2 == a)switch(p % 8){
		case 1: case 7: return 1; case 3: case 5: return -1; default: return 0;
	}
	/// 分解出-1
	if(a < 0) return Legendre(-a, p) * Legendre(-1, p);
	/// 分解出2
	int k = 0;
	while(!(a & 1)) a >>= 1, ++k;
	if(k) return (-1 == Legendre(2, p) && (k & 1)) ? -Legendre(a, p) : Legendre(a, p);
    /// 上下颠倒
	return 1 == a % 4 || 1 == p % 4 ? Legendre(p, a) : -Legendre(p, a);
}

/**
 * @brief Cipolla算法，解二次同余方程 x^2 = n (mod p)
 *  
 * @param n 
 * @param p 
 * @param x0 
 * @param x1 
 * @return int 返回解的数量，必然是012之一
 */
int run(llt n, llt p, llt & x0, llt & x1){
    /// 特判
	if(0 == n) return x0 = x1 = 0, 1;
	if(1 == n) return x0 = 1, x1 = p - 1, 2;
	if(-1 == Legendre(n, p)) return 0;

	n %= p;
	if(n < 0) n += p;

    if(3 == p % 4){//n^((p+1)/2)必然是一个解
        x0 = powerMod(n, (p+1)>>2, p);
    }else if(5 == p % 8){//n^((p+3)/8)与2n*(4n)^((p-5)/8)其中必然有一个是解
        x0 = powerMod(n, (p+3)>>3, p);
        if((x0 * x0 - n) % p) x0 = (n + n) % p * powerMod(4*n%p, (p-5)>>3, p);
    }else{//Cipolla算法
        llt a = rand() % p;
        while(0 == a || 1==Legendre(a * a - n, p)) a = rand()%p;
        x0 = powerMod(make_pair(a, 1), (p+1)>>1, (a * a - n + p) % p, p).first;
    }

    x1 = p - x0;
    if(x0 == x1) return 1;
    if(x0 > x1) swap(x0, x1);
    return 2;
}

}

/// 快速数论变换及多项式计算
namespace NTT{

using llt = long long;
using vll = vector<llt>;

int const SIZE_OF_OMEGA = 20;
int const SIZE = 1 << SIZE_OF_OMEGA;
// llt const NTT_MOD = (479LL << 21) | 1LL; // 大质数
llt const NTT_MOD = 998244353LL; // 大质数
llt const G = 3LL; // 大质数的原根

bool test(const vll & a){
    for(auto i : a)if(i < 0 || i >= NTT_MOD)return false;
    return true;
}

llt powerMod(llt a, llt n){
    llt ans = 1LL;
    a %= NTT_MOD;
    while(n){
        if(n & 1) (ans *= a) %= NTT_MOD;
        (a *= a) %= NTT_MOD;
        n >>= 1;
    }
    return ans;
}

const vll & getOmega(){
    static vll Omega;
    if(Omega.empty()){
        Omega.reserve(SIZE_OF_OMEGA);
        for(int i=0;i<SIZE_OF_OMEGA;++i){
            int t = 1 << i;
            Omega.emplace_back(powerMod(G, (NTT_MOD - 1) / t));
        }
    }
    return Omega;
}

/// 雷德算法
void Rader(vll & a){
    auto n = a.size();    
    assert(0 == (n & n - 1));
    for(int i=1,j=n>>1,k;i+1<n;++i){
        if(i < j) swap(a[i], a[j]);
        k = n >> 1;
        while(j >= k) j -= k, k >>= 1;
        if(j < k) j += k;
    }   
}

/// 快速数论变换，a是输入输出参数，isInv为真表示逆变换
void ntt(vll & a, bool isInv = false){
    Rader(a);
    const auto & omega = getOmega();
    auto n = a.size();    

    for(int h=2,id=1;h<=n;h<<=1,++id){
        for(int j=0;j<n;j+=h){
            llt u,v,w = 1LL;
            for(int k=j,tmp=j+(h>>1);k<tmp;++k){
                u = a[k];
                v = w * a[k+(h>>1)] % NTT_MOD;
                a[k] = (u + v) % NTT_MOD;
                a[k + (h>>1)] = (u - v + NTT_MOD) % NTT_MOD;
                (w *= omega[id]) %= NTT_MOD;
            }
        }
    }
    if(isInv){
        for(int i=1,tmp=n>>1;i<tmp;++i) swap(a[i], a[n-i]);
        llt invv = powerMod(n, NTT_MOD - 2LL);
        for(int i=0;i<n;++i) (a[i] *= invv) %= NTT_MOD;
    }
    return;
}

/// 多项式的乘法
void mul(const vll & a, const vll & b, vll & ans){
    int an = a.size();
    int bn = b.size();
    int ff = 1;
    while(ff < an + bn) ff <<= 1;
    assert(ff <= SIZE);

    ans.clear(); ans.assign(ff, 0);
    copy(a.begin(), a.end(), ans.begin());

    vll y(ff, 0);
    copy(b.begin(), b.end(), y.begin());

    ntt(ans); ntt(y);

    for(int i=0;i<ff;++i) (ans[i] *= y[i]) %= NTT_MOD;

    ntt(ans, true);
    ans.erase(ans.begin()+an+bn-1,ans.end());
    return;
}

/**
 * @brief 多项式求逆,a确保最高次为n，不足需要补零
 *  ax = 1 高于n次的不计
 *  令b最高次为n/2, 且 ab = 1
 *  则 x = b * (2 - a * b)
 *  因此可以使用递归来求
 * @param a a要补到最高次
 * @param deg 最高次
 * @param ans 逆
 */
void inv(const vll & a, int deg, vll & ans){
    assert(a.size() - 1 == deg);
    ans.assign(deg + 1, 0);
    function<void(int)> _dfs_inv = [&](int cur_len){
        if(1 == cur_len) return (void)(ans[0] = powerMod(a[0], NTT_MOD - 2LL));
        /// 递归
        _dfs_inv(1+cur_len>>1);      
        /// 求NTT长度
        int limit = 1, len = 0;
        while(limit < (cur_len << 1)) limit <<= 1, ++len;

        vll x(limit, 0), y(limit, 0);
        copy(a.begin(), a.begin() + cur_len, x.begin());
        copy(ans.begin(), ans.begin() + cur_len, y.begin());

        ntt(x); ntt(y);

        for(int i=0;i<limit;++i){
            (y[i] *= (2LL - x[i] * y[i] % NTT_MOD + NTT_MOD) % NTT_MOD) %= NTT_MOD;
        }

        ntt(y, true);
        copy(y.begin(), y.begin() + cur_len, ans.begin());
        return;
    };
    _dfs_inv(deg + 1); // 这里传的是长度
    return;
}

/**
 * @brief 给定多项式a和b，求多项式q和r满足 a = bq + r
 *   令多项式ar为a的转置，即a是关于x的多项式，而ar是关于1/x的多项式，有
 *   qr = ar & br^(-1)，再转置回来即可得到q，并得到r
 * @param a 保证系数都在[0, MOD)
 * @param b 保证系数都在[0, MOD)
 * @param q 
 * @param pr 
 */
void div(const vll & a, const vll & b, vll & q, vll * pr = nullptr){
    assert(test(a) && test(b));
    int adeg = a.size() - 1;
    int bdeg = b.size() - 1;
    if(adeg < bdeg){
        q.assign(1, 0);
        if(pr) pr->assign(a.begin(), a.end());
        return;
    }

    /// 转置求逆
    vll br(adeg - bdeg + 1, 0);
    copy(b.rbegin(), b.rbegin() + min(adeg - bdeg + 1, bdeg + 1), br.begin());
    vll brni;
    inv(br, adeg - bdeg, brni);
    
    /// 乘法
    vll ar(a.rbegin(), a.rend());
    mul(ar, brni, q);

    /// 转置
    q.erase(q.begin()+adeg-bdeg+1, q.end());
    reverse(q.begin(), q.end());

    /// 求余数
    if(pr){
        auto & r = *pr;
        mul(b, q, r);
        r.erase(r.begin()+bdeg, r.end());
        for(int i=0;i<bdeg;++i){
            r[i] = (a[i] - r[i] + NTT_MOD) % NTT_MOD;
        }
    }
    return;
}

/**
 * @brief 给定多项式a，对其开根，即
 *   ans * ans = a (mod x^n) ，即a的最高次是n-1，大于等于n次的均不考虑
 *   令 H * H = a (mod x^(n/2))，则显然 ans - H = 0
 *   所以 ans * ans + H * H - 2 * ans * H = 0
 *   注意到 ans * ans = a
 *   所以 ans = a / (2 * H) + H / 2
 *   所以可以用递归求解
 * @param a 
 * @param n 表明对x^n取模，a必须保证最高次为n-1，即a的长度保证为n
 * @param ans 输出参数，输出时ans长度为n
 */
void sqrt(const vll & a, int n, vll & ans){
    assert(n == a.size());
	static const llt INV_TWO = powerMod(2LL, NTT_MOD - 2LL);	
    ans.assign(n, 0);

	function<void(const vll &, int)> _dfs_sqrt = [&ans, &_dfs_sqrt](const vll & a, int n)->void{
        if(1 == n){ // 求a0的平方根，必须保证有
            llt x0, x1;
			int tmp = Cipolla::run(a[0], NTT_MOD, x0, x1);
			assert(tmp >= 1);
			ans[0] = x0;
			return;
		}
		/// 递归
		_dfs_sqrt(a, (n + 1)>>1);
		/// 求ans的逆
		vll ni;
		inv(std::move(vll(ans.begin(), ans.begin()+n)), n - 1, ni);
		/// 计算ni * a，注意最高到n-1次
		vll ji;
		mul(std::move(vll(a.begin(), a.begin()+n)), ni, ji);
		/// 计算 (ji  + ans) / 2
		for(int i=0;i<n;++i){
			ans[i] = (ans[i] + ji[i]) % NTT_MOD * INV_TWO % NTT_MOD;
		}
		return;
	};

    _dfs_sqrt(a, n);
	return;
}

}

int N;
vector<llt> A;
vector<llt> Ans;

int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif 
    A.assign(N = getInt(), 0);
	for(auto & i : A) i = getInt();
    NTT::sqrt(A, N, Ans);
	for(auto i : Ans) printf("%lld ", i);
	printf("\n");	
    return 0;
}

