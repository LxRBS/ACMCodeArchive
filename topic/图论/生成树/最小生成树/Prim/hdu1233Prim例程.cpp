#include <cstdio>
#include <algorithm>
using namespace std;

typedef int weight_t; 

#define SIZE 101

int N;

//ͼ���ڽӾ���
weight_t Graph[SIZE][SIZE];

//�����㵽�м�������̾��룬ʼ��ά��
weight_t D[SIZE];

//��־λ
bool Flag[SIZE];

//Prim�㷨������MST�ĳ���
weight_t Prim(){
	//��ʼ������
	fill(D,D+SIZE,INT_MAX);
	fill(Flag,Flag+SIZE,false);

	//��ʼ����һ������ĵ�
	D[1] = 0;

	weight_t ans = 0;

	for(int i=1;i<=N;++i){
		//�ҳ������м�������ĵ�
		int k = -1;
		for(int j=1;j<=N;++j)
			if ( !Flag[j] && ( -1 == k || D[j] < D[k] ) )
				k = j;

		//��k������м���
		Flag[k] = true;
		ans += D[k];

		//����ʣ��㵽�м�������̾���
		for(int j=1;j<=N;++j)
			if ( !Flag[j] && Graph[k][j] < D[j] )
				D[j] = Graph[k][j];
	}

	return ans;
}

bool read(){
	scanf("%d",&N);
	if ( 0 == N ) return false;
	
	for(int i=0;i<N*(N-1)/2;++i){
		int a,b,w;
		scanf("%d%d%d",&a,&b,&w);
		Graph[a][b] = Graph[b][a] = w;
	}
	
	return true;
}

int main(){
	while( read() ){
		printf("%d\n",Prim());
	}
	return 0;
}