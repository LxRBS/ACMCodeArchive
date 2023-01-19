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


/// �������۱任������ʽ����
/// ����ʽ�����ſ�����Ҫ�õ�Cipolla�㷨
namespace NTT{

using llt = long long;
using vll = vector<llt>;

int const SIZE_OF_OMEGA = 20; 
int const SIZE = 1 << SIZE_OF_OMEGA; // ����ʽ�ĳ��Ȳ��ܳ���SIZE
// llt const NTT_MOD = (479LL << 21) | 1LL; // ������
llt const NTT_MOD = 998244353LL; // ������
llt const G = 3LL; // ��������ԭ��

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

/// �׵��㷨
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

/// �������۱任��a���������������isInvΪ���ʾ��任
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

/// ����ʽ�ĳ˷�
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
 * @brief ����ʽ����,aȷ����ߴ�Ϊn��������Ҫ����
 *  ax = 1 ����n�εĲ���
 *  ��b��ߴ�Ϊn/2, �� ab = 1
 *  �� x = b * (2 - a * b)
 *  ��˿���ʹ�õݹ�����
 * @param a aҪ������ߴΣ���a�ĳ�����deg+1
 * @param deg ��ߴ�
 * @param ans ��
 */
void inv(const vll & a, int deg, vll & ans){
    assert(a.size() - 1 == deg);
    ans.assign(deg + 1, 0);
    function<void(int)> _dfs_inv = [&](int cur_len){
        if(1 == cur_len) return (void)(ans[0] = powerMod(a[0], NTT_MOD - 2LL));
        /// �ݹ�
        _dfs_inv(1+cur_len>>1);      
        /// ��NTT����
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
    _dfs_inv(deg + 1); // ���ﴫ���ǳ���
    return;
}

/// �Զ���ʽ��
void derivate(const vll & a, vll & ans){
    auto n = a.size();
	ans.assign(n, 0);
	for(int i=1;i<n;++i){
		ans[i - 1] = i * a[i] % NTT_MOD;
	}
	return;
}

/// �����ʽ��������
void integral(const vll & a, vll & ans){
    auto n = a.size();
	ans.assign(n, 0);
	for(int i=1;i<n;++i){
		ans[i] = a[i-1] * powerMod(i, NTT_MOD - 2LL) % NTT_MOD;
	}
	return;
}

/**
 * @brief �Զ���ʽa��������� ans = ln(a) (mod x^n)
 *  �������� ans' = a' / a
 *  ��˿����ȶ�a�󵼣�Ȼ�����a���棬Ȼ���ٲ������ּ���
 * @param a ��֤x����ߴ�Ϊn-1����a�ĳ�����n����֤a0==1
 * @param n ����ģ x^n
 * @param ans 
 */
void ln(const vll & a, int n, vll & ans){
    assert(a.size() == n);
    /// �ȶ�a����
    inv(a, n - 1, ans);
    /// �ٶ�a��
    vll ap;
    derivate(a, ap);
    /// �˻�
    vll ji;
    mul(ap, ans, ji);
    /// �ٻ���
    integral(ji, ans);
    ans.erase(ans.begin()+n, ans.end());
    return;
}

}



using llt = long long;
using vll = vector<llt>;

vll A;
int N;
vll Ans;

int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif 
    A.assign(N = getInt(), 0);
    for(auto & i : A) i = getInt();

    NTT::ln(A, N, Ans);
    for(auto i : Ans) printf("%lld ", i);
    printf("\n");
    return 0;
}

