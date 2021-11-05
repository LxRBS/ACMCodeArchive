#include <cstdio>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;

#define SIZE 401
int A[SIZE][SIZE];

struct edge_t{
	int node;
    float weight;
	edge_t* next;
}Edge[2*SIZE*(SIZE+1)];
edge_t* Vertex[2*SIZE+1];

const float INF = 1E9;
float Dist[2*SIZE+1];
bool Flag[2*SIZE+1];
int Cnt[2*SIZE+1];
//带检查的SPFA算法,n为顶点的个数,0总为源点
bool spfa(int n){
    fill(Dist,Dist+n,INF);
	Dist[0] = 0.0;
	fill(Flag,Flag+n,false);
	Flag[0] = true;
	fill(Cnt,Cnt+n,0);
	Cnt[0] = 1;

    vector<int> q;
	q.push_back(0);

	while( !q.empty() ){
		int u = q.back();
		Flag[u] = false;
        q.pop_back();

		edge_t* p = Vertex[u];
		while( p ){
			int v = p->node;
			float t = Dist[u] + p->weight;
			p = p->next;

			if ( t < Dist[v] ){
                Dist[v] = t;
				if ( !Flag[v] )
					q.push_back(v), Flag[v] = true, ++Cnt[v];
				if ( Cnt[v] > n ) return false;
			}
		}
	}
	return true;
}

int main(){
	int n,m,low,high;
	while( EOF != scanf("%d%d%d%d",&n,&m,&low,&high) ){
		for(int i=0;i<n;++i)for(int j=0;j<m;++j)
			scanf("%d",A[i]+j);

		fill(Vertex,Vertex+n+m+1,(edge_t*)0);
        //建立有向带权图
		//建立零点到其他个点的边
		for(int i=0;i<n+m;++i){
			Edge[i].node = i + 1;
			Edge[i].weight = 0.0;
			Edge[i].next = Vertex[0];
			Vertex[0] = Edge + i;
		}
		int ecnt = n + m;

		//建立其他各点的边
		for(int i=0;i<n;++i)for(int j=0;j<m;++j){
			Edge[ecnt].node = n + j + 1;
			Edge[ecnt].weight = log((float)A[i][j]/(float)low);
			Edge[ecnt].next = Vertex[1+i];
			Vertex[1+i] = Edge + ecnt ++;

			Edge[ecnt].node = 1 + i;
			Edge[ecnt].weight = log((float)high/(float)A[i][j]);
			Edge[ecnt].next = Vertex[n+j+1];
			Vertex[n+j+1] = Edge + ecnt ++;
		}

		printf(spfa(n+m+1)?"YES\n":"NO\n");
	}
	return 0;
}