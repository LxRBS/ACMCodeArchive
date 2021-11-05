//每个电梯有速度和停靠楼层
//问从0层到k层最少用多少时间
//同一个电梯的停靠楼层之间建一条边
//不同电梯的换乘楼层建一条边

#include <stdio.h>
#include <string.h>
#include <queue>
#include <sstream>
#include <vector>
#include <algorithm>
using namespace std;


//type of edge's weight
typedef int weight_t;

//just as its names
int const SIZE_OF_VERTICES = 550;
int const SIZE_OF_EDGES = 10000;
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


int N,K;
int T[110];
vector<int> Vec[101];
char Input[10000];

bool read(){
    if ( EOF == scanf("%d%d",&N,&K) ) return false;

    ++K;

    initGraph(N*100);
    for(int i=1;i<=100;++i)Vec[i].clear();

    for(int i=1;i<=N;++i)scanf("%d",T+i);

    fgets(Input,9999,stdin);
    int a,b;
    for(int i=1;i<=N;++i){
        fgets(Input,9999,stdin);
        stringstream ss(Input);
        a = -1;
        while( ss >> b ){
            ++b;
            Vec[b].push_back(i);
            if ( -1 == a ){
                a = b;
                continue;
            }

            mkEdge(a+(i-1)*100,b+(i-1)*100,T[i]*(b-a));//一个电梯之间的不同楼层
            a = b;
        }
    }

    //换乘
    for(int i=1;i<=100;++i){
        vector<int>const&v = Vec[i];
        if(v.size()>1)for(unsigned j=0;j<v.size()-1;++j)for(unsigned k=j+1;k<v.size();++k)mkEdge(i+(v[j]-1)*100,i+(v[k]-1)*100,60);
    }

    //1是共通的
    for(int i=2;i<=N;++i) mkEdge(1,1+(i-1)*100,0);

    return true;
}

int D[550];
bool Flag[550];
int main(){
    //freopen("1.txt","r",stdin);
    while( read() ){
        spfa(1,N*100,D,Flag);
        int ans = D[K];
        for(int i=2;i<=N;++i)if(D[K+(i-1)*100]<ans)ans=D[K+(i-1)*100];
        if ( INF == ans ) printf("IMPOSSIBLE\n");
        else printf("%d\n",ans);
    }
    return 0;
}
