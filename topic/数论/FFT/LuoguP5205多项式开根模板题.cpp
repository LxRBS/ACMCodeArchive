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
/// �����ͬ�෽�̵�Cipolla�㷨
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

/// �¸�������
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
 * @brief ���õ·��ţ��ж�a�Ƿ�Ϊp�Ķ���ʣ��
 * @param a 
 * @param p ������
 * @return int �Ƿ���1���񷵻�-1
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
	/// �ֽ��-1
	if(a < 0) return Legendre(-a, p) * Legendre(-1, p);
	/// �ֽ��2
	int k = 0;
	while(!(a & 1)) a >>= 1, ++k;
	if(k) return (-1 == Legendre(2, p) && (k & 1)) ? -Legendre(a, p) : Legendre(a, p);
    /// ���µߵ�
	return 1 == a % 4 || 1 == p % 4 ? Legendre(p, a) : -Legendre(p, a);
}

/**
 * @brief Cipolla�㷨�������ͬ�෽�� x^2 = n (mod p)
 *  
 * @param n 
 * @param p 
 * @param x0 
 * @param x1 
 * @return int ���ؽ����������Ȼ��012֮һ
 */
int run(llt n, llt p, llt & x0, llt & x1){
    /// ����
	if(0 == n) return x0 = x1 = 0, 1;
	if(1 == n) return x0 = 1, x1 = p - 1, 2;
	if(-1 == Legendre(n, p)) return 0;

	n %= p;
	if(n < 0) n += p;

    if(3 == p % 4){//n^((p+1)/2)��Ȼ��һ����
        x0 = powerMod(n, (p+1)>>2, p);
    }else if(5 == p % 8){//n^((p+3)/8)��2n*(4n)^((p-5)/8)���б�Ȼ��һ���ǽ�
        x0 = powerMod(n, (p+3)>>3, p);
        if((x0 * x0 - n) % p) x0 = (n + n) % p * powerMod(4*n%p, (p-5)>>3, p);
    }else{//Cipolla�㷨
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

/// �������۱任������ʽ����
namespace NTT{

using llt = long long;
using vll = vector<llt>;

int const SIZE_OF_OMEGA = 20;
int const SIZE = 1 << SIZE_OF_OMEGA;
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
 * @param a aҪ������ߴ�
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

/**
 * @brief ��������ʽa��b�������ʽq��r���� a = bq + r
 *   �����ʽarΪa��ת�ã���a�ǹ���x�Ķ���ʽ����ar�ǹ���1/x�Ķ���ʽ����
 *   qr = ar & br^(-1)����ת�û������ɵõ�q�����õ�r
 * @param a ��֤ϵ������[0, MOD)
 * @param b ��֤ϵ������[0, MOD)
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

    /// ת������
    vll br(adeg - bdeg + 1, 0);
    copy(b.rbegin(), b.rbegin() + min(adeg - bdeg + 1, bdeg + 1), br.begin());
    vll brni;
    inv(br, adeg - bdeg, brni);
    
    /// �˷�
    vll ar(a.rbegin(), a.rend());
    mul(ar, brni, q);

    /// ת��
    q.erase(q.begin()+adeg-bdeg+1, q.end());
    reverse(q.begin(), q.end());

    /// ������
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
 * @brief ��������ʽa�����俪������
 *   ans * ans = a (mod x^n) ����a����ߴ���n-1�����ڵ���n�εľ�������
 *   �� H * H = a (mod x^(n/2))������Ȼ ans - H = 0
 *   ���� ans * ans + H * H - 2 * ans * H = 0
 *   ע�⵽ ans * ans = a
 *   ���� ans = a / (2 * H) + H / 2
 *   ���Կ����õݹ����
 * @param a 
 * @param n ������x^nȡģ��a���뱣֤��ߴ�Ϊn-1����a�ĳ��ȱ�֤Ϊn
 * @param ans ������������ʱans����Ϊn
 */
void sqrt(const vll & a, int n, vll & ans){
    assert(n == a.size());
	static const llt INV_TWO = powerMod(2LL, NTT_MOD - 2LL);	
    ans.assign(n, 0);

	function<void(const vll &, int)> _dfs_sqrt = [&ans, &_dfs_sqrt](const vll & a, int n)->void{
        if(1 == n){ // ��a0��ƽ���������뱣֤��
            llt x0, x1;
			int tmp = Cipolla::run(a[0], NTT_MOD, x0, x1);
			assert(tmp >= 1);
			ans[0] = x0;
			return;
		}
		/// �ݹ�
		_dfs_sqrt(a, (n + 1)>>1);
		/// ��ans����
		vll ni;
		inv(std::move(vll(ans.begin(), ans.begin()+n)), n - 1, ni);
		/// ����ni * a��ע����ߵ�n-1��
		vll ji;
		mul(std::move(vll(a.begin(), a.begin()+n)), ni, ji);
		/// ���� (ji  + ans) / 2
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

