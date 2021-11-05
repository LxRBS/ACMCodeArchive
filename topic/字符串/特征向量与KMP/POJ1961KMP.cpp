/*
    �Ը���P��ÿһ���Ӵ����ʣ��Ƿ�Ϊ���ڴ��������������Ĵ���
	���磺
	    ���룺aaa
		�����2 2
		      3 3
     ��˼��P�ĳ���Ϊ2���Ӵ������ڴ���������2�����ڣ�����ͬ��
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
			/*��������ڴ�������Ƶ�λ��ǡ���ܱ�������������*/
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

