#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

//type of edge's weight
typedef int weight_t;

//just as its names
int const SIZE_OF_VERTICES = 10010;
int const SIZE_OF_EDGES = 2000010;

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

//to build bi-directional edge
inline void mkEdge(int a,int b,weight_t w=weight_t()){
	Edge[ECnt].from = a;
	Edge[ECnt].to = b;
	Edge[ECnt].weight = w;
	Edge[ECnt].next = Vertex[a];
	Vertex[a] = ECnt ++;

	Edge[ECnt].from = b;
	Edge[ECnt].to = a;
	Edge[ECnt].weight = w;
	Edge[ECnt].next = Vertex[b];
	Vertex[b] = ECnt ++;
}

//vn is the amount of vertices, indexed from 1 to vn
//peo i records the ith node to be eliminated, indexed from 1
//rank i records the rank of node i in PEO, indexed from 1
//label, heap and flag are auxiliary arrays
void mcs(int vn,int peo[],int rank[],int label[],vector<pair<int,int> >& heap,bool flag[]){
    fill(label,label+vn+1,0);
    fill(flag,flag+vn+1,false);

    heap.resize(vn);
    for(int i=0;i<vn;++i) heap[i].first = 0, heap[i].second = i + 1;
    make_heap(heap.begin(),heap.end());

    for(int i=vn;i>0;--i){
        int node;
        while( flag[node=heap.begin()->second] ){
            pop_heap(heap.begin(),heap.end());
            heap.pop_back();
        }

        pop_heap(heap.begin(),heap.end());
        heap.pop_back();

        peo[i] = node;
        rank[node] = i;
        flag[node] = true;

        for(int next=Vertex[node];next;next=Edge[next].next){
            int u = Edge[next].to;
            if ( flag[u] ) continue;

            ++label[u];
            heap.push_back(make_pair(label[u],u));
            push_heap(heap.begin(),heap.end());
        }

    }
}

int N,M;
void read(){
    scanf("%d%d",&N,&M);

    initGraph(N);
    for(int i=0;i<M;++i){
        int a,b;
        scanf("%d%d",&a,&b);
        mkEdge(a,b);
    }

    return;
}

int PEO[SIZE_OF_VERTICES];
int Rank[SIZE_OF_VERTICES];
int Label[SIZE_OF_VERTICES];
vector<pair<int,int> > Heap;
bool Flag[SIZE_OF_VERTICES];
void proc(){
    mcs(N,PEO,Rank,Label,Heap,Flag);

    fill(Label,Label+N+1,0);

    int k = 0;
    for(int i=N;i>0;--i){
        int u = PEO[i];

        fill(Flag,Flag+N+1,false);
        for(int next=Vertex[u];next;next=Edge[next].next){
            int v = Edge[next].to;
            if ( 0 == Label[v] ) continue;

            Flag[Label[v]] = true;
        }

        for(int j=1;j<=N;++j){
            if ( Flag[j] ) continue;

            Label[u] = j;
            if ( k < j ) k = j;
            break;
        }
    }

    printf("%d\n",k);
}

int main(){
    //freopen("1.txt","r",stdin);
    read();
    proc();
    return 0;
}

