/**
  给定A圆和B圆。
  等概率的放置一个正方形在平面上
  然后连续旋转正方形，问
  在正方形位于A内的条件下，正方形位于B内的概率
  就是两圆相交求面积的比例。
*/
#include <bits/stdc++.h>
using namespace std;

typedef double Real;
Real const PI = acos((Real)-1);
Real const EPS = 1E-9;
Real const SQRT2 = sqrt((Real)2) * (Real)0.5;

inline int sgn(Real x){return x>EPS?1:(x<-EPS?-1:0);}
inline Real myacos(Real x){
    if(sgn(x-1)>=0) return 0;
    if(sgn(x+1)<=0) return PI;
    return acos(x);
}

int R1,X1,Y1,R2,X2,Y2,A;

inline Real f(Real r, Real a){
    if(sgn(r-a*SQRT2)<=0) return 0;
    Real tmp = sqrt(r*r-a*a*0.25);
    return tmp - a * 0.5;
}

Real f(Real x1, Real y1, Real r1, Real x2, Real y2, Real r2){
    Real d = sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
    if(sgn(d-r1-r2)>=0) return 0;

    if(sgn(fabs(r1-r2)-d)>=0){
        if(sgn(r2-r1)>=0) return 1.0;
        return r2*r2/(r1*r1);
    }

    Real theta1 = myacos((r1*r1+d*d-r2*r2)/(2*r1*d));
    Real tmp1 = r1 * r1 * theta1;
    Real theta2 = myacos((r2*r2+d*d-r1*r1)/(2*r2*d));
    Real tmp2 = r2 * r2 * theta2;
    return (tmp1 + tmp2 - r1 * d * sin(theta1)) / (PI*r1*r1);
}

int main(){
    //freopen("1.txt","r",stdin);
    int nofkase;
    scanf("%d", &nofkase);
    while(nofkase--){
        scanf("%d%d%d%d%d%d%d",&R1,&X1,&Y1,&R2,&X2,&Y2,&A);
        Real r1p = f(R1,A);
        if(0==sgn(r1p)){
            while(1);
        }
        Real r2p = f(R2,A);
        if(0==sgn(r2p)){
            printf("0.000000\n");
            continue;
        }
        printf("%.6lf\n", f(X1,Y1,r1p,X2,Y2,r2p));
    }
    return 0;
}
