#include <cstdio>
#include <vector>
#include <queue>
#include <map>
#include <algorithm>
#include <functional>
using namespace std;

//type of edge's weight
typedef long long int weight_t;

//just as its names
int const SIZE_OF_VERTICES = 200005;
int const SIZE_OF_EDGES = 100005 * 40;
weight_t const INF = 1000000000000000LL;

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

//this is for heap
struct dijkstra_t{
    int u;
    weight_t w;
    dijkstra_t(int a,weight_t b):u(a),w(b){}
};
bool operator < (dijkstra_t const&lhs,dijkstra_t const&rhs){
    return rhs.w < lhs.w || ( lhs.w == rhs.w && rhs.u < lhs.u );
}

//s is the source
//vn is the amount of vertices, all vertices are indexed from 1 to vn
//di records the shortest distance from s to i
//pre records the previous vertex of i in the shortest path
//flag is auxiliary array
void Dijkstra(int s,int vn,weight_t d[],int pre[],bool flag[]){
    fill(d,d+vn+1,INF);
    fill(flag,flag+vn+1,false);

    priority_queue<dijkstra_t> q;
    q.push(dijkstra_t(s,0));

    flag[s] = false;
    pre[s] = 0;
    d[s] = 0;

    while( 1 ){
        while( !q.empty() && flag[q.top().u] ) q.pop();

        if ( q.empty() ) return;

        dijkstra_t head = q.top();
        q.pop();
        int u = head.u;
        flag[u] = true;

        for(int next=Vertex[u];next;next=Edge[next].next){
            int v = Edge[next].to;
            if ( flag[v] ) continue;

            weight_t t = d[u] + Edge[next].weight;
            if ( t < d[v] ){
                d[v] = t;
                pre[v] = u;
                q.push(dijkstra_t(v,t));
            }
        }
    }
}

struct _t{
    int a,b,c,t;
}T[SIZE_OF_VERTICES];
bool operator < (_t const&lhs,_t const&rhs){
    return lhs.c < rhs.c || (lhs.c==rhs.c&&lhs.a<rhs.a) || (lhs.c==rhs.c&&lhs.a==rhs.a&&lhs.b<rhs.b);
}
vector<int> VC[SIZE_OF_VERTICES];

int N,M;
bool read(){
    if ( EOF == scanf("%d%d",&N,&M) ) return false;

    //for_each(VC+1,VC+N+1,mem_fn(vector<int>::clear));
    for(int i=1;i<=N;++i) VC[i].clear();

    for(int i=0;i<M;++i){
        scanf("%d%d%d%d",&T[i].a,&T[i].b,&T[i].c,&T[i].t);
        if ( T[i].a > T[i].b ) swap(T[i].a,T[i].b);
        VC[T[i].a].push_back(T[i].c);
        VC[T[i].b].push_back(T[i].c);
    }

    for(int i=1;i<=N;++i){
        vector<int>& v = VC[i];
        sort(v.begin(),v.end());
        vector<int>::iterator it = unique(v.begin(),v.end());
        v.erase(it,v.end());
    }
    return true;
}

struct _tt{
    int u;
    int c;
    _tt(int a,int b):u(a),c(b){}
};
bool operator < (_tt const&lhs,_tt const&rhs){
    return lhs.u < rhs.u || (lhs.u==rhs.u&&lhs.c<rhs.c);
}

map<_tt,int> Map;
weight_t D[SIZE_OF_VERTICES];
int Pre[SIZE_OF_VERTICES];
bool Flag[SIZE_OF_VERTICES];
void proc(){
    int vn = 0;
    Map.clear();
    _tt tt(0,0);
    for(int i=1;i<=N;++i){
        vector<int>&v = VC[i];
        for(vector<int>::iterator it=v.begin();it!=v.end();++it){
            /*
            tt.u = i;
            tt.c = *it;
            if ( Map.end() == Map.find(tt) ){
                Map.insert(make_pair(tt,++vn));
            }
            //*/
            Map.insert(make_pair(_tt(i,*it),++vn));
        }
    }

    initGraph(vn+=2);

    int k = 0;
    for(int i=1;i<=N;++i){
        vector<int>&v = VC[i];
        //printf("size = %u\n",v.size());
        int prevc = *v.begin();
        ++k;
        for(vector<int>::iterator it=++v.begin();it!=v.end();++it){
            mkEdge(k,k+1,*it-prevc);
            //printf("%d %d %d\n",k,k+1,*it-prevc);
            prevc = *it;
            ++k;
        }
    }

    vector<int>&v1=VC[1];
    k = 0;
    for(vector<int>::iterator it=v1.begin();it!=v1.end();++it){
        mkEdge(vn-1,++k,0);
        //printf("%d %d %d\n",vn-1,k,0);
    }

    vector<int>&v2 = VC[N];
    k = vn - 2 - v2.size();
    for(vector<int>::iterator it=v2.begin();it!=v2.end();++it){
        mkEdge(++k,vn,0);
        //printf("%d %d %d\n",k,vn,0);
    }

    for(int i=0;i<M;++i){
        mkEdge(Map[_tt(T[i].a,T[i].c)],Map[_tt(T[i].b,T[i].c)],T[i].t);
        //printf("%d %d %d\n",Map[_tt(T[i].a,T[i].c)],Map[_tt(T[i].b,T[i].c)],T[i].t);
    }

    Dijkstra(vn-1,vn,D,Pre,Flag);
    printf("%lld\n",D[vn]);
}

int main()
{
    //freopen("1.txt","r",stdin);
    while( read() ) proc();
    return 0;
}

