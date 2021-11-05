/**
    有向图无环图，问从S到T的期望步数
    保证连通
*/
#include <bits/stdc++.h>
using namespace std;

int getUnsigned(){
	char ch = getchar();
	while( ch < '0' || ch > '9' ) ch = getchar();

	int ret = (int)(ch-'0');
	while( '0' <= ( ch = getchar() ) && ch <= '9' ) ret = ret * 10 + (int)(ch-'0');
	return ret;
}

int const SIZE_OF_VERTICES = 101000;
int const SIZE_OF_EDGES = 2200000;

struct edge_t{
	int from,to;
	int weight;
	int next;//Index of the array is used as pointers, ZERO means NULL
}Edge[SIZE_OF_EDGES];
int ECnt;
int Vertex[SIZE_OF_VERTICES];

//Don't forget calling it
//n is the amount of vertices
inline void initGraph(int n){
	ECnt = 2;
	fill(Vertex,Vertex+n+1,0);
}

//to build bi-directional edge
inline void mkEdge(int a,int b,int weight){
	Edge[ECnt].from = a;
	Edge[ECnt].to = b;
	Edge[ECnt].weight = weight;
	Edge[ECnt].next = Vertex[a];
	Vertex[a] = ECnt ++;
}


double D[101000] = {0.0};
int Deg[101000],Xishu[101000];
queue<int> Q;
int main(){
    //freopen("1.txt","r",stdin);
    int n = getUnsigned();
    int m = getUnsigned();
    initGraph(n);
    while(m--){
        int a = getUnsigned();
        int b = getUnsigned();
        mkEdge(b,a,getUnsigned());
        ++Deg[a];++Xishu[a];
    }
    Q.push(n);
    while(!Q.empty()){
        int u = Q.front();
        Q.pop();
        for(int p=Vertex[u];p;p=Edge[p].next){
            int v = Edge[p].to;
            D[v] += (D[u] + Edge[p].weight) / Xishu[v];
            if(--Deg[v] == 0){
                Q.push(v);
            }
        }
    }
    printf("%.2f\n",D[1]);
    return 0;
}

