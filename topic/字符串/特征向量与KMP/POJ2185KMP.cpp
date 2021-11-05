/*
    给定一个字符矩阵，找出能够填充的最小长方形的面积
	例如：
	    输入：ABABA
		      ABABA
	    输出：2（一行为一个周期）
	这道题测试数据感觉有问题！！！
*/
#include <string>
#include <iostream>
#include <cstring>

using namespace std;

/*  
求给定模式的特征向量
arg1：模式P，C char*类型
arg2：特征向量数组，特征向量保存在该数组中
arg3：模式P的长度，也是特征向量数组的有效长度
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
/*求最大公约数*/
inline int gcd(int a,int b){
    int c;
	while( c = a % b ){
		a = b;
		b = c;
	}
	return b;
}
/*求最小公倍数*/
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
	int r,c;              /*r行×c列*/
	int i,j;              /*循环变量*/
	int rlcm,clcm;        /*行列特征向量的最小公倍数*/
	int k;                /*后移位数*/
	scanf("%d%d",&r,&c);
	for(i=0;i<r;i++) {
		scanf("%s",P[i]);
		for(j=0;j<c;j++) PCOL[j][i] = P[i][j];
		                  /*按列保存*/
	}
	rlcm = 1;
	for(i=0;i<r;i++){
		getNext(P[i],next,c+1);
		k = c - next[c-1];     /*某一行后移的位数*/
		rlcm = lcm(rlcm,k);    /*最小公倍数就是这几行可以一起后移的最小位数*/
		CLEAR_ADDR(next);
		if ( rlcm >= c ){
			rlcm = c;
			break;
		}
	}	
	clcm = 1;
	for(i=0;i<rlcm;i++){       /*不必搜索所有的列，只需前rlcm列，因为后面都是重复*/
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
