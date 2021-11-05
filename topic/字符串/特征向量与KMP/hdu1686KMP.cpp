#include <stdio.h>
#include <string.h>

int const SIZE = 1000000+10;

//求src的用于KMP匹配的特征向量，n为src的长度
void getKMPNext(char const src[],int n,int next[]){
    next[0] = -1;
    int i = 0, k = -1;
    while( i < n ){
        while( k >= 0 && src[i] != src[k] ) k = next[k];
        ++i, ++k;
        if ( i == n ) return;
        next[i] = src[i] == src[k] ? next[k] : k;
    }
}

//求P在T中出现的次数，可以重迭，next的长度要求是pn+1
int KMPCount(char const T[],int tn,char const P[],int pn,int const next[]){
    if ( pn > tn ) return 0;
    int tp = 0, pp = 0, ret = 0;
    while( tp < tn ){
        if ( -1 == pp || T[tp] == P[pp] ) ++tp, ++pp;
        else pp = next[pp];
        if ( pp == pn ){
            ++ret;
            pp = next[pn];
        }
    }
    return ret;
}

char A[SIZE],B[SIZE];
int Next[SIZE];

int main(){
    int n,kase;
    scanf("%d",&kase);
    while(kase--){
        scanf("%s%s",A,B);
        getKMPNext(A,n=strlen(A)+1,Next);
        printf("%d\n",KMPCount(B,strlen(B),A,n-1,Next));
    }
    return 0;
}
