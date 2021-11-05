/*
    ��һ��˫����У�ÿ�ο��Դ�ͷ��βȡ��һ��������a
    ��i��ȡ������������Ϊa*i
    ���������
*/
#include <cstdio>
#include <algorithm>
using namespace std;

int getUnsigned(){
	char ch = getchar();
	while( ch < '0' || ch > '9' ) ch = getchar();

	int ret = (int)(ch-'0');
	while( '0' <= ( ch = getchar() ) && ch <= '9' ) ret = ret * 10 + (int)(ch-'0');
	return ret;
}

int N;
int A[2010];
int D[2010][2010];//Dij��ʾ��ǰ����Ϊ[i,j]����õ�ֵ,��[1,N]��ʼ

void dp(){
    D[1][N] = 0;
    for(int i=2;i<=N;++i) D[i][N] = D[i-1][N] + ( i - 1 ) * A[i-1];

    for(int i=N-1;i>=1;--i) D[1][i] = D[1][i+1] + ( N - i ) * A[i+1];

    for(int i=2;i<N;++i){
        for(int j=N-1,r=i;j>=i;--j,++r){
            D[i][j] = max(D[i-1][j]+r*A[i-1],D[i][j+1]+r*A[j+1]);
        }
    }
}

int main(){
    N = getUnsigned();
    for(int i=1;i<=N;++i) A[i] = getUnsigned();

    dp();
    int r = 0;
    for(int i=1;i<=N;++i){
        int t = D[i][i] + N * A[i];
        if ( r < t ) r = t;
    }
    printf("%d\n",r);
    return 0;
}
