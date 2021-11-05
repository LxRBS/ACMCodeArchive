#include <iostream>
using namespace std;

#define SIZE 301

int A[SIZE],B[SIZE];

void init(){
	for(int i=0;i<=SIZE;++i)A[i]=1,B[i]=0;
	for(int i=2;i<=SIZE;++i){
		for(int j=0;j<=SIZE;++j)for(int k=0;k+j<=SIZE;k+=i*i)
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
	while( scanf("%d",&n) && n )
		printf("%d\n",A[n]);
	
	return 0;
}
