#include <cstdio>
#include <queue>
#include <climits>
#include <algorithm>
using namespace std;

struct edge_t{
    int u;//�ڵ�
	int c;//����
	edge_t* next;
}Edge[40000];
int ECnt;
edge_t* Ver[201];

int N,M;
int L[201];//���ͼ

//����ߣ����Ǻ����������
inline edge_t* neg(edge_t* p){return Edge + ( ( p - Edge ) ^ 1 );}

//�������ͼ,sΪԴ�㣬tΪ���
bool bfs(int s,int t){
	fill(L,L+M+1,-1);
	queue<int> q;
	q.push(s);
	L[s] = 0;

	while( !q.empty() ){
		int u = q.front();
		q.pop();

		for(edge_t* p=Ver[u];p;p=p->next){
			int v = p->u;
			int c = p->c;
			if ( -1 == L[v] && c > 0 )
				q.push(v), L[v] = L[u] + 1;
		}
	}
	return -1 != L[t];
}
//�ڲ��ͼ����������·,cfΪ��ǰ�������t�ǻ��
int dfs(int u,int cf,int t){
	if ( u == t ) return cf;
      int tf = 0;//Ϊu����һ����ܿ�����
	for(edge_t*p=Ver[u];p;p=p->next){
		int v = p->u;
		int c = p->c;
		if ( L[u]+1==L[v] && c>0 && cf > tf ){
			int f = dfs(v,min(c,cf-tf),t);
		    if ( 0 == f ) continue;

			p->c -= f;//����߼�ȥ����
			neg(p)->c += f;//�����
                  tf += f;
		}
	}
      if ( 0 == tf ) L[u] = -1;//�޸Ĳ��ͼ��u��������
	return tf;
}
//Dinic�㷨
int Dinic(){
	int ret = 0;
	while( bfs(1,M) ){//��һ��bfs���ֲ�ͼ
		int res;//�ڶ���dfs�ڷֲ�ͼ����������·
		while( res = dfs(1,INT_MAX,M) )
			ret += res;
	}
	return ret;
}
void mkEdge(int s,int e,int c){
	Edge[ECnt].u = e;
	Edge[ECnt].c = c;
	Edge[ECnt].next = Ver[s];
	Ver[s] = Edge + ECnt ++;

	Edge[ECnt].u = s;
	Edge[ECnt].c = 0;
	Edge[ECnt].next = Ver[e];
	Ver[e] = Edge + ECnt ++;
}
bool read(){
	if ( EOF == scanf("%d%d",&N,&M) )return false;
	
	fill(Ver,Ver+N+1,(edge_t*)0);
	ECnt = 0;
	
	for(int i=0;i<N;++i){
        int s,e,c;
		scanf("%d%d%d",&s,&e,&c);
		mkEdge(s,e,c);
	}
	return true;
}
int main(){
	while( read() ) printf("%d\n",Dinic());
	return 0;
}