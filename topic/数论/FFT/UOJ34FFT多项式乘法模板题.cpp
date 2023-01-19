/**
 * 多项式乘法，FFT模板题
 */
#include <bits/stdc++.h>
using namespace std;
 
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
 
#ifndef ONLINE_JUDGE
int const SIZE = 23;
#else
int const SIZE = 110;
#endif

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

using vi = vector<int>;
using vd = vector<double>;
vd A, B;
int N, M;

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    A.assign((N=getInt())+1, 0);
    B.assign((M=getInt())+1, 0);
    for(auto & i : A) i = getInt();
    for(auto & i : B) i = getInt();

    vd ans;
    FFT::mul(A, B, ans);

    for(const auto & i : ans){
        printf("%d ", (int)(i + 0.5));
    }
    printf("\n");
    return 0;
}
