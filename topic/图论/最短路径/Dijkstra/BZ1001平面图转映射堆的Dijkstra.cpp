//2248ms，与采用最小堆的Dijkstra算法差不多
#include <cstdio>
#include <algorithm>
using namespace std;

struct MapHeap{
    typedef int value_t;
    enum {SIZE=2000010};

	value_t data[SIZE];
	int index[SIZE];//索引
	int i2d[SIZE];//索引到数据的映射，索引为i的数据是data[i2d[idx]]
	int cnt,toUsed,c;

	MapHeap():cnt(0){}
	void clear(){cnt=0;}

	//指定索引，插入一个值，索引需各自不同
	void insert(int idx,value_t const& value){
		for (toUsed=++cnt;toUsed>1&&value<data[toUsed>>1];data[i2d[index[toUsed]=index[toUsed>>1]]=toUsed]=data[toUsed>>1],toUsed>>=1);
		data[i2d[index[toUsed]=idx]=toUsed]=value;
	}

	//删除一个索引，其值由参数传回
	int remove(int idx,value_t& value){
		idx=i2d[idx];
		if (idx<1||idx>cnt) return 0;

		for (value=data[toUsed=idx];toUsed>1;data[i2d[index[toUsed]=index[toUsed>>1]]=toUsed]=data[toUsed>>1],toUsed>>=1);
		for (c=2;c<cnt&&data[c+=(c<cnt-1&&data[c+1]<data[c])]<data[cnt];data[i2d[index[toUsed]=index[c]]=toUsed]=data[c],toUsed=c,c<<=1);
		data[i2d[index[toUsed]=index[cnt]]=toUsed]=data[cnt];
		--cnt;
		return 1;
	}
	//弹出最小值及其索引，由参数传回
	int pop(int& idx,value_t& value){
		if (cnt<1) return 0;
		idx=index[1];
		for (value=data[toUsed=1],c=2;c<cnt&&data[c+=(c<cnt-1&&data[c+1]<data[c])]<data[cnt];data[i2d[index[toUsed]=index[c]]=toUsed]=data[c],toUsed=c,c<<=1);
		data[i2d[index[toUsed]=index[cnt]]=toUsed]=data[cnt];
		--cnt;
		return 1;
	}
};


//type of edge's weight
typedef int weight_t;

//just as its names
int const SIZE_OF_VERTICES = 2000010;
int const SIZE_OF_EDGES = 6000010;
weight_t const INF = 1000000000;

struct edge_t{
	int from,to;
	weight_t weight;
	int next;//Index of the array is used as pointers, ZERO means NULL
}Edge[SIZE_OF_EDGES];
int ECnt;
int Vertex[SIZE_OF_VERTICES];

//Don't forget calling it
//cnt is the amount of vertices
inline void initGraph(int cnt){
	ECnt = 1;
	fill(Vertex,Vertex+cnt+1,0);
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

//s is the source
//vn is the amount of vertices, all vertices are indexed from 1 to vn
//di records the shortest distance from s to idx
//pre records the previous vertex of idx in the shortest path
//flag and heap are auxiliaries
void Dijkstra(int s,int vn,weight_t d[],int pre[],bool flag[],MapHeap& heap){
    fill(d,d+vn+1,INF);
    fill(flag,flag+vn+1,false);
    pre[s] = 0;
    flag[s] = true;
    d[s] = 0;
    heap.clear();heap.insert(s,0);

    int u,v;
    weight_t w,tmp;
    while( heap.pop(u,w) ){
        flag[u] = true;
        for(int p=Vertex[u];p;p=Edge[p].next){
            if( !flag[v=Edge[p].to] && (tmp=d[u]+Edge[p].weight)<d[v] ){
                pre[u] = v;
                d[v] = tmp;
                heap.remove(v,w);
                heap.insert(v,tmp);
            }
        }
    }
}

int N,M,S,T;
bool Flag[SIZE_OF_VERTICES];
weight_t D[SIZE_OF_VERTICES];
int Pre[SIZE_OF_VERTICES];
int Cnt[SIZE_OF_VERTICES];
MapHeap Heap;

bool read(){
    scanf("%d%d",&N,&M);

    if ( 1 == N ){
        int t = INF;
        int w;
        for(int i=1;i<M;++i){
            scanf("%d",&w);
            if ( w < t ) t = w;
        }
        printf("%d\n",INF==t?0:t);
        return true;
    }

    if ( 1 == M ){
       int t = INF;
        int w;
        for(int i=1;i<N;++i){
            scanf("%d",&w);
            if ( w < t ) t = w;
        }
        printf("%d\n",t);
        return true;
    }

    S = ( N - 1 ) * ( M - 1 ) * 2 + 1;
    T = S + 1;
    initGraph(T);

    int a,b,w;
    //the first row of horizontal edges
    for(int i=1;i<=M-1;++i){
        scanf("%d",&w);
        mkEdge(T,i,w);
    }

    for(int i=2;i<N;++i){
        a = ( 2 * ( i - 1 ) - 1 ) * ( M - 1 ) + 1;
        b = a + M - 1;

        for(int j=1;j<=M-1;++j){
            scanf("%d",&w);
            mkEdge(a++,b++,w);
        }
    }

    //the last row of horizontal edges
    b = ( M - 1 ) * ( 2 * N - 3 ) + 1;
    for(int i=1;i<=M-1;++i){
        scanf("%d",&w);
        mkEdge(S,b++,w);
    }

    //vertical edges
    for(int i=2;i<=N;++i){
        b = ( 2 * i - 3 ) * ( M - 1 ) + 1;
        scanf("%d",&w);
        mkEdge(S,b,w);

        ++b;
        a = b - M;
        for(int j=1;j<M-1;++j){
            scanf("%d",&w);
            mkEdge(a++,b++,w);
        }

        scanf("%d",&w);
        mkEdge(T,a,w);
    }

    //diagonal edges
    for(int i=2;i<=N;++i){
        b = (2*i-3)*(M-1) + 1;
        a = b - M + 1;
        for(int j=1;j<=M-1;++j){
            scanf("%d",&w);
            mkEdge(a++,b++,w);
        }
    }

    Dijkstra(S,T,D,Pre,Flag,Heap);
    //spfa(S,T,D,Pre,Flag,Cnt);
    printf("%d\n",D[T]);

    return true;
}

int main()
{
    //freopen("1.txt","r",stdin);
    read();
    return 0;
}