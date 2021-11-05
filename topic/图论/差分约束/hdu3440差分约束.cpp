/*
    跳房子，每次往更高的房子跳
    每次跳的最远水平距离为M
    N个房子排成一排，要求从最矮的房子依次跳到最高的房子
    问最矮的房子与最高的房子的最大距离是多少
*/

#include <stdio.h>
#include <queue>
#include <algorithm>
using namespace std;

int getUnsigned(){
	char ch = getchar();
	while( ch < '0' || ch > '9' ) ch = getchar();

	int ret = (int)(ch-'0');
	while( '0' <= ( ch = getchar() ) && ch <= '9' ) ret = ret * 10 + (int)(ch-'0');
	return ret;
}

//type of edge's weight
typedef int weight_t;

//just as its names
int const SIZE_OF_VERTICES = 1010;
int const SIZE_OF_EDGES = 50000;
weight_t const INF = 2000000000;

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

//
inline void mkEdge(int a,int b,weight_t w=weight_t()){
	Edge[ECnt].from = a;
	Edge[ECnt].to = b;
	Edge[ECnt].weight = w;
	Edge[ECnt].next = Vertex[a];
	Vertex[a] = ECnt ++;
}

//s is the source id
//vn is the amount of vertices, all vertices are indexed from 1 to vn
//d[i] records the shortest distance from s to i
//pre[i] records the previous node of i in the shortest path
//flag and cnt are auxiliary arrays
//returning false means there exists a negative loop in given graph
bool spfa(int s,int vn,weight_t d[],bool flag[],int cnt[]){
	fill(d,d+vn+1,INF);
	fill(flag,flag+vn+1,false);
	fill(cnt,cnt+vn+1,0);

	queue<int> q;
	q.push(s);

	flag[s] = true;
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

struct _t{
    int h;
    int idx;
}H[SIZE_OF_VERTICES];
bool operator < (_t const&lhs,_t const&rhs){
    return lhs.h < rhs.h;
}

int N,M;

bool read(){
    N = getUnsigned();
    M = getUnsigned();

    for(int i=1;i<=N;++i) H[i].h = getUnsigned(),H[i].idx = i;
    sort(H+1,H+N+1);

    initGraph(N);
    for(int i=1;i<N;++i){
        //x(i+1)-xi>=1,相当于xi-x(i+1)<=-1
        mkEdge(i+1,i,-1);
        //H(i+1)-Hi<=M，要注意谁左谁右
        mkEdge(min(H[i].idx,H[i+1].idx),max(H[i].idx,H[i+1].idx),M);
    }

    return true;
}

int D[SIZE_OF_VERTICES];
bool Flag[SIZE_OF_VERTICES];
int Cnt[SIZE_OF_VERTICES];

int main(){
    //freopen("1.txt","r",stdin);
    int nofkase = getUnsigned();
    for(int kase=1;kase<=nofkase;++kase){
        read();

        //一律是从左往右建图的，所以源点必须是左边的点，目标必须是右边的点
        bool b = spfa(min(H[1].idx,H[N].idx),N,D,Flag,Cnt);

        printf("Case %d: ",kase);
        if ( !b ){
            printf("-1\n");
        }else{
            printf("%d\n",D[max(H[1].idx,H[N].idx)]);
        }
    }
    return 0;
}
