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

using llt = long long;
using vll = vector<llt>;


namespace NTT{

using llt = long long;
using vll = vector<llt>;

int const SIZE_OF_OMEGA = 22; 
int const SIZE = 1 << SIZE_OF_OMEGA; // 多项式的长度不能超过SIZE
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


/**
 * @brief 多项式求逆,a确保最高次为n，不足需要补零
 *  ax = 1 高于n次的不计
 *  令b最高次为n/2, 且 ab = 1
 *  则 x = b * (2 - a * b)
 *  因此可以使用递归来求
 * @param a a要补到最高次，即a的长度是deg+1
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


}

int N;
vll A;
vll B;

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    // ios::sync_with_stdio(0); 
    // cin.tie(0); cout.tie(0);	
    using namespace IO;
	A.assign(N=getInt(), 0);
	A[0] = 1;
	for(int i=1;i<N;++i) A[i] = NTT::NTT_MOD - getInt() % NTT::NTT_MOD;
    NTT::inv(A, N - 1, B);
    for(auto i : B) printf("%lld ", i);
	printf("\n");
	return 0;
}