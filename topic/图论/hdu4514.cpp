//判环，然后求最长路径
#include <cstdio>
#include <vector>
#include <algorithm>
//#pragma comment(linker,"/STACK:102400000,102400000")
using namespace std;

struct _t{
	int v;
	int w;
	_t *next;
}Edge[1000000*2+5];
int ECnt = 0;

_t* V[100000+5];

int N,M;

void mkEdge(int a,int b,int w){
	Edge[ECnt].v = b;
	Edge[ECnt].w = w;
	Edge[ECnt].next = V[a];
	V[a] = Edge + ECnt ++;

	Edge[ECnt].v = a;
	Edge[ECnt].w = w;
	Edge[ECnt].next = V[b];
	V[b] = Edge + ECnt ++;
}

//并查集初始化，顺便初始化图
int Father[100000+5];
void init(){
	ECnt = 0;
	fill(V+1,V+N+1,(_t*)0);
	for(int i=1;i<=N;Father[i]=i++);
}
int find(int x){return Father[x]==x?x:Father[x]=find(Father[x]);}
void unite(int x,int y){Father[find(y)]=find(x);}

//求从给定点出发的距离,返回值为最远的那个端点
bool F[100000+5];
int D[100000+5];
vector<int> q;
int bfs(int root){
	///*
	fill(F+1,F+N+1,false);
	F[root] = true;
	fill(D+1,D+N+1,0);
	//*/
	D[root] = 0;
	int t = root, d = 0;
	
	q.clear();
	q.push_back(root);

	while( !q.empty() ){
		int u = q.back();
		q.pop_back();

		for(_t*p=V[u];p;p=p->next){
			int v = p->v;
			if ( F[v] ) continue;
			D[v] = D[u] + p->w;
			F[v] = true;
			q.push_back(v);

			if ( D[v] > d ) d = D[v], t = v;
		}
	}

	return t;
} 

int main(){
	q.reserve(100000+5);
	while( EOF != scanf("%d%d",&N,&M) ){
		init();
		bool flag = false;
		for(int i=0;i<M;++i){
			int a,b,w;
			scanf("%d%d%d",&a,&b,&w);
			if ( !flag ){
                if ( find(a) == find(b) ){
					flag = true;
				}else{
					mkEdge(a,b,w);
					unite(a,b);
				}
			}
		}
		if ( flag ){
			printf("YES\n");
			continue;
		}
		//求最长长度，找树的最长长度
		int ret = 0;
		for(int i=1;i<=N;++i){
			if ( Father[i] != i ) continue;
			int t = bfs(i);
			//再搜一遍
            t = bfs(t);
			if ( ret < D[t] ) ret = D[t];
		}
		printf("%d\n",ret);
	}
	return 0;
}
