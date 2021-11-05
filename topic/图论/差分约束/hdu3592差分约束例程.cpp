#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

typedef int weight_t; 

#define SIZE 1005

int N,X,Y;

//�ߵĽṹ
struct edge_t{
	int node;
	weight_t w;
	edge_t* next;
}Edge[SIZE*21];
int ECnt;

//ͼ���ڽӱ�
edge_t* Ver[SIZE];

//���������
inline void mkEdge(int a,int b,weight_t w){
	Edge[ECnt].node = b;
	Edge[ECnt].w = w;
	Edge[ECnt].next = Ver[a];
	Ver[a] = Edge + ECnt ++;
}

//��ʼ��
inline void init(){
	ECnt = 0;
	fill(Ver,Ver+N+1,(edge_t*)0);
}

//���·�Ľ��
weight_t D[SIZE];

//��־λ
bool Flag[SIZE];

//��Ӵ���
int Cnt[SIZE];

//�ɼ�鸺����SPFA��sΪԴ
bool spfa(int s){
	//��ʼ������
	fill(D,D+N+1,INT_MAX);
	fill(Flag,Flag+N+1,false);
	fill(Cnt,Cnt+N+1,0);

	//��ʼ��Դ
	D[s] = 0;
	Flag[s] = true;
	Cnt[s] = 1;

	vector<int> q;
	q.push_back(s);

	while( !q.empty() ){
		int u = q.back();
		q.pop_back();
		Flag[u] = false;

		//��u��ÿһ������
		for(edge_t*p=Ver[u];p;p=p->next){
			int v = p->node;
			weight_t tmp = D[u] + p->w;
			if ( tmp < D[v] ){
				D[v] = tmp;
				if ( !Flag[v] )
					Flag[v] = true, q.push_back(v), ++Cnt[v];
				//��ͼ����N+1����
				if ( Cnt[v] > N + 1 ) return false;
			}
		}
	}
	return true;
}

void read(){
	scanf("%d%d%d",&N,&X,&Y);
	
	init();

	//�൱�ڲ���ʽb-a<=c
	for(int i=0;i<X;++i){
		int a,b,c;
		scanf("%d%d%d",&a,&b,&c);
		mkEdge(a,b,c);
	}

	//�൱�ڲ���ʽb-a>=c����a-b<=-c
	for(int i=0;i<Y;++i){
		int a,b,c;
		scanf("%d%d%d",&a,&b,&c);
		mkEdge(b,a,-c);
	}

	//����0�㵽�����ڵ�ı�
	for(int i=1;i<=N;++i)
		mkEdge(0,i,0);
	
	return;
}

int main(){
	int nofkase;
	scanf("%d",&nofkase);
	while( nofkase-- ){
		read();
		if ( spfa(1) ){
			if ( INT_MAX == D[N] ) printf("-2\n");
			else printf("%d\n",D[N]);
		}else{//���ڸ���������ʽ���޽�
			printf("-1\n");
		}
	}
	return 0;
}