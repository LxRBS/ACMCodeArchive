/**
   һ���͹ޣ���������ڣ��м���Բ����
   �ֽ�����бһ���̶ȣ������滹�ж�����
   ʹ�ö����ּ������
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

//���㶨����
double integral(double(*f)(double),double x1,double x2){
    double sum = 0.0;
    for(double x=x1;x<=x2;x+=EPS){
        sum += f(x);
    }
    return sum * EPS;
}

//���㹭�εĸ߶ȣ��뾶Ϊr���߶�Ϊh
inline double area(double r, double h){
    if(is0(r)||sgn(h)<=0) return 0.0;
    if(sgn(h-r-r)>=0) return PI * r * r;
    double a = r - h;
    double theta = myacos(a/r);
    return (theta - 0.5 * sin(theta+theta)) * r * r;
}

double D;//��ڵ����ֱ��
double L;//Բ����ĳ���
double R,R2;//��ڵ���İ뾶
double T;//��б�Ժ�,Բ����ĸ�ߵĸ߶�,����б�Ǿ���arcsin(T/L)
double H;//ʣ�µ���,��Һ��߶ȣ��Ǵ�Բ����ĵ׶˿�ʼ����
double Theta;
double hOfQiuque,xLeft,xRight,rOfYuanzhu;
double K,B;//y=kx+B;��k��INF��ʾx=B

//����x���ĺ�����������һ������
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

