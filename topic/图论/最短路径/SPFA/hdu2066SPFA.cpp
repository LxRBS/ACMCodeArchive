#include <cstdio>
#include <queue>
#include <algorithm>
using namespace std;
struct _t{
	int node;
	int weight;
	_t(int a=0,int b=0):node(a),weight(b){}
};

#define SIZE 1001
_t Graph[SIZE][SIZE];//图
int Degree[SIZE];    //度

int Dist[SIZE];
bool Flag[SIZE];

//SPFA算法，参数s表示源
//题目保证没有负环
void spfa(int s){
    fill(Dist,Dist+SIZE,INT_MAX);
	Dist[s] = 0;
	fill(Flag,Flag+SIZE,false);
	Flag[s] = true;

	queue<int> q;
	q.push(s);

	while( !q.empty() ){
		int u = q.front();
		q.pop();
		Flag[u] = false;

		for(int i=0;i<Degree[u];++i){
			int v = Graph[u][i].node;

			int tmp = Dist[u] + Graph[u][i].weight;
			if ( tmp < Dist[v] ){
				Dist[v] = tmp;
				if ( !Flag[v] ){
					q.push(v);
					Flag[v] = true;
				}
			}
		}
	}
	return;
}

int main(){
	int t,s,d;
	while( EOF != scanf("%d%d%d",&t,&s,&d) ){
        fill(Degree,Degree+SIZE,0);
		for(int i=0;i<t;++i){
			int a,b,time;
			scanf("%d%d%d",&a,&b,&time);
            Graph[a][Degree[a]].node = b;
            Graph[a][Degree[a]].weight = time;
			++Degree[a];
			Graph[b][Degree[b]].node = a;
			Graph[b][Degree[b]].weight = time;
			++Degree[b];
		}

		int tmp;
		for(int i=0;i<s;++i){
			scanf("%d",&tmp);
			Graph[0][Degree[0]].node = tmp;
            Graph[0][Degree[0]].weight = 0;
			++Degree[0];
			Graph[tmp][Degree[tmp]].node = 0;
			Graph[tmp][Degree[tmp]].weight = 0;
			++Degree[tmp];
		}

		spfa(0);

		int ans = INT_MAX;
		for(int i=0;i<d;++i){
			scanf("%d",&tmp);
		    if ( Dist[tmp] < ans ) ans = Dist[tmp];
		}
		printf("%d\n",ans);
	}
	return 0;
}