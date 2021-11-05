#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

typedef int weight_t; 

#define SIZE 101

int N,M;

//�ߵĽṹ
struct edge_t{
	int node;
	weight_t w;//�����и�������
	edge_t* next;
}Edge[SIZE];
int ECnt;

//��������
int InDeg[SIZE];

//ͼ���ڽӱ�
edge_t* Ver[SIZE];

//���������
inline void mkEdge(int a,int b,weight_t w=0){
	++InDeg[b];
	Edge[ECnt].node = b;
	Edge[ECnt].w = w;
	Edge[ECnt].next = Ver[a];
	Ver[a] = Edge + ECnt ++;
}

//��ʼ��
inline void init(){
	ECnt = 0;
	fill(Ver,Ver+N,(edge_t*)0);
	fill(InDeg,InDeg+N,0);
}

//�������򣬷��ؿ����˵ĵ�ĸ���
int topoSort(){
	int ret = 0;

	//�������Ϊ0�ĵ�
	vector<int> vec;
	for(int i=0;i<N;++i)
		if ( 0 == InDeg[i] )
			vec.push_back(i);

	//����ÿһ�����Ϊ0�ĵ�
	while( !vec.empty() ){
		int u = vec.back();
		vec.pop_back();
		++ret;

		//��u��ÿһ������
		for(edge_t*p=Ver[u];p;p=p->next){
			int v = p->node;
			--InDeg[v];
			if ( 0 == InDeg[v] ) vec.push_back(v);
		}
	}
	
	return ret;
}

bool read(){
	scanf("%d%d",&N,&M);
	if ( 0 == N ) return false;
	
	init();
	for(int i=0;i<M;++i){
		int a,b;
		scanf("%d%d",&a,&b);
		mkEdge(a,b);
	}
	
	return true;
}

int main(){
	while( read() ){
		printf( topoSort() == N ? "YES\n" : "NO\n" );
	}
	return 0;
}