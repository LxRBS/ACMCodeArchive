#include <cstdio>
#include <map>
#include <algorithm>
#include <numeric>
using namespace std;

struct edge_t{
	int node;
	edge_t* next;
}Edge[450];

int EdgeCnt = 0;
edge_t* Vertex[31] = {0};

typedef map<int,int> mii;
typedef mii::iterator miiit;
mii M2I;//编号对索引

//生成边
void mkEdge(int a,int b){
	Edge[EdgeCnt].node = b;
	Edge[EdgeCnt].next = Vertex[a];
	Vertex[a] = Edge + EdgeCnt++;

	Edge[EdgeCnt].node = a;
	Edge[EdgeCnt].next = Vertex[b];
	Vertex[b] = Edge + EdgeCnt++;
}

int Dist[31][31];
//floyd算法
void floyd(int n){
	//三重循环
	for(int k=0;k<n;++k)for(int i=0;i<n;++i)for(int j=0;j<n;++j)
		Dist[i][j] = min(Dist[i][j],Dist[i][k]+Dist[k][j]);
}

int main(){
    int nc;
	scanf("%d",&nc);

	for(int i=0;i<nc;++i)fill(Dist[i],Dist[i]+nc,40);


	for(int i=0;i<nc;++i){
		int a,b;
		scanf("%d%d",&a,&b);

		int ia,ib;
        miiit it = M2I.find(a);
		if ( M2I.end() != it ) ia = it->second;
		else ia = M2I.size(),M2I[a] = ia;

		it = M2I.find(b);
		if ( M2I.end() != it ) ib = it->second;
		else ib = M2I.size(), M2I[b] = ib;
		
		mkEdge(ia,ib);
		Dist[ia][ib] = Dist[ib][ia] = 1;
		Dist[ia][ia] = Dist[ib][ib] = 0;
	}
    
	floyd(M2I.size());

	//问题
	int a,b;
	while( scanf("%d%d",&a,&b) && a && b ){
		int s = M2I[a];
		printf("%d\n",count_if(Dist[s],Dist[s]+M2I.size(),bind2nd(greater<int>(),b)));
	}
	return 0;
}