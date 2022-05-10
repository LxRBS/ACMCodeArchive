/**
  有N个人，每个人属于一个学校，有一个擅长的项目，并且有一个能力值
  现在需要挑出若干个人组队，队伍需要满足：不能有同校的人，不能有同项目的人
  假设能够构成队伍的最多人数为k，现在问：
  对x人的队伍，其能力值之和最大是多少，x=1,2,...,k
  即要回答k次这个问题。
  首先，求k显然是一个最大匹配的问题，在此基础上上还要求最值，显然可以做成费用流
  从1到k，每个限定人数都需要回答一次问题，显然可以用逐步扩流来解决 
*/
#include <bits/stdc++.h>
using namespace std;

char *__abc147, *__xyz258, __ma369[100000];
#define __hv007() ((__abc147==__xyz258) && (__xyz258=(__abc147=__ma369)+fread(__ma369,1,100000,stdin),__abc147==__xyz258) ? EOF : *__abc147++)

int getInt(){
	int sgn = 1;
	char ch = __hv007();
	while( ch != '-' && ( ch < '0' || ch > '9' ) ) ch = __hv007();
	if ( '-' == ch ) {sgn = 0;ch=__hv007();}

	int ret = (int)(ch-'0');
	while( '0' <= (ch=__hv007()) && ch <= '9' ) ret = ret * 10 + (int)(ch-'0');
	return sgn ? ret : -ret;
}

#ifndef ONLINE_JUDGE
int const SIZE = 400;
#else
int const SIZE = 1e5+5;
#endif

using llt = long long;
typedef llt weight_t;

int const SIZE_OF_VERTICES = SIZE;
int const SIZE_OF_EDGES = SIZE<<2;
weight_t const INF = 0x3F3F3F3FFFFFFFFF;
llt const UP = 2000000000;

struct edge_t{
    int from,to;
    weight_t cap;//容量
    weight_t cost;//费用
    int next;
}Edge[SIZE_OF_EDGES];
int ECnt;

int Vertex[SIZE_OF_VERTICES];

//初始化
inline void initGraph(int n){
    ECnt = 2;//ECnt从2开始，空指针用0表示，反向边用^1计算
    fill(Vertex,Vertex+n+1,0);
}

inline void mkEdge(int a,int b,weight_t capa,weight_t cost){
    Edge[ECnt].from = a;
    Edge[ECnt].to = b;
    Edge[ECnt].cap = capa;
    Edge[ECnt].cost = cost;
    Edge[ECnt].next = Vertex[a];
    Vertex[a] = ECnt++;

    Edge[ECnt].from = b;
    Edge[ECnt].to = a;
    Edge[ECnt].cap = 0;
    Edge[ECnt].cost = -cost;
    Edge[ECnt].next = Vertex[b];
    Vertex[b] = ECnt++;
}

void spfa(int s,int vn,weight_t d[],int pre[],bool flag[]){
    fill(d,d+vn+1,INF);
    fill(flag,flag+vn+1,false);
    fill(pre,pre+vn+1,0);

    queue<int> q;
    q.push(s);

    d[s] = 0;
    flag[s] = true;

    int u,v;
    weight_t tmp;
    while( !q.empty() ){
        flag[ u = q.front() ] = false;
        q.pop();

        for(int p=Vertex[u];p;p=Edge[p].next){
            if ( Edge[p].cap > 0 && ( tmp = d[u] + Edge[p].cost ) < d[ v=Edge[p].to ] ){
                d[v] = tmp;pre[v] = p;
                if ( !flag[v] ) q.push(v), flag[v] = true;
            }
        }
    }
}

using vi = vector<llt>;
vi Ans;

pair<weight_t,weight_t> mcmf(int s,int t,int vn,weight_t d[],int pre[],bool flag[]){
    weight_t miniCost = 0;
    weight_t maxFlow = 0;
    while(1){
        spfa(s,vn,d,pre,flag);
        //说明找不到增广路
        if ( INF == d[t] ) break;

        //找出该增广路上的可行流
        weight_t curFlow = INF;
        for(int p=pre[t];p;p=pre[Edge[p].from])if(curFlow>Edge[p].cap)curFlow = Edge[p].cap;

        //变动流量
        for(int p=pre[t];p;p=pre[Edge[p].from]){
            Edge[p].cap -= curFlow;
            Edge[p^1].cap += curFlow;
        }

        //更新流量和费用
        miniCost += d[t] * curFlow;
        maxFlow += curFlow;
        Ans.push_back(maxFlow * UP - miniCost);
    }

    return make_pair(maxFlow,miniCost);
}

int N;
int A[SIZE], B[SIZE], C[SIZE];
llt D[SIZE];
int Pre[SIZE];
bool Flag[SIZE];

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    N = getInt();
    for(int i=1;i<=N;++i){
        A[i] = getInt(); B[i] = getInt(); C[i] = getInt();    
    }
    initGraph(N+N+302);
    int s = N+N+301, t = N+N+302;
    for(int i=1;i<=N;++i){
       mkEdge(i, i+N, 1, UP-C[i]);
       mkEdge(A[i]+N+N, i, 1, 0);
       mkEdge(i+N, N+N+150+B[i], 1, 0);
    }
    for(int i=1;i<=150;++i){
        mkEdge(s, N+N+i, 1, 0);
        mkEdge(N+N+150+i, t, 1, 0);
    }
    mcmf(s, t, t, D, Pre, Flag);
    printf("%d\n", Ans.size());
    for(llt a: Ans)printf("%lld\n", a);
    return 0;
}
