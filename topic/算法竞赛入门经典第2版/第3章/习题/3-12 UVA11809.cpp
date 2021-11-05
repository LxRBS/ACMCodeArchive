/*
    令a依次为0.5, 0.5 + 0.5^2, 0.5 + 0.5^2 + 0.5^3, 0.5 + ... + 0.5^10
    令b依次为2^(2^e-1)
    则log10(a*b) = log10(a)+(2^e-1)log10(2) = A.B
    则a*b = 10^0.B + 10^A
*/
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

double M[10][31];//M和E一共有300种可能，所以一次性算出所有的答案，然后去比对即可
int E[10][31];

//注意判断实数相等，必须使用精度
double const EPS = 1E-6;
inline bool is0(double x){return -EPS<x&&x<EPS;}

double const LOG10_2 = log10(2.0);

void init(){
    double a = 0.0, aa = 1.0;
    for(int m=0;m<=9;++m){
        a += aa *= 0.5;
        for(int e=1;e<=30;++e){
            double tmp = log10(a) + (double)((1<<e)-1)*LOG10_2;
            E[m][e] = (int)tmp;
            M[m][e] = pow(10.0,tmp-(int)tmp);
        }
    }
}

void f(double a,int b){
    for(int m=0;m<=9;++m)for(int e=1;e<=30;++e){
        if ( is0(a-M[m][e]) && b == E[m][e] ){
            printf("%d %d\n",m,e);
            return;
        }
    }
    printf("Never get here\n");
}

char A[110];
int main(){
    //freopen("1.txt","r",stdin);
    init();
    while(1){
        scanf("%s",A);
        //找到e的位置
        int k = 0;
        while(A[k]!='e') ++k;
        A[k] = '\0';

        double a = atof(A);   //atof就是把字符串转成double，字符串的内容必须正确，且以'\0'结尾
        int b = atoi(A+k+1);  //atoi就是把字符串转成int
        if ( 0==a && 0==b ) break;

        f(a,b);
    }
    return 0;
}