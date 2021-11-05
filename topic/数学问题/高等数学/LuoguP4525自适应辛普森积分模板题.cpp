/**
   自适应辛普森积分模板题
*/
#include <bits/stdc++.h>
using namespace std;

double simpson(double(*f)(double),double a,double b){
    double mid = ( a + b ) * 0.5;
    return (b-a)*(f(a)+f(b)+4.0*f(mid)) / 6.0;
}
//自适应辛普森积分的递归调用
double asr(double(*f)(double),double a,double b,double eps,double ans){
    double mid = ( a + b ) * 0.5;
    double lans = simpson(f,a,mid);
    double rans = simpson(f,mid,b);
    //精度够直接返回
    if(fabs(lans+rans-ans)<=eps) return ans;
    //精度不够递归调用
    return asr(f,a,mid,eps,lans) + asr(f,mid,b,eps,rans);
}
//自适应辛普森积分，区间[a, b]，精度eps，原函数f
double asr(double (*f)(double),double a,double b,double eps){
    return asr(f,a,b,eps,simpson(f,a,b));
}


double a,b,c,d,L,R;
double f(double x){
    return (c*x+d)/(a*x+b);
}
int main(){
    scanf("%lf%lf%lf%lf%lf%lf",&a,&b,&c,&d,&L,&R);
    printf("%.6f\n",asr(f,L,R,1E-10));
    return 0;
}
