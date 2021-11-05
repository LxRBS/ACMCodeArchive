/*
    给定n个开口向上的一元二次函数Si(x)
    令F(x) = max( Si(x) )
    求F(x)的最小值

    一元二次函数是凸函数，
    F(x)肯定也是凸函数，
    凸函数的极值使用三分搜索
*/

#include <stdio.h>
#include <math.h>
#include <iostream>
#include <iomanip>
using namespace std;

typedef double ldt;

ldt const EPS = 1E-9;

inline bool is0(ldt x){
    return -EPS <= x && x <= EPS;
}

int N;
ldt A[10010],B[10010],C[10010];

ldt f(ldt x){
    ldt ret = A[0] * x * x + B[0] * x + C[0];
    ldt t;
    for(int i=1;i<N;++i){
        t = A[i] * x * x + B[i] * x + C[i];
        if ( ret < t ) ret = t;
    }
    return ret;
}

ldt trinary(){
    ldt left = 0.0, right = 1000.0, m1, m2, t;
    do{
        t = ( right - left ) / 3.0;
        m1 = left + t; m2 = right - t;
        if ( f(m1) < f(m2) ) right = m2;
        else left = m1;
    }while( !is0(left-right) );
    return f(right);
}

int main(){
    //freopen("1.txt","r",stdin);
    int nofkase;
    scanf("%d",&nofkase);
    while(nofkase--){
        scanf("%d",&N);
        for(int i=0;i<N;++i)scanf("%lf%lf%lf",A+i,B+i,C+i);

        printf("%.4f\n",trinary());
    }
    return 0;
}
