/*
    ��a����Ϊ0.5, 0.5 + 0.5^2, 0.5 + 0.5^2 + 0.5^3, 0.5 + ... + 0.5^10
    ��b����Ϊ2^(2^e-1)
    ��log10(a*b) = log10(a)+(2^e-1)log10(2) = A.B
    ��a*b = 10^0.B + 10^A
*/
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

double M[10][31];//M��Eһ����300�ֿ��ܣ�����һ����������еĴ𰸣�Ȼ��ȥ�ȶԼ���
int E[10][31];

//ע���ж�ʵ����ȣ�����ʹ�þ���
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
        //�ҵ�e��λ��
        int k = 0;
        while(A[k]!='e') ++k;
        A[k] = '\0';

        double a = atof(A);   //atof���ǰ��ַ���ת��double���ַ��������ݱ�����ȷ������'\0'��β
        int b = atoi(A+k+1);  //atoi���ǰ��ַ���ת��int
        if ( 0==a && 0==b ) break;

        f(a,b);
    }
    return 0;
}