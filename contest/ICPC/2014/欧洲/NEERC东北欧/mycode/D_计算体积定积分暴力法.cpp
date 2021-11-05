/**
   一个油罐，两边是球冠，中间是圆柱。
   现将其倾斜一定程度，问里面还有多少油
   使用定积分计算体积
*/
#include <bits/stdc++.h>
using namespace std;

double const EPS = 3E-3;
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

//计算定积分
double integral(double(*f)(double),double x1,double x2){
    double sum = 0.0;
    for(double x=x1;x<=x2;x+=EPS){
        sum += f(x);
    }
    return sum * EPS;
}

//计算弓形的高度，半径为r，高度为h
inline double area(double r, double h){
    if(is0(r)||sgn(h)<=0) return 0.0;
    if(sgn(h-r-r)>=0) return PI * r * r;
    double a = r - h;
    double theta = myacos(a/r);
    return (theta - 0.5 * sin(theta+theta)) * r * r;
}

double D;//球冠底面的直径
double L;//圆柱体的长度
double R,R2;//球冠的球的半径
double T;//倾斜以后,圆柱体母线的高度,即倾斜角就是arcsin(T/L)
double H;//剩下的油,其液面高度，是从圆柱体的底端开始计算
double Theta;
double hOfQiuque,xLeft,xRight,rOfYuanzhu;
double K,B;//y=kx+B;当k是INF表示x=B

//计算x处的横截面积，这是一个弓形
double f(double x){
    double r = rOfYuanzhu;
    if(x<0){
        r = sqrt(R2-(x-xLeft)*(x-xLeft));
    }else if(x>L){
        r = sqrt(R2-(x-xRight)*(x-xRight));
    }
    double y0 = K*x + B;
    if(isEq(K,INF)) y0 = (x<=B?INF:-INF);
    return area(r,y0+r-rOfYuanzhu);
}

double proc(){
    if(isEq(T,L)) K = INF, B = H;
    else Theta = asin(T/L), K = -tan(Theta), B = H / cos(Theta);

    rOfYuanzhu = 0.5 * D;
    xLeft = sqrt(R2-rOfYuanzhu*rOfYuanzhu);
    hOfQiuque = R - xLeft;
    xRight = L + hOfQiuque - R;
    return integral(f,-hOfQiuque,L+hOfQiuque);
}

int main(){
    freopen("damage.in","r",stdin);
    freopen("damage.out","w",stdout);
    //freopen("1.txt","r",stdin);
    while(5==scanf("%lf%lf%lf%lf%lf",&D,&L,&R,&T,&H)){
        R2 = R * R;
        printf("%.6f\n",proc()/1E6);
    }
    return 0;
}

