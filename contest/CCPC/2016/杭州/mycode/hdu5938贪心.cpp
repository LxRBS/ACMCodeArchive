/*
    一串数字，分成5个部分，依次添加加减乘除4个操作
    问能够得到的最大数
    显然要减法后面的数尽可能的小
    乘法只要1位乘1位即可，除法可以有一位或者两位（可能有三位？）
    加法只有两种情况，第一位加剩下的，或者最后一位加剩下的
    这些当中最大的就是结果
*/
#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;

typedef long long int llt;
char S[110];

llt f(int idx,int jdx){
    llt ret = 0LL;
    for(char*p=S+idx;p!=S+jdx;++p){
        ret = ret*10LL + (*p-'0');
    }
    return ret;
}

//除数为一位
llt f1(){
    int n = strlen(S);
    llt e = S[n-1]-'0';
    llt d = S[n-2]-'0';
    llt c = S[n-3]-'0';
    llt tmp = c*d/e;
    //计算加和
    llt tt = f(0,n-4) + S[n-4]-'0';
    llt tt2 = *S-'0'+f(1,n-3);
    if(tt<tt2) tt=tt2;
    return tt-tmp;
}
//除数为两位
llt f2(){
    int n = strlen(S);
    llt e = f(n-2,n);
    llt d = S[n-3]-'0';
    llt c = S[n-4]-'0';
    llt tmp = c*d/e;
    //计算加和
    llt tt = f(0,n-5) + S[n-5]-'0';
    llt tt2 = *S-'0'+f(1,n-4);
    if(tt<tt2) tt=tt2;
    return tt-tmp;
}
//除数为三位
llt f3(){
int n = strlen(S);
    llt e = f(n-3,n);
    llt d = S[n-4]-'0';
    llt c = S[n-5]-'0';
    llt tmp = c*d/e;
    //计算加和
    llt tt = f(0,n-6) + S[n-6]-'0';
    llt tt2 = *S-'0'+f(1,n-5);
    if(tt<tt2) tt=tt2;
    return tt-tmp;
}
llt proc(){
    int n = strlen(S);

    llt t1 = f1();
    if(n<6) return t1;

    llt t2 = f2();
    if(n<7) return max(t1,t2);

    llt t3 = f3();
    return max(t1,max(t2,t3));
}
int main(){
    int nofkase;
    scanf("%d",&nofkase);
    for(int kase=1;kase<=nofkase;++kase){
        scanf("%s",S);
        printf("Case #%d: %I64d\n",kase,proc());
    }
    return 0;
}
