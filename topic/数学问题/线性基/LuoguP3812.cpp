/*
    给定n个整数（数字可能重复），
    求在这些数中选取任意个，
    使得他们的异或和最大。

    首先求出这些数的线性基，
    即针对异或的最大线性无关
    然后利用这些基求最大值
*/
#include <stdio.h>
#include <algorithm>
using namespace std;

typedef long long int llt;

//判断value是否与b线性无关
//如果是，则value加入b，作为其中一个基
int _insertLB(llt value,llt b[],int siz){
    for(int i=siz-1;i>=0;--i){
        if(value&(1LL<<i)){
            if(!b[i]){//value是一个基
                b[i] = value;
                return 1;
            }
            value ^= b[i];
            //value可以由b中的若干基进行表达
            if(!value) return 0;
        }
    }
    return 0;
}

//建立线性基
//a是源数组，n是数量，b是结果,siz是最高位再加1
//返回基的数量
int buildLB(llt const a[],int n,llt b[],int siz){
    fill(b,b+siz,0LL);

    int cnt = 0;
    for(int i=0;i<n;++i){
        cnt += _insertLB(a[i],b,siz);
    }
    return cnt;
}

//给定线性基，求能够组成的最大数
llt max(llt const b[],int siz){
    llt ret = 0LL,tmp;
    for(int i=siz-1;i>=0;--i){
        if((tmp=ret^b[i])>ret){
            ret = tmp;
        }
    }
    return ret;
}

int N;
llt A[110],B[110];

int main(){
    //freopen("1.txt","r",stdin);
    scanf("%d",&N);
    for(int i=0;i<N;++i)scanf("%lld",A+i);

    buildLB(A,N,B,50);
    printf("%lld\n",max(B,50));
    return 0;
}
