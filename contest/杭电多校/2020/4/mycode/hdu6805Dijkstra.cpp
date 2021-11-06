/**
   无向图，每个节点分为LRM三类。
   从L到R或者从R到L需要付出额外的代价X
   问从S到T的最小代价是多少
   将M类型的节点拆点，跑最短路
   前向星会超时！！！SPFA会超时！！！
*/
#include <bits/stdc++.h>
using namespace std;

//type of edge's weight
typedef long long int weight_t;

//just as its names
int const SIZE_OF_VERTICES = 100010<<1;
int const SIZE_OF_EDGES = 200010<<2;
weight_t const INF = 0x3FFFFFFF3FFFFFFF;

struct edge_t{
	int from,to;
	weight_t weight;
	int next;//Index of the array is used as pointers, ZERO means NULL
}Edge[SIZE_OF_EDGES];
int ECnt;
int Vertex[SIZE_OF_VERTICES];

vector<pair<int,weight_t> > G[SIZE_OF_VERTICES];

//Don't forget calling it
//n is the amount of vertices
inline void initGraph(int n){
	//ECnt = 1;
	//fill(Vertex,Vertex+n+1,0);
	for(int i=1;i<=n;++i)G[i].clear();
}

//to build bi-directional edge
inline void mkEdge(int a,int b,weight_t w=weight_t()){
    /*
	Edge[ECnt].from = a;
	Edge[ECnt].to = b;
	Edge[ECnt].weight = w;
	Edge[ECnt].next = Vertex[a];
	Vertex[a] = ECnt ++;

	Edge[ECnt].from = b;
	Edge[ECnt].to = a;
	Edge[ECnt].weight = w;
	Edge[ECnt].next = Vertex[b];
	Vertex[b] = ECnt ++;//*/
	G[a].push_back(make_pair(b,w));
	G[b].push_back(make_pair(a,w));
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
void Dijkstra(int s,int vn,weight_t d[],bool flag[]){
    fill(d,d+vn+1,INF);
    fill(flag,flag+vn+1,false);

    priority_queue<dijkstra_t> q;
    q.push(dijkstra_t(s,0));

    d[s] = 0;

    while( 1 ){
        while( !q.empty() && flag[q.top().u] ) q.pop();

        if ( q.empty() ) return;

        dijkstra_t head = q.top();
        q.pop();
        int v,u = head.u;
        weight_t tmp;
        flag[u] = true;

        /*
        for(int next=Vertex[u];next;next=Edge[next].next){
            if ( !flag[v = Edge[next].to] && (tmp=d[u]+Edge[next].weight) < d[v] ){
            	q.push(dijkstra_t(v,d[v]=tmp));
	        }
        }//*/
        vector<pair<int,weight_t> > const& vec = G[u];
        for(vector<pair<int,weight_t> >::const_iterator it=vec.begin();it!=vec.end();++it){
            if(!flag[v=it->first] && (tmp=d[u]+it->second)<d[v]){
                q.push(dijkstra_t(v,d[v]=tmp));
            }
        }
    }
}

//s is the source id
//vn is the amount of vertices, all vertices are indexed from 1 to vn
//d[i] records the shortest distance from s to i
//pre[i] records the previous node of i in the shortest path
//flag and cnt are auxiliary arrays
//returning false means there exists a negative loop in given graph
bool spfa(int s,int vn,weight_t d[],bool flag[]){
	fill(d,d+vn+1,INF);
	fill(flag,flag+vn+1,false);

	queue<int> q;
	q.push(s);

	flag[s] = true;
	d[s] = 0;

	while( !q.empty() ){
		int u = q.front();
		q.pop();
		flag[u] = false;

		/*
		for(int next=Vertex[u];next;next=Edge[next].next){
			int v = Edge[next].to;
			weight_t t = d[u] + Edge[next].weight;

			if ( t < d[v] ){
				d[v] = t;
				if ( !flag[v] ){
					flag[v] = true;
					q.push(v);
				}
			}
		}//*/
		weight_t t;
		int v;
		vector<pair<int,weight_t> > const& vec = G[u];
        for(vector<pair<int,weight_t> >::const_iterator it=vec.begin();it!=vec.end();++it){
            if((t=d[u]+it->second)<d[v=it->first]){
                d[v] = t;
                if(!flag[v]){
                    flag[v] = true;
					q.push(v);
                }
            }
        }
	}

	return true;
}

int getUnsigned(){
	char ch = getchar();
	while( ch < '0' || ch > '9' ) ch = getchar();

	int ret = (int)(ch-'0');
	while( '0' <= ( ch = getchar() ) && ch <= '9' ) ret = ret * 10 + (int)(ch-'0');
	return ret;
}

char A[SIZE_OF_VERTICES];
int N,M,S,T,X;

bool Flag[SIZE_OF_VERTICES];
weight_t D[SIZE_OF_VERTICES];

int main(){
    //freopen("1.txt","r",stdin);
    int a,b,nofkase = getUnsigned();
    weight_t w;
    while(nofkase--){
        initGraph((N=getUnsigned())*2+2);
        M = getUnsigned();
        S = getUnsigned();
        T = getUnsigned();
        X = getUnsigned();
        scanf("%s",A+1);

        while(M--){
            a = getUnsigned();
            b = getUnsigned();
            w = getUnsigned();

            //*
            if('M'==A[a]){//两个点,a表示L，a+N表示R
                if('M'==A[b]){
                    mkEdge(a,b,w);
                    mkEdge(a,b+N,w+X);
                    mkEdge(a+N,b,w+X);
                    mkEdge(a+N,b+N,w);
                }else if('L'==A[b]){
                    mkEdge(a,b,w);
                    mkEdge(a+N,b,w+X);
                }else{
                    mkEdge(a,b,w+X);
                    mkEdge(a+N,b,w);
                }
            }else if('L'==A[a]){
                if('M'==A[b]){
                    mkEdge(a,b,w);
                    mkEdge(a,b+N,w+X);
                }else if('L'==A[b]){
                    mkEdge(a,b,w);
                }else{
                    mkEdge(a,b,w+X);
                }
            }else{
                if('M'==A[b]){
                    mkEdge(a,b,w+X);
                    mkEdge(a,b+N,w);
                }else if('L'==A[b]){
                    mkEdge(a,b,w+X);
                }else{
                    mkEdge(a,b,w);
                }
            }//*/
        }

        int s = N+N+1, t = N+N+2;

        //*
        if('M'==A[S]){
            mkEdge(s,S,0);mkEdge(s,S+N,0);
        }else{
            mkEdge(s,S,0);
        }
        if('M'==A[T]){
            mkEdge(T,t,0);mkEdge(T+N,t,0);
        }else{
            mkEdge(T,t,0);
        }//*/
        Dijkstra(s,t,D,Flag);
        //spfa(s,t,D,Flag);
        printf("%lld\n",D[t]);
    }
    return 0;
}
