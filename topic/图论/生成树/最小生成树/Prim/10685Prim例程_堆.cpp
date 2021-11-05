//求MST的长度 
#include <cstdio>
#include <queue>
#include <climits>
#include <algorithm>
using namespace std;

#define SIZE 105

struct edge_t{
	int node;
	int w;
	edge_t *next;
}Edge[SIZE*SIZE];
int ECnt;
edge_t* Ver[SIZE];

//STL默认的优先队列是最大值在队首 
bool operator < (edge_t const&l,edge_t const&r){
	return l.w > r.w || ( l.w == r.w && l.node > r.node )
	    || ( l.w == r.w && l.node == r.node && l.next > r.next );
}

//此处只要加一条边即可 
void mkEdge(int a,int b,int w){
	Edge[ECnt].node = b;
	Edge[ECnt].w = w;
	Edge[ECnt].next = Ver[a];
	Ver[a] = Edge + ECnt ++;
}

void init(int n){
	ECnt = 0;
	fill(Ver,Ver+n,(edge_t*)0);
}

bool Flag[SIZE];
//n表示顶点个数 
int Prim(int n){
	fill(Flag,Flag+n,false);
	Flag[0] = true;
    
    priority_queue<edge_t> h;
    for(edge_t*p=Ver[0];p;p=p->next)
    	h.push(*p);
       
    int ret = 0;
    int cnt = 1;//已经选取了一个点 
    while( cnt < n ){
    	while( Flag[h.top().node] ) h.pop();
    	
    	++cnt;
    	ret += h.top().w;
    	int node = h.top().node;
    	Flag[node] = true;
    	h.pop();
    	
    	//将与node关联的且没用过的点的边加入堆 
    	for(edge_t*p=Ver[node];p;p=p->next){
		    if ( !Flag[p->node] ) h.push(*p);    	       
   	    }
	}        
	return ret;
}

int main(){
	int n;

	while( EOF != scanf("%d",&n) ){
		init(n);
        for(int i=0;i<n;i++)for(int j=0;j<n;j++){
        	int w;
        	scanf("%d",&w);
        	if ( i != j ) mkEdge(i,j,w);
		}
			
        printf("%d\n",Prim(n));
	}

	return 0;
}

