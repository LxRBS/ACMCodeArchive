/*
    一个圆台里面装了水
    已知水的体积V，圆台的下径r、上径R和高H，下窄上宽
    求水的高度

    圆台的体积公式：V = 1/3 Pi H ( r^2 + R^2 + rR )

    设水高为h，水面半径为x
    则 (r-x)/(r-R) = (H-h)/H
    则 x = r + h * (R-r)/H，这个式子即使在圆柱体下也成立
*/

#include <stdio.h>
#include <math.h>
#include <iostream>
#include <iomanip>
using namespace std;

typedef double ldt;

ldt const EPS = 1E-9;
ldt const PI = acos(-1.0);

inline bool is0(ldt x){
    return -EPS <= x && x <= EPS;
}

ldt r,R,H,V;
ldt f(ldt h){
    ldt x = r + (R-r)/H*h;
    return PI*h*( r*r + x*x + r*x )/3.0;
}

ldt proc(){
    ldt left = 0.0, right = H, mid;
    do{
        mid = ( left + right ) * 0.5;
        if ( f(mid) < V ) left = mid;
        else right = mid;
    }while(!is0(left-right));
    return left;
}
int main(){
    //freopen("1.txt","r",stdin);
    int nofkase;
    scanf("%d",&nofkase);
    while(nofkase--){
        scanf("%lf%lf%lf%lf",&r,&R,&H,&V);
        printf("%.6f\n",proc());
    }
    return 0;
}
