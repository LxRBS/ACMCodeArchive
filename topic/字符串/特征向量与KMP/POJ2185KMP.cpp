/*
    ����һ���ַ������ҳ��ܹ�������С�����ε����
	���磺
	    ���룺ABABA
		      ABABA
	    �����2��һ��Ϊһ�����ڣ�
	�����������ݸо������⣡����
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
/*�����Լ��*/
inline int gcd(int a,int b){
    int c;
	while( c = a % b ){
		a = b;
		b = c;
	}
	return b;
}
/*����С������*/
inline int lcm(int a,int b){
	return a / gcd(a,b) * b;
}
#define  R_SIZE 10001
#define  C_SIZE 76

#define CLEAR_ADDR(addr) ( memset( (addr) , 0 , sizeof( (addr) ) ) )

char P[R_SIZE][C_SIZE];
char PCOL[C_SIZE][R_SIZE];
int next[R_SIZE];

int main(){
	int r,c;              /*r�С�c��*/
	int i,j;              /*ѭ������*/
	int rlcm,clcm;        /*����������������С������*/
	int k;                /*����λ��*/
	scanf("%d%d",&r,&c);
	for(i=0;i<r;i++) {
		scanf("%s",P[i]);
		for(j=0;j<c;j++) PCOL[j][i] = P[i][j];
		                  /*���б���*/
	}
	rlcm = 1;
	for(i=0;i<r;i++){
		getNext(P[i],next,c+1);
		k = c - next[c-1];     /*ĳһ�к��Ƶ�λ��*/
		rlcm = lcm(rlcm,k);    /*��С�����������⼸�п���һ����Ƶ���Сλ��*/
		CLEAR_ADDR(next);
		if ( rlcm >= c ){
			rlcm = c;
			break;
		}
	}	
	clcm = 1;
	for(i=0;i<rlcm;i++){       /*�����������е��У�ֻ��ǰrlcm�У���Ϊ���涼���ظ�*/
		getNext(PCOL[i],next,r+1);
		k = r - next[r-1];
		clcm = lcm(clcm,k);
		CLEAR_ADDR(next);
		if ( clcm >= r ){
			clcm = r;
			break;
		}
	}
	printf("%d",rlcm*clcm);
	return 0;
}
