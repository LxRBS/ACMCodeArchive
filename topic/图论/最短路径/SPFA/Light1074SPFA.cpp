/*
    ÿ������һ��Ȩֵ
    ����֮��ı�ȨֵΪ�������

    �ʴ�1��q�����̾���
    �����̾�������������̻���С��3���߲��ɴ����ʺ�
    
    ����Ҫ�и���
    ���Ҫע��������޼��̵ĵ�δ���ڸ�����
    �����ĺ�̶��������޼���
    ����ҵ�һ�������������
*/

#include <stdio.h>
#include <vector>
#include <queue>
using namespace std;

//type of edge's weight
typedef int weight_t;

//just as its names
int const SIZE_OF_VERTICES = 300;
int const SIZE_OF_EDGES = 50000;
weight_t const INF = 1000000000;

struct edge_t{
	int from,to;
	weight_t weight;
	int next;//Index of the array is used as pointers, ZERO means NULL
}Edge[SIZE_OF_EDGES];
int ECnt;
int Vertex[SIZE_OF_VERTICES];

//Don't forget calling it
//n is the amount of vertices
inline void initGraph(int n){
	ECnt = 1;
	fill(Vertex,Vertex+n+1,0);
}

//to build unidirectional edge
inline void mkEdge(int a,int b,weight_t w=weight_t()){
	Edge[ECnt].from = a;
	Edge[ECnt].to = b;
	Edge[ECnt].weight = w;
	Edge[ECnt].next = Vertex[a];
	Vertex[a] = ECnt ++;
}

//���u�Ǹ����ϵĵ㣬�������к�̶��������޼���
bool Neg[SIZE_OF_VERTICES];
void dfs(int u){
    Neg[u] = true;
    for(int p=Vertex[u];p;p=Edge[p].next)if(!Neg[Edge[p].to])dfs(Edge[p].to);
}

//s is the source id
//vn is the amount of vertices, all vertices are indexed from 1 to vn
//d[i] records the shortest distance from s to i
//pre[i] records the previous node of i in the shortest path
//flag and cnt are auxiliary arrays
//returning false means there exists a negative loop in given graph
bool spfa(int s,int vn,weight_t d[],bool flag[]/*,int pre[]*/,int cnt[]){
	fill(d,d+vn+1,INF);
	fill(flag,flag+vn+1,false);
	fill(cnt,cnt+vn+1,0);
	//fill(pre,pre+vn+1,0);

	queue<int> q;
	q.push(s);

	flag[s] = true;
	//pre[s] = 0;
	d[s] = 0;
	cnt[s] = 1;

	while( !q.empty() ){
		int u = q.front();
		q.pop();
		flag[u] = false;

		for(int next=Vertex[u];next;next=Edge[next].next){
			int v = Edge[next].to;
			if ( Neg[v] ) continue;

			weight_t t = d[u] + Edge[next].weight;

			if ( t < d[v] ){
				d[v] = t;
				//pre[v] = u;
				if ( !flag[v] ){
					++cnt[v];
					if ( cnt[v] > vn ) dfs(v);

					flag[v] = true;
					q.push(v);
				}
			}
		}
	}

	return true;
}

int N,M;
weight_t W[SIZE_OF_VERTICES];
inline weight_t f(weight_t x){return x*x*x;}

void read(){
    scanf("%d",&N);
    for(int i=1;i<=N;++i)scanf("%d",W+i);

    initGraph(N);
    scanf("%d",&M);
    int a,b;
    for(int i=0;i<M;++i){
        scanf("%d%d",&a,&b);
        mkEdge(a,b,f(W[b]-W[a]));
    }
}

weight_t D[SIZE_OF_VERTICES];
bool Flag[SIZE_OF_VERTICES];
int Cnt[SIZE_OF_VERTICES];

int main(){
    //freopen("1.txt","r",stdin);
    int nofkase;
    scanf("%d",&nofkase);
    for(int kase=1;kase<=nofkase;++kase){
        read();

        fill(Neg,Neg+N+1,false);
        spfa(1,N,D,Flag,Cnt);

        printf("Case %d:\n",kase);

        int q,t;
        scanf("%d",&q);
        while(q--){
            scanf("%d",&t);
            if ( INF == D[t] || D[t] < 3 || Neg[t] ) puts("?");
            else printf("%d\n",D[t]);
        }
    }
}