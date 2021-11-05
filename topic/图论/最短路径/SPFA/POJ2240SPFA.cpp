/*
    货币A到货币B的汇率为rab
    1个单位的A能兑换到1*rab个单位的B
    问是否能通过兑换赚钱

    能赚钱则有 PI( r ) > 1
    取对数 SIGMA( log(r) ) > 0
    即判断有没有正环
    取负对数，即判有没有负环
*/
#include <stdio.h>
#include <string>
#include <math.h>
#include <limits.h>
#include <map>
#include <queue>
#include <iostream>
#include <algorithm>
using namespace std;


//type of edge's weight
typedef double weight_t;

//just as its names
int const SIZE_OF_VERTICES = 300;
int const SIZE_OF_EDGES = 3000;
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
    /*
	Edge[ECnt].from = b;
	Edge[ECnt].to = a;
	Edge[ECnt].weight = w;
	Edge[ECnt].next = Vertex[b];
	Vertex[b] = ECnt ++;
	//*/
}

//s is the source id
//vn is the amount of vertices, all vertices are indexed from 1 to vn
//d[i] records the shortest distance from s to i
//pre[i] records the previous node of i in the shortest path
//flag and cnt are auxiliary arrays
//returning false means there exists a negative loop in given graph
bool spfa(int s,int vn,weight_t d[],bool flag[],/*int pre[],*/int cnt[]){
	fill(d,d+vn+1,INF);
	fill(flag,flag+vn+1,false);
	fill(cnt,cnt+vn+1,0);
	//fill(pre,pre+vn+1,0);

	queue<int> q;
	q.push(s);

	flag[s] = true;
	//pre[s] = 0;
	d[s] = 0;
	cnt[s] = 1;

	while( !q.empty() ){
		int u = q.front();
		q.pop();
		flag[u] = false;

		for(int next=Vertex[u];next;next=Edge[next].next){
			int v = Edge[next].to;
			weight_t t = d[u] + Edge[next].weight;

			if ( t < d[v] ){
				d[v] = t;
				//pre[v] = u;
				if ( !flag[v] ){
					++cnt[v];
					if ( cnt[v] > vn ) return false;

					flag[v] = true;
					q.push(v);
				}
			}
		}
	}

	return true;
}


int N,M;
map<string,int> S2V;
bool read(){
    cin>>N;
    if ( 0 == N ) return false;

    S2V.clear();
    string s;
    for(int i=1;i<=N;++i){
        cin>>s;
        S2V.insert(make_pair(s,i));
    }

    initGraph(N);
    cin>>M;
    string t;
    double w;
    for(int i=0;i<M;++i){
        cin>>s>>w>>t;
        mkEdge(S2V[s],S2V[t],-log(w));
    }
    return true;
}

weight_t D[SIZE_OF_VERTICES];
int Cnt[SIZE_OF_VERTICES];
bool Flag[SIZE_OF_VERTICES];

int main(){
    //freopen("1.txt","r",stdin);
    for(int kase=1;read();++kase){
        printf("Case %d: ",kase);
        printf(spfa(1,N,D,Flag,Cnt)?"No\n":"Yes\n");
    }
    return 0;
}
