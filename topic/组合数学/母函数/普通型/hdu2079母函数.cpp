//典型的母函数，写对函数项，相乘即可

#include <string.h>
#include <iostream>
using namespace std;

int A[41],B[41];

int main(){
	int nofcase;
	scanf("%d",&nofcase);

	int score[9] = {0};
	while(nofcase--){
		memset(score,0,sizeof(score));
		memset(B,0,sizeof(B));
		memset(A,0,sizeof(A));
		
		int n,k;
		scanf("%d%d",&n,&k);
		for(int i=0;i<k;++i){
			int x,y;
			scanf("%d%d",&x,&y);
			score[x] = y;
		}

		for(int i=0;i<=score[1];++i)A[i] = 1;
		int sum = score[1];

		for(int ex=2;ex<=8;++ex){
			for(int i=0;i<=sum;++i)for(int k=0;k*ex+i<=n&&k<=score[ex];++k)
				B[i+k*ex] += A[i];

			sum += score[ex]*ex;
			if ( sum > n ) sum = n;
			for(int i=0;i<=sum;++i) A[i] = B[i], B[i] = 0;
		}

		printf("%d\n",A[n]);
	}
	return 0;
}
