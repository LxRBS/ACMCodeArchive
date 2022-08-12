/**
  在BZOJ上AC，在洛谷上有一个样例过不了。。。
  BZOJ的1337WA，不知何故，也许是精度问题
*/
#include <stdio.h>
#include <math.h>
#include <algorithm>
using namespace std;

/**最小覆盖圆*/

double const EPS = 1E-12;

//判断实数的符号
int sign(double x){
    if( x >= EPS ) return 1;
    return x <= -EPS ? -1 : 0;
}

struct point64f_t{
    double x,y;
};

//计算两点距离的平方
double dist2(point64f_t const&A,point64f_t const&B){
    double x = A.x - B.x;
    double y = A.y - B.y;
    return x*x+y*y;
}

//判断点p是否在圆O上，半径为r
bool isInCircle(point64f_t const&p,point64f_t const&O,double r){
    return sign( sqrt(dist2(p,O)) - r ) <= 0;
}

//过两点做圆
double mkCircle(point64f_t const&A,point64f_t const&B,point64f_t&O){
    O.x = (A.x+B.x)*0.5;
    O.y = (A.y+B.y)*0.5;
    return sqrt(dist2(A,B))*0.5;
}

//过三点做圆，根据外心性质解方程可得到公式
double mkCircle(point64f_t const&A,point64f_t const&B,point64f_t const&C,point64f_t&O){
    double a1 = (B.x-A.x) * 2.0;
    double b1 = (B.y-A.y) * 2.0;
    double nb = B.x*B.x+B.y*B.y;
    double c1 = nb -(A.x*A.x+A.y*A.y);
    double a2 = 2.0 * (C.x-B.x);
    double b2 = 2.0 * (C.y-B.y);
    double c2 = (C.x*C.x+C.y*C.y) - nb;
    O.x = ( c1*b2 - c2*b1 ) / ( a1*b2 - a2*b1 );
    O.y = ( a1*c2 - a2*c1 ) / ( a1*b2 - a2*b1 );
    return sqrt(dist2(O,A));
}

//最小覆盖圆,求点集P[n]的最小覆盖圆
//圆心在O，半径由函数返回
double miniCoverCircle(point64f_t P[],int n,point64f_t&O){
    random_shuffle(P,P+n);//随机打乱

    //初始圆即P[0]
    double radius = 0.0;
    O = P[0];

    for(int i=1;i<n;++i){
        if(isInCircle(P[i],O,radius)) continue;

        O = P[i];radius = 0.0;
        for(int j=0;j<i;++j){
            if(isInCircle(P[j],O,radius)) continue;

            radius = mkCircle(P[j],P[i],O);
            for(int k=0;k<j;++k){
                if(isInCircle(P[k],O,radius)) continue;
                radius = mkCircle(P[k],P[j],P[i],O);
            }
        }
    }
    return radius;
}

point64f_t P[100100];
int main(){
    //freopen("1.txt","r",stdin);
    int n;
    while(EOF!=scanf("%d",&n)){
        for(int i=0;i<n;++i)scanf("%lf%lf",&P[i].x,&P[i].y);
        point64f_t o;
        double r = miniCoverCircle(P,n,o);
        printf("%.10lf\n%.10lf %.10lf\n",r,o.x,o.y);
    }
    return 0;
}

