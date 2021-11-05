/*
    给定一个字符串，问每个前缀能否表示成某个字符串的K次方
    输出前缀的长度和K
*/
#include <stdio.h>
#include <string.h>

int const SIZE = 1000000+10;

//求特征向量
void getNext(char const src[],int n,int next[]){
    next[0] = 0;
    for(int i=1;i<n;++i){
        int k = next[i-1];
        while( k > 0 && src[i] != src[k] ) k = next[k-1];
        next[i] = src[i] == src[k] ? k + 1 : 0;
    }
}

char A[SIZE];
int Next[SIZE];
int main(){
    int n;
    for(int kase=1;;++kase){
        scanf("%d",&n);
        if ( 0 == n ) break;
        scanf("%s",A);

        printf("Test case #%d\n",kase);
        getNext(A,n,Next);
        for(int i=2;i<=n;++i){
            if ( 0 == i % ( i - Next[i-1] ) && i/(i-Next[i-1])>1 ){
                printf("%d %d\n",i,i/(i-Next[i-1]));
            }
        }
        printf("\n");
    }
    return 0;
}
