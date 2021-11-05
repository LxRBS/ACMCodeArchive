/**
    n个城市，m个道路
    其中有d条坏了
    问要使AB连通，修复的道路长度最短是多少    
    
    也可以用并查集做连通块
    没有破坏的边，可以直接令其权值为0
*/
#include <bits/stdc++.h>
using namespace std;

typedef int weight_t;
int const SIZE_OF_VERTICES = 110;
int const SIZE_OF_EDGES = 100100;
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

struct ufs_t{
    enum{UF_SIZE=110};
    int father[UF_SIZE+1];

    void init(int n){for(int i=0;i<=n;++i)father[i]=i;}
    int find(int x){return father[x]==x?x:father[x]=find(father[x]);}
    void unite(int x,int y){father[find(y)]=find(x);}
}UF;

int A[110],B[110],W[110],Map[110][110];
set<int> Set;
weight_t D[110];
bool Flag[110];
int main(){
    //freopen("1.txt","r",stdin);
    int n = getUnsigned();
    int m = getUnsigned();
    for(int i=0;i<m;++i) A[i]=getUnsigned(),B[i]=getUnsigned(),W[i]=getUnsigned(),Map[A[i]][B[i]]=Map[B[i]][A[i]]=i;
    int d = getUnsigned();
    while(d--){
        int a = getUnsigned();
        int b = getUnsigned();
        Set.insert(Map[a][b]);
    }
    UF.init(n);
    for(int i=0;i<m;++i){
        if(Set.find(i)==Set.end()){
            UF.unite(A[i],B[i]);
        }
    }
    int s = getUnsigned();
    int t = getUnsigned();
    if(UF.find(s)==UF.find(t)){
        puts("0");return 0;
    }
    initGraph(n);
    for(int i=0;i<m;++i)if(Set.find(i)!=Set.end()){
        int a = UF.find(A[i]);
        int b = UF.find(B[i]);
        if(a!=b) mkEdge(a,b,W[i]);
    }
    spfa(UF.find(s),n,D,Flag);
    printf("%d\n",D[UF.find(t)]);
    return 0;
}
