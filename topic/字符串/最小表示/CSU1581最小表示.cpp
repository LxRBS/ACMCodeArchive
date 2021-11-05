#include <cstdio>
#include <algorithm>
using namespace std;

void dispArray(int const a[],int n){
	for(int i=0;i<n;++i)printf("%d ",a[i]);
	printf("\n");
}

#define SIZE 200005
int A[SIZE],B[SIZE];
int N;

inline int tr(int t){return t%N;}
//最小表示
bool miniPre(){
    int ia = 0;
    int ib = 0;
    int k = 0;
    while(1){
    	while( k < N && A[tr(ia+k)]==B[tr(ib+k)] ) ++k;
    	if ( k == N ) return true;
    	if ( A[tr(ia+k)] > B[tr(ib+k)] ) ia += k + 1;
    	else ib += k + 1;
    	if ( ia >= N || ib >= N ) return false;
    	k = 0;
    }
    return false;
}
int main(){
	while( EOF != scanf("%d",&N) ){
		for(int i=0;i<N;++i)scanf("%d",A+i);
		for(int i=0;i<N;++i)scanf("%d",B+i);
		sort(A,A+N);
		sort(B,B+N);

		int t = A[0];
		for(int i=0;i<N-1;++i){
			A[i] -= A[i+1];
			if ( A[i] < 0 ) A[i] += 360000;
		}
		A[N-1] -= t;
		if ( A[N-1] < 0 ) A[N-1] += 360000;

		t = B[0];
		for(int i=0;i<N-1;++i){
			B[i] -= B[i+1];
			if ( B[i] < 0 ) B[i] += 360000;
		}
		B[N-1] -= t;
		if ( B[N-1] < 0 ) B[N-1] += 360000;

		//dispArray(A,N);dispArray(B,N);
        printf(miniPre()?"possible\n":"impossible\n");
	}
	return 0;
}

