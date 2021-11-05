/*
    对给定P的每一个子串，问：是否为周期串，并给出反复的次数
	例如：
	    输入：aaa
		输出：2 2
		      3 3
     意思是P的长度为2的子串是周期串，并且有2个周期；后面同理。
*/
#include <string>
#include <iostream>
#include <stdio.h>
using namespace std;
#define MAXSIZE 1000002
char P[MAXSIZE];
int next[MAXSIZE];
/*
 * arg 1: P is the pattern
 * arg 2: next is the array to keep eigenvector
 * arg 3: n is the length of P
 */
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

int main(){
    int N;
    int no=0;
    scanf("%d",&N);
    while( N ){
        no++;
        printf("Test case #%d\n",no);
        scanf("%s",P);
        getNext(P,next,N+1);
        int i,k;
        for(i=2;i<=N;i++){
            k = i - next[i-1];    
			/*如果是周期串，则后移的位数恰好能被整串长度整除*/
            if ( i%k==0 && i/k!=1)
                printf("%d %d\n",i,i/k);
        }
        printf("\n");
        memset(P,0,N);
        memset(next,0,N);
        scanf("%d",&N);
    }
    return 1;
}

