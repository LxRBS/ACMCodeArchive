/*
    �����ַ���P��һ���� P = a^n������a��ĳһ���ַ�����������n
	���磺
	    ���룺aaaa
		�����4
*/
#include <string>
#include <iostream>
#include <cstring>

using namespace std;

/*  
�����ģʽ����������
arg1��ģʽP��C char*����
arg2�������������飬�������������ڸ�������
arg3��ģʽP�ĳ��ȣ�Ҳ�����������������Ч����
*/
bool getNext(char const P[],int next[],int n){
	int i,k;
	next[0] = 0;
	for ( i=1;i<n;i++ ){
		k = next[i-1];
		while( k > 0 && P[i] != P[k]  )
			k = next[k-1];
		if ( P[i] == P[k] ) next[i] = k + 1;
		else next[i] = 0;
	}
	return true;
}

#define  SIZE 1000001
#define CLEAR_ADDR(addr) ( memset( (addr) , 0 , sizeof( (addr) ) ) )

char P[SIZE];
int next[SIZE];

int main(){
    int i;
	int len;
	int n;
	int k;
	while( scanf("%s",P) ){
		if ( P[0] == '.' && P[1] == 0 ) return 0;
		len = strlen(P);
		getNext(P,next,len+1);
        k = len - next[len-1];     /*����ܹ���ĳ�η��������λ�����ܱ���������*/
		if ( len % k == 0 ) printf("%d\n",len/k);
		else                printf("1\n");
	}
	return 0;
}
