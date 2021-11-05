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
