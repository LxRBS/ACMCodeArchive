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
    complex_t conj()const{return complex_t(real,-imag);}
    void disp()const{printf("(%3.1f",real);if(imag>0)putchar('+');printf("%3.1fi)",imag);}
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

int getUnsigned(){
	char ch = getchar();
	while( ch < '0' || ch > '9' ) ch = getchar();

	int ret = (int)(ch-'0');
	while( '0' <= ( ch = getchar() ) && ch <= '9' ) ret = ret * 10 + (int)(ch-'0');
	return ret;
}

void dispArr(complex_t const a[],int n){
    for(int i=0;i<n;++i)a[i].disp();
    putchar('\n');
}
int main(){
    //freopen("1.txt","r",stdin);
	int n = getUnsigned();
	int m = getUnsigned();

    //令输入为Ax和Bx，则X=A+Bi
	++n,++m;
	for(int i=0;i<n;++i)X[i].real=getUnsigned();
	for(int i=0;i<m;++i)X[i].imag=getUnsigned();

	int ff = 1;
	while( ff < n + m ) ff <<= 1;

	FFT(X,ff);
	//FFT(Y,ff);

	//dispArr(X,ff);
	//dispArr(Y,ff);

    ///*
    complex_t const ctmp(0.0,0.25);
    Y[0].real = X[0].real * X[0].imag;
    Y[0].imag = 0;
	for(int i=1;i<ff;++i){
        Y[i] = ( X[ff-i].conj() + X[i] ) * ( X[ff-i].conj() - X[i] ) * ctmp;
	}

	FFT(Y,ff,-1);

	--n,n += --m;
	printf("%d",(int)(Y[0].real+0.5));
	for(int i=1;i<=n;++i){
        printf(" %d",(int)(Y[i].real+0.5));
	}
    putchar('\n');
    //*/
	return 0;
}
