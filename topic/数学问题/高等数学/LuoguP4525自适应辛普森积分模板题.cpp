/**
   ����Ӧ����ɭ����ģ����
*/
#include <bits/stdc++.h>
using namespace std;

double simpson(double(*f)(double),double a,double b){
    double mid = ( a + b ) * 0.5;
    return (b-a)*(f(a)+f(b)+4.0*f(mid)) / 6.0;
}
//����Ӧ����ɭ���ֵĵݹ����
double asr(double(*f)(double),double a,double b,double eps,double ans){
    double mid = ( a + b ) * 0.5;
    double lans = simpson(f,a,mid);
    double rans = simpson(f,mid,b);
    //���ȹ�ֱ�ӷ���
    if(fabs(lans+rans-ans)<=eps) return ans;
    //���Ȳ����ݹ����
    return asr(f,a,mid,eps,lans) + asr(f,mid,b,eps,rans);
}
//����Ӧ����ɭ���֣�����[a, b]������eps��ԭ����f
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
