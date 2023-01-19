
/// 快速傅里叶变换以及多项式计算
namespace FFT{

using Real = double;
using vr = vector<Real>;
using Complex = complex<Real>;
using vc = vector<Complex>;

Real const PI = acos((Real)-1);
Real const D_PI = PI + PI;

// 雷德算法，调整系数的位置
void Rader(vc & a){
    auto n = a.size() - 1;
    /// n必须是2的幂
    assert(0 == (n & n - 1));
    for(int i=1,j=n>>1,k;i+1<n;++i){
        if(i < j) swap(a[i], a[j]);
        k = n >> 1;
        while(j >= k) j -= k, k >>= 1;
        if(j < k) j += k;
    }
}

/// 快速傅里叶变换, a表示系数，从a0到an
/// n必须是2的幂, inv取-1表示逆变换
/// 结果放在a中
void fft(vc & a, int inv = 1){
    Rader(a);
    auto n = a.size() - 1;
    /// 最外层循环
    for(int i=2;i<=n;i<<=1){
        Complex wm(cos(D_PI/(Real)i), -inv * sin(D_PI/(Real)i));
        /// 中间循环n/i次
        for(int j=0;j<n;j+=i){
            Complex w(1.0, 0.0);
            for(int k=j,t=j+(i>>1);k<t;++k){
                Complex u(a[k]);
                Complex v(w * a[k + (i>>1)]);
                a[k] = u + v;
                a[k + (i>>1)] = u - v;
                w = w * wm;
            }
        }
    }
    /// 如果是逆变换，再除以n
    if(-1 == inv)for(auto & c : a) c /= n; 
}

/// 计算多项式a * b，结果放在ans
void mul(const vr & a, const vr & b, vr & ans){
    /// 构建一个复数多项式x,令 x = a + bi
    int an = a.size();
    int bn = b.size();
    auto ff = 1;
    while(ff < an + bn) ff <<= 1;

    vc x(ff+1, Complex((Real)0, (Real)0));
    for(int i=0,n=a.size();i<n;++i) x[i].real(a[i]);
    for(int i=0,n=b.size();i<n;++i) x[i].imag(b[i]);

    fft(x);

    const Complex ctmp((Real)0, (Real)0.25);
    vc y; y.reserve(ff + 1);
    y.emplace_back(x[0].real() * x[0].imag(), (Real)0);
    for(int i=1;i<=ff;++i){
        y.emplace_back((conj(x[ff-i]) + x[i]) * (conj(x[ff-i]) - x[i]) * ctmp);
    }

    fft(y, -1);
    
    --an, --bn;
    ans.clear(); ans.reserve(an + bn + 1);
    for(int i=0,n=an+bn;i<=n;++i){
        ans.emplace_back(y[i].real());
    }

    return;
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

}
