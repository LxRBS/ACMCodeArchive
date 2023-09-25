/**
 * 大整数乘法，据说需要常数优化
 * 但不优化的NTT也能过
 */
#include <bits/stdc++.h>
using namespace std;

#include <bits/extc++.h>
using namespace __gnu_pbds;


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



int main(){
#ifndef ONLINE_JUDGE
    freopen("z.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    string sa, sb; cin >> sa >> sb;
    int na = sa.length(), nb = sb.length();
    vector<double> a(na), b(nb), c;
    for(int i=na-1;i>=0;--i) a[na - i - 1] = sa[i] - '0';
    for(int i=nb-1;i>=0;--i) b[nb - i - 1] = sb[i] - '0';
    FFT::mul(a, b, c);
    vector<int> d; d.reserve(c.size() + 1);
    int carry = 0;
    for(int t,i=0,n=c.size();i<n;++i) {
        t = (int)(c[i] + 0.5) + carry;
        carry = t / 10;
        d.push_back(t % 10);
    }
    if(carry) d.push_back(carry);
    for(int i=d.size()-1;i>=0;--i) cout << d[i];
    cout << endl;
    return 0;
}