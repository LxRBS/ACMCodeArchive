/**
 * 已知f(z)是复平面上的分式变换
 * 并且给定zi和f(zi), i=1,2,3
 * 再给定z0，求f(z0)
 * 本质上是解方程，f(z) = (az + b) / (cz + d)
 * 解出a、b、c、d即可。可以固定一个数，做缩放解另外三个数
 * 复平面分式变换具有一系列的性质，例如交比不变性：
 *      w - w1         z - z1
 *     --------       --------
 *      w - w2         z - z2
 *   ------------ == -----------
 *      w3 - w1        z3 - z1
 *     ---------      ---------
 *      w3 - w2        z3 - z2
 * 其中 wi = f(zi)
 * 题目保证有解，因此要么能够解出来，要么重合的情况下，直接取值即可。
*/
#include <bits/stdc++.h>
using namespace std;

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

typedef long long llt;
llt const INF = 1E17;

#ifndef ONLINE_JUDGE
int const SIZE = 13;
#else
int const SIZE = 300010;
#endif

typedef long double Real;
Real const EPS = 1E-9;
inline int sgn(Real x){return x>EPS?1:(x<-EPS?-1:0);}

struct Complex{
	Real a, b;
	Complex(Real aa=0, Real bb=0):a(aa),b(bb){}
}Z[4], W[4];

bool operator == (const Complex &lhs, const Complex &rhs){
    return 0 == sgn(lhs.a-rhs.a) && 0 == sgn(lhs.b-rhs.b);
}

const Complex operator - (const Complex &lhs, const Complex &rhs){
	return Complex(lhs.a - rhs.a, lhs.b - rhs.b);
}

const Complex operator + (const Complex &lhs, const Complex &rhs){
	return Complex(lhs.a + rhs.a, lhs.b + rhs.b);
}

const Complex operator * (const Complex &lhs, const Complex &rhs){
	return Complex(lhs.a*rhs.a - lhs.b*rhs.b, lhs.a*rhs.b + lhs.b*rhs.a);
}

const Complex operator / (const Complex &lhs, const Complex &rhs){
	Real t = rhs.a * rhs.a + rhs.b * rhs.b;
	return Complex((lhs.a*rhs.a+lhs.b*rhs.b)/t, (lhs.b*rhs.a-lhs.a*rhs.b)/t);
}

const Complex ONE(1, 0);

void proc(){
	if(Z[0] == Z[1]) {
		W[0] = W[1]; 
	}else if(Z[0] == Z[2]){
		W[0] = W[2]; 
	}else if(Z[0] == Z[3]){
		W[0] = W[3]; 
	}else{
		/// 以下注释的4行也可以AC
		// Complex zuo = (Z[0]-Z[1])*(W[3]-W[1])*(Z[3]-Z[2]);
		// Complex you = (Z[0]-Z[2])*(W[3]-W[2])*(Z[3]-Z[1]);
		// if(zuo == you)while(1);
		// else W[0] = (zuo * W[2] - you * W[1]) / (zuo - you);  
		Complex tmp = ((Z[0]-Z[1])/(Z[0]-Z[2]))/((Z[3]-Z[1])/(Z[3]-Z[2])) * (W[3]-W[1])/(W[3]-W[2]);
	    W[0] = (tmp * W[2] - W[1]) / (tmp - ONE);      		
	}
	// printf("%.9f %.9f\n", W->a, W->b);  
	printf("%.12Lf %.12Lf\n", W->a, W->b);  
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt","r",stdin);
#endif
    int nofkase = getInt();
	while(nofkase--){
        for(int i=1;i<=3;++i){
			Z[i].a = getInt();
			Z[i].b = getInt();
			W[i].a = getInt();
			W[i].b = getInt();
		}
		Z[0].a = getInt(); Z[0].b = getInt();
		proc();
	}
    return 0;
}

