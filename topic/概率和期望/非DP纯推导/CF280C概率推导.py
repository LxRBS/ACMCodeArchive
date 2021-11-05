/**
    有一棵树，每次随机选一个点，
    将其及其子孙节点全部删除，问将树删空需要的操作次数期望
    树根的概率必然为1
    一级子节点的概率为树根排在其后的概率，1/2
    二级子节点的概率为树根与一级均排在其后的概率，1/3
    ...
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

//just as its names
int const SIZE_OF_VERTICES = 100010;
int const SIZE_OF_EDGES = 200010;

struct edge_t{
	int from,to;
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
inline void mkEdge(int a,int b){
	Edge[ECnt].from = a;
	Edge[ECnt].to = b;
	Edge[ECnt].next = Vertex[a];
	Vertex[a] = ECnt ++;
}
double Ans = 0.0;
void dfs(int u,int parent,int depth){
    depth += 1;
    for(int v,p=Vertex[u];p;p=Edge[p].next){
        if((v=Edge[p].to)!=parent){
            Ans += 1.0 / depth;
            dfs(v, u, depth);
        }
    }
}
int main(){
    //freopen("1.txt","r",stdin);
    int n = getUnsigned();
    initGraph(n);
    for(int i=1;i<n;++i){
        int a = getUnsigned();
        int b = getUnsigned();
        mkEdge(a, b); mkEdge(b, a);
    }
    Ans = 1.0;
    dfs(1, 0, 1);
    printf("%.10f\n",Ans);
    return 0;
}
