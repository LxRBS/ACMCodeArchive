/**
 * 给定一个数组A，还有模数M，作如下操作：
 * 1. 任选一个元素Ai
 * 2. 假设上一个选出的元素是X，则这次可以选择X或者(X+1)%M
 * 3. 重复2操作，直到无法进行
 * 问经过此系列操作后，数组A中能够留下的数的总和最小是多少
 * 显然相等的元素会全部取出，然后再考虑下一个。
 * 做一个有向图，如果Aj能在Ai后面取出，即Aj = (Ai + 1) % M，则i到j有一条边
 * 再做一个SCC，求出KDAG，从入度为0的点向后走，即可求出每条路上可能拿走的最大和，即可求出答案
 * 实际上应该最多只有一个环，剩下的都是线性的路径，直接打标记搜索即可。
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
int const SIZE = 23;
#else
int const SIZE = 2E5+13;
#endif

//just as its names
int const SIZE_OF_VERTICES = SIZE;
int const SIZE_OF_EDGES = SIZE + SIZE;

struct edge_t{
	int from,to;
	// weight_t weight;
	int next;//Index of the array is used as pointers, ZERO means NULL
}Edge[SIZE_OF_EDGES];
int ECnt;
int Vertex[SIZE_OF_VERTICES];

//Don't forget calling it
//n is the amount of vertices
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

int Stack[SIZE_OF_VERTICES], StackTop;//辅助栈
bool IsInStack[SIZE_OF_VERTICES];

int TimeStamp;
int Dfn[SIZE_OF_VERTICES], Low[SIZE_OF_VERTICES];

int SCCCnt;//连通分量的总数量
int Belong[SIZE_OF_VERTICES];//第i个顶点属于第Belong[i]个强连通分量
int SCCSize[SIZE_OF_VERTICES];//第i个连通分量的大小，下标从1开始

void dfs(int u){
    Dfn[u] = Low[u] = ++TimeStamp;

    //入栈
    IsInStack[ Stack[StackTop++] = u ] = true;

    //对u的每一条边
    int v;
    for(int next=Vertex[u];next;next=Edge[next].next){
        if ( 0 == Dfn[ v = Edge[next].to ] ){
            dfs(v);
            if ( Low[v] < Low[u] ) Low[u] = Low[v];
        }else if ( IsInStack[v] && Dfn[v] < Low[u] ){
            Low[u] = Dfn[v];
        }
    }

    //找到一个SCC
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


using llt = long long;
using pii = pair<int, int>;
using vi = vector<int>;
using vpii = vector<pii>;

int N, M;
int A[SIZE];
unordered_map<int, int> I2V;
unordered_map<int, int> Cnt;

vi Kag[SIZE];
int Deg[SIZE] = {0};
llt W[SIZE] = {0};

llt f(int start){
    queue<int> q;
    q.push(start);
    llt ans = W[start];

    while(!q.empty()){
       int h = q.front(); q.pop();
       assert(Kag[h].size() <= 1);
       for(auto v : Kag[h]){
           ans += W[v];
           q.push(v);          
       }
    }
    return ans;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r" ,stdin);
#endif
    N = getInt();
    M = getInt();
    for(int i=0;i<N;++i) ++Cnt[A[i] = getInt()];
    sort(A, A+N);
    int n = unique(A, A+N) - A;
    for(int i=0;i<n;++i){
        I2V[A[i]] = i + 1;
    }

    initGraph(n);
    for(int i=0;i<n;++i){
        int x = A[i];
        int y = (x + 1) % M;
        auto it = I2V.find(y);
        if(it != I2V.end()){
            mkEdge(I2V[x], it->second);   
        }
    }
    Tarjan(n);

    for(int i=1;i<=n;++i){
        int u = Belong[i];
        W[u] += (llt)A[i-1] * Cnt[A[i-1]];
    }

    for(int u,v,i=2;i<ECnt;++i){
        u = Edge[i].from;
        v = Edge[i].to;
        int bu = Belong[u];
        int bv = Belong[v];
        if(bu == bv) continue;
        Kag[bu].push_back(bv);
        ++Deg[bv];
    }

    llt ans = 0;
    for(int i=1;i<=SCCCnt;++i){
        if(Deg[i]) continue;

        llt tmp = f(i);
        ans = max(ans, tmp);
    }

    llt sum = 0;
    for(auto p : Cnt){
        sum += (llt)p.first * p.second;
    }
    cout << sum - ans << endl;
    return 0;
}
