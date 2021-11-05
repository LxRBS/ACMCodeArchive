#include <cstdio>
#include <climits>
#include <algorithm>
#include <queue>
using namespace std;

int const SIZE = 505;

typedef int capa_t;
typedef int cost_t;
int N,M;

//��
struct edge_t{
	int s;//���
	int e;//�յ�
	capa_t capa;//����
	cost_t cost;//����
	edge_t* next;
}Edge[SIZE*20];
int ECnt;

//ͼ
edge_t* Ver[SIZE];

void init(){
	ECnt = 0;
	fill(Ver,Ver+N+1,(edge_t*)0);
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
    int totalFlow = 0;

	while(1){
		spfa(s);
		//˵���Ҳ�������·
		if ( INT_MAX == D[t] ) break;

		//���¸�����
		for(edge_t*p=Pre[t];p;p=Pre[p->s]){
			p->capa -= 1;
			neg(p)->capa += 1;
		}

        //���·���
		miniCost += D[t];
		totalFlow += 1;

		if ( 2 == totalFlow ) break;
	}
	return miniCost;
}

bool read(){
    if ( EOF == scanf("%d%d",&N,&M) ) return false;

    init();

    for(int i=0;i<M;++i){
        int a,b,w1,w2;
        scanf("%d%d%d%d",&a,&b,&w1,&w2);
        mkEdge(a,b,1,w1);
        mkEdge(a,b,1,w1+w2);
    }

    return true;
}

int main(){
    for(int kase=1;read();++kase)
        printf("Case %d: %d\n",kase,mcmf(1,N));
    return 0;
}

