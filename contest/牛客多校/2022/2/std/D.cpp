#include <cstdio>
#include <cmath>
#include <queue>
#include <vector>
#define MN 1000

using std::log;
using std::queue;
using std::vector;

using ld = long double;

struct Edge{
	int v;
	ld w;
};

int n,m;
int din[MN+5];
vector<Edge> e[MN+5];
ld psw;

void addEdge(int u,int v,ld w){
	e[u].push_back({v,w});
	din[v]++;
}

struct Dis{
	ld dis;
	int cnt;
	
	void reset(){
		dis = 0;
		cnt = 0;
	}
	
	void setInf(){
		dis = 1e100;
		cnt = 0;
	}
	
	bool operator < (const Dis& that)const{
		return dis+cnt*psw < that.dis+that.cnt*psw;
	}
	
	Dis operator + (ld w)const{
		return {dis+w,cnt+1};
	}
	
};

Dis dis[MN+5];
bool inq[MN+5];

bool hasNegativeLoop(){
	queue<int> q;
	for(int i=1;i<=n;i++){
		dis[i].reset();
		q.push(i);
		inq[i] = true;
	}
	while(!q.empty()){
		int u = q.front();
		q.pop();
		inq[u] = false;
		if(dis[u].cnt>=n) return true;
		for(Edge edge:e[u]){
			int v = edge.v;
			ld w = edge.w;
			if(dis[u]+w<dis[v]){
				dis[v] = dis[u]+w;
				if(!inq[v]){
					q.push(v);
					inq[v] = true;
				}
			}
		}
	}
	return false;
}

bool check(ld psw){
	::psw = psw;
	return !hasNegativeLoop();
}

int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++){
		int a,u,c,v;
		scanf("%d%d%d%d",&a,&u,&c,&v);
		ld w = -log((ld)c/a);
		addEdge(u,v,w);
	}
	ld l=0,r=1;
	for(int t=0;t<60;t++){
		ld mid = (l+r)/2;
		if(check(-log(mid))){
			l = mid;
		}else{
			r = mid;
		}
	}
	printf("%.10f\n",(double)r);
}
