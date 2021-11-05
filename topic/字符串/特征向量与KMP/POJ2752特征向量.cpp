/*
    对给定P的每一个子串中找出：
        其前后缀相等的长度（如果为0则忽略）
    例如：
        输入：ala
		输出：1 3
*/
#include <stdio.h>
#include <string.h>
bool getNext(const char *P,int next[],int n){
    int i,k;
    next[0] = 0;
    for ( i=1;i<n;i++ ){
        k = next[i-1];
        while( k>0 && P[i]!=P[k]  )
            k = next[k-1];
        if ( P[i] == P[k] ) next[i] = k + 1;
        else next[i] = 0;
    }
    return true;
}
#define MAXSIZE 400002
char P[MAXSIZE];
int next[MAXSIZE];
int out[MAXSIZE];
int main(){
    while( scanf("%s",P)!=EOF ){
        int n = strlen(P);
        getNext(P,next,n);      /*求出特征向量*/
        int i=0,k=next[n-1];
        while( k != 0 ){        /*反向寻找*/
            out[i++] = k;
            k = next[k-1];       
        }
        for(;i>0;i--) printf("%d ",out[i-1]);
        printf("%d\n",n);
        
        memset(P,0,n);
        memset(next,0,n);
    }
    return 0;    
}
