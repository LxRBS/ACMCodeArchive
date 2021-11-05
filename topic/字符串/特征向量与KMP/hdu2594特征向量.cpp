/*
    给定字符串A、B，求最长的子串
    既是A的前缀又是B的后缀    
*/
#include <cstdio>
#include <cstring>

//求src的特征向量，n为src的长度
void getNext(char const src[],int n,int next[]){
    next[0] = 0;
    for(int i=1;i<n;++i){
        int k = next[i-1];
        while( k > 0 && src[i] != src[k] ) k = next[k-1];
        next[i] = src[i] == src[k] ? k + 1 : 0;
    }
}

char A[100010],B[50010];
int Next[100010];

int main(){
    while( EOF != scanf("%s%s",A,B) ){
        int n = strlen(A);
        A[n++] = '#';
        for(char*p=B;*p;++p) A[n++] = *p;
        A[n] = '\0';

        getNext(A,n,Next);
        A[Next[n-1]] = '\0';
        if ( Next[n-1] ) printf("%s ",A);
        printf("%d\n",Next[n-1]);
    }
    return 0;
}
