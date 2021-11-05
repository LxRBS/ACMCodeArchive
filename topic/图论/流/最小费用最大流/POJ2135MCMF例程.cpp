//����һ������ͼ��Ҫ��1�㵽N���ٷ���1�㣬ÿ���������һ�Σ��������Ҫ�߶�Զ
//��Ŀ������N���㡢M����, �ߵ�������Ϊ1 
//���һ��Դ������1�㡢����Ϊ2
//���һ����, N�㵽�㣬����Ϊ2 
#include <cstdio>
#include <queue>
#include <algorithm>
using namespace std;

typedef int capa_t;
typedef int cost_t;

#define SIZE 1010

int N,M;

//��
struct edge_t{
	int s;//���
	int e;//�յ�
	capa_t capa;//����
	cost_t cost;//����
	edge_t* next;
}Edge[SIZE*40];
int ECnt;

//ͼ
edge_t* Ver[SIZE];

void init(){
	ECnt = 0;
	fill(Ver,Ver+N+2,(edge_t*)0);
}
//������
void mkEdge(int a,int b,capa_t capa,cost_t cost){
	Edge[ECnt].s = a;
	Edge[ECnt].e = b;
	Edge[ECnt].capa = capa;
	Edge[ECnt].cost = cost;
	Edge[ECnt].next = Ver[a];
	Ver[a] = Edge + ECnt ++;

	Edge[ECnt].s = b;
	Edge[ECnt].e = a;
	Edge[ECnt].capa = 0;
	Edge[ECnt].cost = -cost;
	Edge[ECnt].next = Ver[b];
	Ver[b] = Edge + ECnt ++;
}

inline edge_t* neg(edge_t* p){
	return Edge + ( ( p - Edge ) ^ 1 );
}

cost_t D[SIZE];
bool Flag[SIZE];
edge_t* Pre[SIZE];//�ߣ�ͨ����������Ի�ԭ���·��
//SPFA�㷨��ʹ��cost��ΪȨֵ���������·��
void spfa(int s){
	fill(D,D+N+2,INT_MAX);
	fill(Flag,Flag+N+2,false);
	fill(Pre,Pre+N+2,(edge_t*)0);

	D[s] = 0;
	Flag[s] = true;

	queue<int> q;
	q.push(s);

	while( !q.empty() ){
		int u = q.front();
		q.pop();
		Flag[u] = false;

		for(edge_t*p=Ver[u];p;p=p->next){
			if ( p->capa <= 0 ) continue;
			int v = p->e;
			cost_t tmp = D[u] + p->cost;
			if ( tmp < D[v] ){
				D[v] = tmp;
				Pre[v] = p;
				if ( !Flag[v] )
					q.push(v), Flag[v] = true;
			}
		}
	}
}

//��С�����������sΪԴ��tΪ��
int mcmf(int s,int t){
    int miniCost = 0;

	while(1){
		spfa(s);
		//˵���Ҳ�������·
		if ( INT_MAX == D[t] ) break;

		//�ҳ�������·�Ŀ�����
		int flow = INT_MAX;
		for(edge_t*p=Pre[t];p;p=Pre[p->s])
			if ( flow > p->capa )
				flow = p->capa;

		//���¸�����
		for(edge_t*p=Pre[t];p;p=Pre[p->s]){
			p->capa -= flow;
			neg(p)->capa += flow;
		}

            //���·���
		miniCost += D[t] * flow;
	}
	return miniCost;
}

bool read(){
	if ( EOF == scanf("%d%d",&N,&M) )
		return false;

	init();
	for(int i=0;i<M;++i){
		int a,b,c;
		scanf("%d%d%d",&a,&b,&c);
		mkEdge(a,b,1,c);
		mkEdge(b,a,1,c);
	}
    //����Դ��1�ı�
	mkEdge(0,1,2,0);
	//����N����ı�
	mkEdge(N,N+1,2,0);

	return true;
}

int main(){
	while( read() )
		printf("%d\n",mcmf(0,N+1));
	return 0;
}
