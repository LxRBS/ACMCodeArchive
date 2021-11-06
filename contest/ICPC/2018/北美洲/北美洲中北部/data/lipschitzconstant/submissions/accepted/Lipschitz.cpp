#include<stdio.h>
#include<algorithm>
using namespace std;
int n;
struct A {
    double x,y;
    bool operator <(const A &o)const {
     return x < o.x;
    }
}a[200222];
int main () {
    int i,j,k;
    double p,q,r;
    double t = -1.0;
    scanf("%d",&n);
    for(i=0;i<n;i++) {
        scanf("%lf %lf",&a[i].x,&a[i].y);
    }
    sort(a,a+n);
    /*for(i=0;i<n;i++) {
        printf("%lf %lf\n",a[i].x,a[i].y);
    }*/
    for(i=0;i<n-1;i++) {
        p = a[i+1].x - a[i].x;
        q = a[i+1].y - a[i].y;
        if(p < 0.0) p *= -1.0;
        if(q < 0.0) q *= -1.0;
        r = q/p;
        if(r > t) t = r;
    }
    printf("%lf",t);

    return 0;
}

/*
4 -10 6.342 -7 3 46 18.1 2 -34
*/
