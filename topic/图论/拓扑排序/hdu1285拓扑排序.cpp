#include <cstdio>
#include <set>
#include <algorithm>
using namespace std;

struct edge_t{
	int node;
	edge_t* next;
}Edge[503];
edge_t* Vertex[503];
int Degree[503];//入度

//拓扑排序，n代表顶点的个数，直接输出结果
void topoSort(int n){
	set<int> s;

    //找到度为0的点
	for(int i=1;i<=n;++i)
		if( 0 == Degree[i] )
			s.insert(i);

	int u = *s.begin();
	printf("%d",u);
	s.erase(s.begin());
	edge_t* next = Vertex[u];
	while(next){
		int& d = Degree[next->node];
		--d;
		if ( 0 == d ) s.insert(next->node);
		next = next->next;
	}

	while( !s.empty() ){
		//输出头结点
		int u = *s.begin();
		printf(" %d",u);
		s.erase(s.begin());

		//删除u指向的所有点
		edge_t* next = Vertex[u];
		while(next){
			int& d = Degree[next->node];
			--d;
			if ( 0 == d ) s.insert(next->node);
			next = next->next;
		}
	}
	printf("\n");
	return;
}
int main(){
    int n,m;
	while( EOF != scanf("%d%d",&n,&m) ){
		fill(Vertex+1,Vertex+n+1,(edge_t*)0);
        fill(Degree+1,Degree+n+1,0);

		for(int i=0;i<m;++i){
			int a,b,w;
			scanf("%d%d",&a,&b);

			Edge[i].node = b;
			Edge[i].next = Vertex[a];
			Vertex[a] = Edge + i;
			++Degree[b];
		}

		topoSort(n);
	}
	return 0;
}