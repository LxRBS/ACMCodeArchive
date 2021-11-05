//最大子段和
#include <cstdio>

int N;
int A[100001];
int D[100001];//D[i]表示以A[i]结尾的最大子段和
bool F[100001];//表示D[i] = D[i-1] + A[i]，寻找位置使用
int main(){
	int nofkase;
	scanf("%d",&nofkase);
	for(int kase=1;kase<=nofkase;++kase){
		scanf("%d",&N);
		for(int i=0;i<N;++i)scanf("%d",A+i);
		
		int ret = A[0];
		int pos = 0;
		D[0] = A[0];
		F[0] = false;
		for(int i=1;i<N;++i){
			D[i] = D[i-1] >= 0 ? (F[i] = true,D[i-1] + A[i]) : (F[i] = false,A[i]);
			if ( ret < D[i] ) ret = D[i], pos = i;
		}
		//寻找位置
		int start = pos;
		while( F[start] ) --start;

		if ( kase > 1 ) printf("\n");
		printf("Case %d:\n",kase);
		printf("%d %d %d\n",ret,start+1,pos+1);
	}
	return 0;
}