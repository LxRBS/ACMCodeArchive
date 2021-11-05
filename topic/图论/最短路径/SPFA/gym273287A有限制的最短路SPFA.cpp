/**
    给定平面上若干个点，另加起点和终点
    每个点对之间有一个距离，且有若干种花费
    问在距离不超过B的情况下，从起点到终点的最小花费是多少
    相当于二维最短路，或者二维SPFA
    令Wij为起点到i距离不超过j的最小花费，
    更新的时候如果花费超过B则略过
    最后看Wti中的最小值即可
*/
#include <bits/stdc++.h>
using namespace std;

int getInt(){
	int sgn = 1;
	char ch = getchar();
	while( ch != '-' && ( ch < '0' || ch > '9' ) ) ch = getchar();
	if ( '-' == ch ) {sgn = 0;ch=getchar();}

	int ret = (int)(ch-'0');
	while( '0' <= (ch=getchar()) && ch <= '9' ) ret = ret * 10 + (int)(ch-'0');
	return sgn ? ret : -ret;
}


//type of edge's weight
struct weight_t{
    int cost;
    int distance;
    weight_t(int a=0,int b=0):cost(a),distance(b){}
};

//just as its names
int const SIZE_OF_VERTICES = 1100;
int const SIZE_OF_EDGES = 3000000;
weight_t const INF = weight_t(1000000000,1000000000);

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

typedef pair<int,int> pii;

int D[1100][1100];

int dist(int x1,int y1,int x2,int y2){
    int x = x2-x1;
    int y = y2-y1;
    int tt = x*x+y*y;
    int t = sqrt(tt);
    if(t*t==tt) return t;
    return t + 1;
}

///Wij表示s走到i点距离不超过j所用的小花费
int W[1010][1010];
bool Flag[1010][1010];
int proc(int B,int vn,int s,int t){
    for(int i=1;i<=vn;++i)fill(W[i],W[i]+B+1,1000000000);
    W[s][0] = 0;
    Flag[s][0] = true;
    queue<pii> q;
    q.push(pii({s,0}));
    while(!q.empty()){
        pii u = q.front();
        q.pop();
        Flag[u.first][u.second] = false;

        for(int tmp,v,i=Vertex[u.first];i;i=Edge[i].next){
            v = Edge[i].to;
            if((tmp=u.second+Edge[i].weight.distance)<=B&&W[v][tmp]>W[u.first][u.second]+Edge[i].weight.cost){
                W[v][tmp] = W[u.first][u.second]+Edge[i].weight.cost;
                if(!Flag[v][tmp]){
                    q.push(pii({v,tmp}));
                    Flag[v][tmp] = true;
                }
            }
        }
    }
    int ans = 1000000000;
    for(int i=0;i<=B;++i){
        ans = min(ans, W[t][i]);
    }
    return ans == 1000000000 ? -1 : ans;
}

int main(){
    //freopen("1.txt","r",stdin);
    ///起点
    int xs = getInt();
    int ys = getInt();
    ///终点
    int xd = getInt();
    int yd = getInt();
    ///限制
    int B = getInt();
    ///费用
    int c[110];
    ///car 费用
    c[0] = getInt();
    ///T种出行方式
    int T = getInt();
    for(int i=1;i<=T;++i)c[i] = getInt();
    ///N个站
    int N = getInt();
    int x[1100],y[1100];
    vector<pii> trans[1100];
    for(int i=1;i<=N;++i){
        ///每个站的坐标
        x[i] = getInt();
        y[i] = getInt();
        ///每个站与其他站的连接
        int m = getInt();
        while(m--){
            int j = getInt()+1;
            int t = getInt();
            trans[i].push_back(pii({j,t}));
        }
    }
    ///建图，一共N+2个点
    int vn = N + 2;
    int s = vn - 1, t = vn;
    initGraph(vn);

    D[s][t] = D[t][s] = dist(xs,ys,xd,yd);
    ///计算每两个站之间的距离
    for(int i=1;i<=N;++i){
        ///计算i到起点与终点的距离
        D[s][i] = D[i][s] = dist(xs,ys,x[i],y[i]);
        D[t][i] = D[i][t] = dist(xd,yd,x[i],y[i]);

        ///计算站站之间的距离
        for(int j=i+1;j<=N;++j){
            D[i][j] = D[j][i] = dist(x[i],y[i],x[j],y[j]);
        }
    }

    ///起点到终点有一条边
    mkEdge(s,t,weight_t(c[0]*D[s][t],D[s][t]));
    ///每个站到起点和终点各有一条边
    for(int i=1;i<=N;++i){
        mkEdge(s,i,weight_t(c[0]*D[s][i],D[s][i]));
        mkEdge(t,i,weight_t(c[0]*D[t][i],D[t][i]));
    }

    ///站站之间右边
    for(int i=1;i<=N;++i){
        for(auto p:trans[i]){
            mkEdge(i,p.first,weight_t(c[p.second]*D[i][p.first],D[i][p.first]));
        }
    }

    printf("%d\n",proc(B,vn,s,t));
    return 0;
}
