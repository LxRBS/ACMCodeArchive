/*
    һ��Բ̨����װ��ˮ
    ��֪ˮ�����V��Բ̨���¾�r���Ͼ�R�͸�H����խ�Ͽ�
    ��ˮ�ĸ߶�

    Բ̨�������ʽ��V = 1/3 Pi H ( r^2 + R^2 + rR )

    ��ˮ��Ϊh��ˮ��뾶Ϊx
    �� (r-x)/(r-R) = (H-h)/H
    �� x = r + h * (R-r)/H�����ʽ�Ӽ�ʹ��Բ������Ҳ����
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
