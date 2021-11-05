/**
    求整数的拆分数
*/
#include <cstdio>

#define SIZE 121

int A[SIZE],B[SIZE];

void init(){
	//初始化
	for(int i=0;i<=SIZE;++i) A[i] = 1, B[i] = 0;

	for(int i=2;i<=SIZE;++i){

		for(int j=0;j<=SIZE;++j)for(int k=0;k+j<=SIZE;k+=i) 
			B[j+k] += A[j];

		for(int j=0;j<=SIZE;++j){
			A[j] = B[j];
			B[j] = 0;
		}

	}
}

int main(){
	int n;
	init();
	while( EOF != scanf("%d",&n) )
		printf("%d\n",A[n]);

	return 0;
}
