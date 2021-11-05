//快速傅里叶变换，多项式乘法，模板题
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <algorithm>
using namespace std;

double const PI = acos(-1.0);
double const D_PI = 2.0 * PI;

//复数及其运算
struct complex_t{
    double real,imag;
    complex_t(double xx=0.0,double yy=0.0):real(xx),imag(yy){}
};

const complex_t operator + (complex_t const&lhs,complex_t const&rhs){
	return complex_t( lhs.real + rhs.real, lhs.imag + rhs.imag );
}

const complex_t operator - (complex_t const&lhs,complex_t const&rhs){
	return complex_t( lhs.real - rhs.real, lhs.imag - rhs.imag );
}

const complex_t operator * (complex_t const&lhs,complex_t const&rhs){
	return complex_t(
		    lhs.real * rhs.real - lhs.imag * rhs.imag,
			lhs.real * rhs.imag + lhs.imag * rhs.real
		);
}

//雷德算法，调整系数位置，n为数组长度，从0开始
void Rader(complex_t a[],int n){
    for(int i=1,j=n>>1,k;i<n-1;++i){
        if ( i < j ) swap(a[i],a[j]);
        k = n >> 1;
        while( j >= k ) j -= k, k >>= 1;
        if ( j < k ) j += k;
    }
}

//快速傅里叶变换，n必须是2的幂，inv取-1表示逆变换
void FFT(complex_t a[],int n,int inv=1){
    Rader(a,n);
    //最外层循环
    for(int i=2;i<=n;i<<=1){
        complex_t wm( cos(D_PI/(double)i),-inv*sin(D_PI/(double)i) );

        //中间循环n/i次
        for(int j=0;j<n;j+=i){
            complex_t w(1.0);
            for(int k=j,t=j+(i>>1);k<t;++k){
                complex_t u(a[k]);
                complex_t v(w*a[k+(i>>1)]);
                a[k] = u + v;
                a[k+(i>>1)] = u - v;
                w = w * wm;
            }
        }
    }
    //如果是逆变换，再除以n，不关心虚部
    if ( -1 == inv ) for(int i=0;i<n;++i) a[i].real /= n;
}

//将字符串转为复数序列，an为字符串长度，cn为复数序列长度
void str2Complex(char const a[],int const an,complex_t c[],int const cn){
    for(int i=0;i<an;++i) c[i].real = (double)(a[an-1-i]-'0'), c[i].imag = 0.0;
    fill(c+an,c+cn,complex_t());
}

int const SIZE = 65536<<1;

complex_t X[SIZE<<1],Y[SIZE<<1];

int main(){
	int n,m;
	scanf("%d%d",&n,&m);
	++n,++m;
	for(int i=0;i<n;++i)scanf("%lf",&X[i].real),X[i].imag=0.;
	for(int i=0;i<m;++i)scanf("%lf",&Y[i].real),Y[i].imag=0.;

	int ff = 1;
	while( ff < n + m ) ff <<= 1;

	FFT(X,ff);
	FFT(Y,ff);

	for(int i=0;i<ff;++i) X[i] = X[i] * Y[i];

	FFT(X,ff,-1);

	--n,n += --m;
	printf("%d",(int)(X[0].real+0.5));
	for(int i=1;i<=n;++i){
        printf(" %d",(int)(X[i].real+0.5));
	}
    putchar('\n');
	return 0;
}
