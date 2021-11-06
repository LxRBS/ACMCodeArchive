/**
   给一个字符串，问是否能够分割为若干长度大于1的循环同构的子串
   首先必然是约数，然后对每个约数检查循环同构即可
   暴力法
*/
//#include <bits/stdc++.h>
#include <stdio.h>
using namespace std;

typedef long long llt;

//线性筛法
int const SIZE = 5000010;//一般只筛到30000+即可
bool isComp[SIZE] = {false};//isComp[i]为真说明i是合数
int P[SIZE];//P[i]为第i个素数，i从0开始
int PCnt = 0;//PCnt记录1~SIZE之间的素数的个数
void sieve(){
    for(int i=2;i<SIZE;++i){
        if ( !isComp[i] ) P[PCnt++] = i;

        for(int j=0;j<PCnt&&(llt)i*P[j]<SIZE;++j){
            isComp[i*P[j]] = true;
            if ( 0 == i % P[j] ) break;
        }
    }
}

int N;
char A[SIZE];

bool checkSingle(){
    char const *p = A + 1;
    while(*p)if(*p!=*A)return false;else ++p;
    return true;
}

//检查[start1,len+start1)与[start2,len+start2)是否为循环同构
bool check(int start1,int start2,int len){
    int n1 = start1 + len;
    int n2 = start2 + len;
    int i = 0, j = 0;
    int k = 0;
    while(i<n1&&j<n2){
        while(A[start1+(i+k)%len]==A[start2+(j+k)%len]&&k<len) ++k;
        if(k==len) return true;
        if(A[start1+(i+k)%len]>A[start2+(j+k)%len]) i += k + 1;
        else j += k + 1;
        k = 0;
    }
    return false;
}

//检查是否存在k-同构
bool check(int k){
    for(int i=k;i<N;i+=k){
        if(!check(0,i,k)) return false;
    }
    return true;
}

bool proc(){
    if(1==N) return false;
    if(2==N) return *A == *(A+1);
    if(checkSingle()) return true;
    if(!isComp[N]) return false;

    int nn = N;
    for(llt i=2;i*i<=N;++i){
        if(N%i==0){
            if(check(i)) return true;
            if(check(N/i)) return true;
        }
    }
    return false;
}

int main(){
    //freopen("1.txt","r",stdin);
    sieve();
    int nofkase;
    scanf("%d",&nofkase);
    while(nofkase--){
        scanf("%d%s",&N,A);
        puts(proc()?"Yes":"No");
    }
    return 0;
}
