/**
   给定一个矩形，再给定一个弯道，问矩形能够过弯的弯道宽度最小是多少
   车头方向必须是切线方向
   由于指定了车头方向，所以指定角度下的宽度很容易计算
   且宽度应该是角度的一个单峰函数，三分即可
   做完发现可以直接解析得到最值，不用三分
*/
#include <bits/stdc++.h>
using namespace std;

double const EPS = 1E-8;
double const PI = acos(-1.0);
double const INF = 1E100;

inline int sgn(double x){return x>EPS?1:(x<-EPS?-1:0);}
inline bool is0(double x){return 0==sgn(x);}
inline bool isEq(double x,double y){return is0(x-y);}
inline double myasin(double x){
    if(x<-1.0)x=-1.0;
    else if(x>1.0)x=1.0;
    return asin(x);
}
inline double myacos(double x){
    if(x<-1.0)x=-1.0;
    else if(x>1.0)x=1.0;
    return acos(x);
}

int getUnsigned(){
	char ch = getchar();
	while( ch < '0' || ch > '9' ) ch = getchar();

	int ret = (int)(ch-'0');
	while( '0' <= ( ch = getchar() ) && ch <= '9' ) ret = ret * 10 + (int)(ch-'0');
	return ret;
}

double A,B,R,D;
inline double f(double theta){
    return (A+R) * cos(theta) + B * sin(theta);
}
double trinary(){
    double theta = atan(B/(A+R));
    theta = min(theta, D*PI/180.0);

    double left = 0.0, right = theta, m1, m2, t;
    do{
        t = (right-left) / 3.0;
        m1 = left + t, m2 = right - t;
        if(f(m1) < f(m2)) left = m1;
        else right = m2;
    }while(!is0(right-left));
    return f(right);
}
int main(){
    //freopen("damage.in","r",stdin);
    //freopen("damage.out","w",stdout);
    //freopen("1.txt","r",stdin);
    int nofkase = getUnsigned();
    for(int kase=1;kase<=nofkase;++kase){
        A = getUnsigned();
        B = getUnsigned();
        R = getUnsigned();
        D = getUnsigned();
        printf("%.12f\n",trinary()-R);
    }
    return 0;
}

