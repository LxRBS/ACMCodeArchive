
#include <cstdio>
#include <algorithm>
using namespace std;

#define SIZE 505

typedef bool weight_t;

int N,M;//A��B�е������
int K;

weight_t G[SIZE][SIZE]; //����ͼ����
int L[SIZE];//L[i]ΪA����Biƥ��ĵ㣬Bi��δƥ����Ϊ0
bool F[SIZE];//F[i]��ʾBi�Ƿ���������·�ϣ���һ��������

void init(){
	for(int i=0;i<=N;++i)
		fill(G[i],G[i]+M+1,false);
	fill(L,L+M+1,0);
}

//dfsʵ���������㷨��nodeΪ�ڵ��ţ�A�еĽڵ�
bool dfs(int node){
	for(int i=1;i<=M;++i){
		//���û�б߻���������·��
		if ( !G[node][i] || F[i] ) continue;
		F[i] = true;

		//���Bi��δʹ�ù������Ϊ���߽����
		if ( 0 == L[i] ){
			L[i] = node;
			return true;
		}

		//���Bi�Ѿ�ʹ�ù�����ȥ�����������ӵ�A�еĵ�
		if ( dfs(L[i]) ){
			L[i] = node;//�൱�ڽ���
			return true;
		}
	}
	return false;
}

int Hungary(){
	int ret = 0;
	for(int i=1;i<=N;++i){
		fill(F+1,F+M+1,false);//ÿ��������Ҫ���
		if ( dfs(i) ) ++ret;
	}
	return ret;
}

bool read(){
	scanf("%d",&K);
	if ( 0 == K ) return false;

	scanf("%d%d",&N,&M);
	init();

	for(int i=0;i<K;++i){
		int a,b;
		scanf("%d%d",&a,&b);
		G[a][b] = true;
	}
	return true;
}

int main(){
	while( read() ) printf("%d\n",Hungary());
	return 0;
}
