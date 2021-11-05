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

double a;
double f(double x){
    return pow(x,a/x-x);
}
int main(){
    //freopen("1.txt","r",stdin);
    scanf("%lf",&a);
    if(a<0)printf("orz\n");
    else printf("%.5f\n",asr(f,1E-8,30.0,1E-10));
    return 0;
}
