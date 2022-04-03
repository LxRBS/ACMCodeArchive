/**
 * 给定一个有向无环图，问有多少个点满足：
 * 从这个点出发可以进入循环路径，即永远可以走下去
 * 有向图上要想循环，显然要走到至少为包含2个点的SCC上
 * 因此先做一个SCC，再在KDAG上随便处理一下即可
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
int const SIZE = 100;
#else
int const SIZE = 3E5+5;
#endif

struct edge_t{
	int from,to;
	int next;//Index of the array is used as pointers, ZERO means NULL
}Edge[SIZE+SIZE];
int ECnt;
int Vertex[SIZE];

inline void initGraph(int n){
	ECnt = 2;
	fill(Vertex,Vertex+n+1,0);
}

inline void mkEdge(int a,int b){
	Edge[ECnt].from = a;
	Edge[ECnt].to = b;
	//Edge[ECnt].weight = w;
	Edge[ECnt].next = Vertex[a];
	Vertex[a] = ECnt ++;
}

int Stack[SIZE], StackTop;//
bool IsInStack[SIZE];

int TimeStamp;
int Dfn[SIZE], Low[SIZE];

int SCCCnt;//
int Belong[SIZE];//
int SCCSize[SIZE];//

void dfs(int u){
    Dfn[u] = Low[u] = ++TimeStamp;

    //
    IsInStack[ Stack[StackTop++] = u ] = true;

    //
    int v;
    for(int next=Vertex[u];next;next=Edge[next].next){
        if ( 0 == Dfn[ v = Edge[next].to ] ){
            dfs(v);
            if ( Low[v] < Low[u] ) Low[u] = Low[v];
        }else if ( IsInStack[v] && Dfn[v] < Low[u] ){
            Low[u] = Dfn[v];
        }
    }

    //
    if ( Dfn[u] == Low[u] ){
        ++SCCCnt;
        do{
            IsInStack[ v = Stack[--StackTop] ] = false;
            ++SCCSize[ Belong[v] = SCCCnt ];
        }while( v != u );        
    }
}

void Tarjan(int vn){
    fill(Dfn,Dfn+vn+1,0);
    fill(IsInStack,IsInStack+vn+1,false);
    fill(SCCSize,SCCSize+vn+1,0);

    TimeStamp = SCCCnt = StackTop = 0;

    for(int i=1;i<=vn;++i){
        if ( 0 == Dfn[i] ){
            dfs(i);
        }
    }
}

int Father[SIZE];
void init(int n){for(int i=0;i<=n;++i)Father[i]=i;}
int find(int x){return x==Father[x]?x:Father[x]=find(Father[x]);}
void unite(int x, int y){Father[find(y)]=find(x);}

typedef vector<int> vi;
vi G[SIZE];

int N, M;
int Ans[SIZE];

void ddddfs(int u){
	Ans[u] = SCCSize[u] > 1 ? 1 : 0;
	for(int v: G[u]){
		if(-1 == Ans[v]){
			dfs(v);
		}
		Ans[u] |= Ans[v];
	}
	return;
}

int proc(){
	Tarjan(N);

	// init(SCCCnt);
    for(int a,b,i=2;i<ECnt;++i){
        // if((a=(Belong[Edge[i].from])) == (b=find(Belong[Edge[i].to]))) continue;
		// unite(a, b);
		a=Belong[Edge[i].from];
		b=Belong[Edge[i].to];
		if(a != b){
			G[a].push_back(b);
		}        
	}

    fill(Ans, Ans+SCCCnt+1, -1);
	for(int i=1;i<=SCCCnt;++i){
		if(-1 == Ans[i]){
			ddddfs(i);
		}
	}
	int ans = 0;
	for(int i=1;i<=SCCCnt;++i){
		if(1 == Ans[i]){
			ans += SCCSize[i];
		}
	}
	return ans;
}

int main() {    
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif    
    N = getInt(); M = getInt();
	initGraph(N);
	for(int a,b,i=0;i<M;++i){
		a = getInt(); b = getInt();
		mkEdge(a, b);
	}
	printf("%d\n", proc());
    return 0;
}

