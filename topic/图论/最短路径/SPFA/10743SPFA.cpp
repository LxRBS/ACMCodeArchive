#include <cstdio>
#include <queue>
#include <algorithm>
using namespace std;

#define SIZE 100003

//图结构
struct edge_t{
	int node;
	int weight;
	edge_t* next;
}Edge[SIZE+SIZE];
edge_t* Vertex[SIZE];

int Dist0[SIZE];//0到其他各点的最短距离
int Dist[13][SIZE];

bool Flag[SIZE];

//SPFA算法，s为源，n为顶点数量，d为结果
void spfa(int s,int n,int d[]){
    fill(d,d+n,INT_MAX);
	d[s] = 0;

	fill(Flag,Flag+n,false);
	Flag[s] = true;

	queue<int> q;
	q.push(s);

	while( !q.empty() ){
        int u = q.front();
		q.pop();
		Flag[u] = false;

		edge_t* next = Vertex[u];
		while( next ){
			int v = next->node;
			int tmp = d[u] + next->weight;
			next = next->next;

			if ( tmp < d[v] ){
				d[v] = tmp;
				if (!Flag[v]) q.push(v), Flag[v] = true;
			}
		}
	}
	return;
}

int const FAC[] = {1,1,2,6,24,120,720,5040,40320,362880,3628800,39916800};

//n是需要访问点的个数(不包括0点),arr是点的具体内容
int solve(int n,int arr[]){
	int x[] = {0,1,2,3,4,5,6,7,8,9,10,11};
    
    int ret = INT_MAX;

	for(int i=0;i<FAC[n];++i){
        int tmp = Dist0[arr[x[0]]] + Dist0[arr[x[n-1]]];
		for(int j=1;j<n;++j)
            tmp += Dist[x[j-1]][arr[x[j]]];
		if ( ret > tmp ) ret = tmp;
		next_permutation(x,x+n);
	}

	return ret;
}
int main(){
	int kase;
	scanf("%d",&kase);
	while(kase--){
        int n,m;
		scanf("%d%d",&n,&m);

		fill(Vertex,Vertex+n,(edge_t*)0);

		for(int i=0;i<m;++i){
            int a,b,w;
			scanf("%d%d%d",&a,&b,&w);

			Edge[i].node = b;
			Edge[i].weight = w;
			Edge[i].next = Vertex[a];
			Vertex[a] = Edge + i;

			Edge[i+m].node = a;
			Edge[i+m].weight = w;
			Edge[i+m].next = Vertex[b];
			Vertex[b] = Edge + i + m;
		}

		int cnt;
		int arr[14];
		scanf("%d",&cnt);
		for(int i=0;i<cnt;++i)scanf("%d",arr+i);

		//对每个点做一次SPFA
		spfa(0,n,Dist0);
		for(int i=0;i<cnt;++i)spfa(arr[i],n,Dist[i]);

		printf("%d\n",solve(cnt,arr));
	}
	return 0;
}