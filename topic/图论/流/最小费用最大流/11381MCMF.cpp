#include <cstdio>
#include <queue>
#include <algorithm>
using namespace std;

struct edge_t{
	int u,v;//����ߵ������˵�
	int capa,cost;//����������
	edge_t* next;
}Edge[30000];
int ECnt;

edge_t* Ver[2005];

//��ȡ�����
inline edge_t* neg(edge_t* p){
	return Edge + ( ( p - Edge ) ^ 1 );
}

//������
void mkEdge(int a,int b,int capa,int cost){
	Edge[ECnt].u = a;
	Edge[ECnt].v = b;
	Edge[ECnt].capa = capa;
	Edge[ECnt].cost = cost;
	Edge[ECnt].next = Ver[a];
	Ver[a] = Edge + ECnt ++;

	Edge[ECnt].u = b;
	Edge[ECnt].v = a;
	Edge[ECnt].capa = 0;
	Edge[ECnt].cost = -cost;
	Edge[ECnt].next = Ver[b];
	Ver[b] = Edge + ECnt ++;
}
int N,M;
void init(){
	ECnt = 0;
	fill(Ver,Ver+N+N+2,(edge_t*)0);
}

bool read(){
	if ( EOF == scanf("%d%d",&N,&M) ) return false;
	init();
	//ÿ���ڵ�һ��Ϊ2
	for(int i=2;i<N;++i){
		mkEdge(i+i-1,i+i,1,0);//����Ϊ1��ȷ��ÿ����ֻ��ѡ��1��
	}
	mkEdge(1,2,2,0);
	mkEdge(N+N-1,N+N,2,0);//��㡢�յ�����Ϊ2��ȷ���ܹ�ѡ��2��·��
	mkEdge(0,1,2,0);
	mkEdge(N+N,N+N+1,2,0);//�����µ������յ�
	for(int i=0;i<M;++i){
		int a,b,c;
		scanf("%d%d%d",&a,&b,&c);
		//��a��b������Ϊ1��ȷ��ÿ����ֻ��ѡ��1��
		mkEdge(a+a,b+b-1,1,c);
	}
	return true;
}

//��costΪȨֵѰ�ҿ������·��
int D[2005];
bool Flag[2005];
edge_t* Pre[2005];//��¼���·��
void spfa(int s){
	fill(D,D+N+N+2,INT_MAX);
	fill(Flag,Flag+N+N+2,false);
	fill(Pre,Pre+N+N+2,(edge_t*)0);

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
			int v = p->v;
			int t = D[u] + p->cost;
			if ( t < D[v] ){
				D[v] = t;
				Pre[v] = p;
				if ( !Flag[v] ) q.push(v),Flag[v] = true;
			}
		}
	}
}

//��С���������
int mcmf(int s,int t){
	int ret = 0;
	while(1){
		spfa(s);
		if ( INT_MAX == D[t] ) return ret;

		/*//�ҳ�������·�Ŀ��������˴�һ����1
		int flow = INT_MAX;
		for(edge_t*p=Pre[t];p;p=Pre[p->u])
			if ( flow > p->capa )
				flow = p->capa;
		//*/
		
		int flow = 1;
		//��������
		for(edge_t*p=Pre[t];p;p=Pre[p->u]){
			p->capa -= flow;
			neg(p)->capa += flow;
		}

		//���·���
		ret += D[t] * flow;
	}
}

int main(){
	while( read() ) printf("%d\n",mcmf(0,N+N+1));
	return 0;
}