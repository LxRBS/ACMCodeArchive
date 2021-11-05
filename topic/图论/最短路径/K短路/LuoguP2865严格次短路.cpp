/**
    严格次短路，保证存在
    同一条边可以来回走多次
    同时维护2个路径即可
*/
#include <bits/stdc++.h>
using namespace std;

//type of edge's weight
typedef int weight_t;

//just as its names
int const SIZE_OF_VERTICES = 5100;
int const SIZE_OF_EDGES = 220000;
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
bool spfa(int s,int vn,weight_t d[][5100],bool flag[]){
	fill(d[0],d[0]+vn+1,INF);
	fill(d[1],d[1]+vn+1,INF);
	fill(flag,flag+vn+1,false);

	queue<int> q;
	q.push(s);

	flag[s] = true;
	d[0][s] = 0;

	while( !q.empty() ){
		int u = q.front();
		q.pop();
		flag[u] = false;

		for(int next=Vertex[u];next;next=Edge[next].next){
			int v = Edge[next].to;
			weight_t tmp[] = { //一共4个数
			    d[0][u] + Edge[next].weight,
			    d[1][u] + Edge[next].weight,
			    d[0][v],d[1][v]
			};
            sort(tmp,tmp+4);
            int tn = unique(tmp,tmp+4) - tmp;

            while(tn&&tmp[tn-1]>=INF) --tn;
            if(0==tn) continue;

            if(tmp[0]<d[0][v]){
                d[0][v] = tmp[0];
                if(!flag[v]){
                    flag[v] = true;
					q.push(v);
                }
            }

            if(tn>1 && tmp[1]<d[1][v]){
                d[1][v] = tmp[1];
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

weight_t D[2][5100];
bool Flag[5100];

int main(){
    //freopen("1.txt","r",stdin);
    int n = getUnsigned();
    int m = getUnsigned();
    initGraph(n);
    while(m--){
        int a = getUnsigned();
        int b = getUnsigned();
        mkEdge(a,b,getUnsigned());
    }
    spfa(1,n,D,Flag);
    printf("%d\n",D[1][n]);
    return 0;
}
