#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
#define SIZE 205

typedef int weight_t;

int N,M;

//�ߵĽṹ
struct edge_t{
	int node;
	weight_t c;//cΪ����
	edge_t* next;
	edge_t* redge;//ָ�����
}Edge[SIZE*2];
int ECnt;

//ͼ���ڽӱ�
edge_t* Ver[SIZE];

void init(){
	ECnt = 0;
	fill(Ver+1,Ver+M+1,(edge_t*)0);
}

//����˫���
void mkEdge(int a,int b,weight_t c){
	int t1 = ECnt++;
	int t2 = ECnt++;

	Edge[t1].node = b;
	Edge[t1].c = c;
	Edge[t1].next = Ver[a];
	Edge[t1].redge = Edge + t2;
	Ver[a] = Edge + t1;

	Edge[t2].node = a;
	Edge[t2].c = 0;
	Edge[t2].next = Ver[b];
	Edge[t2].redge = Edge + t1;
	Ver[b] = Edge + t2;
}

int L[SIZE];//���ͼ

//�������������Դs����t�Ĳ��ͼ
bool bfs(int s,int t){
	fill(L+1,L+M+1,-1);
	vector<int> q;
	q.push_back(s);
	L[s] = 0;

	while( !q.empty() ){
		int u = q.back();
		q.pop_back();
		
		//Ѱ�һ��в����ı�
		for(edge_t*p=Ver[u];p;p=p->next){
			if ( p->c <= 0 ) continue;

			int v = p->node;
			if ( -1 != L[v] ) continue;

			q.push_back(v);
			L[v] = L[u] + 1;
		}
	}

	return -1 != L[t];
}

//�ڲ��ͼ����������·���������Ͼ��������������������
//��������Ǹ���֮����������Сֵ
//uΪ��ǰ�ڵ㣬cfΪ�Ѿ��������Ľ����tΪ���
int dfs(int u,int cf,int t){
	if ( u == t ) return cf;

	int tf = 0;//tf��¼u����һ����ܿ�������
	for(edge_t*p=Ver[u];p;p=p->next){
		int v = p->node;
		weight_t c = p->c;

		if ( L[u] + 1 == L[v] && c > 0 && cf > tf ){
			int f = dfs(v,min(c,cf-tf),t);
			if ( 0 == f ) continue;

			p->c -= f;//����߼�ȥ��������
			p->redge->c += f;//����߼���
			tf += f;
		}
	}
	if ( 0 == tf ) L[u] = -1;//�޸Ĳ��ͼ
	return tf;
}

//Dinic�㷨��sΪԴ��tΪ��
int Dinic(int s,int t){
	int ret = 0;
	while( bfs(s,t) ){//��һ�������ֲ�ͼ
		int ans;
		//�ڶ����ڷֲ�ͼ�ϲ���һ������·���Ŀ�������
		while( ans = dfs(s,INT_MAX,t) )
			ret += ans;
	}
	return ret;
}

bool read(){
	if ( EOF == scanf("%d%d",&N,&M) )
		return false;

	init();
	for(int i=0;i<N;++i){
		int a,b,c;
		scanf("%d%d%d",&a,&b,&c);
		mkEdge(a,b,c);
	}
	return true;
}

int main(){
	while( read() )
		printf("%d\n",Dinic(1,M));
	return 0;
}