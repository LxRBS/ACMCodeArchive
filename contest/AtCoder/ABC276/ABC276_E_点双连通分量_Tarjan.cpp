/**
 * 一个二维数组，#表示障碍物，点表示通路，S表示起点
 * 问是否存在从S开始且到S结束的简单路径，且长度大于等于4
 * 考虑到二维数组的图，如果S最多关联4条边，只要有任意两条边属于同一个点双，即说明路径存在
 * 模板题
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
int const SIZE = 1E6+13;
#endif

//type of edge's weight
typedef int weight_t;

//just as its names
int const SIZE_OF_VERTICES = SIZE;
int const SIZE_OF_EDGES = SIZE * 8;

struct edge_t{
	int from,to;
	//weight_t weight;
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

//双向边
inline void mkEdge(int a,int b,weight_t w=weight_t()){
	Edge[ECnt].from = a;
	Edge[ECnt].to = b;
	//Edge[ECnt].weight = w;
	Edge[ECnt].next = Vertex[a];
	Vertex[a] = ECnt ++;

	Edge[ECnt].from = b;
	Edge[ECnt].to = a;
	//Edge[ECnt].weight = w;
	Edge[ECnt].next = Vertex[b];
	Vertex[b] = ECnt ++;
}

int Stack[SIZE_OF_EDGES],StackTop;//辅助栈，基于边的
int TimeStamp;
int Dfn[SIZE_OF_VERTICES], Low[SIZE_OF_VERTICES];
int Belong2BiCC[SIZE_OF_EDGES];//边i属于第Bi个双连通分量，从1开始；对点来说，割点可能同时属于多个点双连通
int Represent[SIZE_OF_EDGES];//Ri表示第i个双连通中边数编号最小的边
int BiCCCnt;//双连通分量的数量

void dfs(int u,int pre){
    Dfn[u] = Low[u] = ++TimeStamp;

    int v, edge = 0;
    for(int next=Vertex[u];next;next=Edge[next].next)if( (v=Edge[next].to) != pre ){
        if ( 0 == Dfn[v] ){
            //入栈
            Stack[StackTop++] = next;
            dfs(v,u);
            if ( Low[v] < Low[u] ) Low[u] = Low[v];

            //说明u是割点，栈内的边都属于同一个点双连通
            if ( Dfn[u] <= Low[v] ){
                ++BiCCCnt;
                do{
                    Belong2BiCC[edge = Stack[--StackTop]] = BiCCCnt;
                    Belong2BiCC[edge^1] = BiCCCnt;
                    if ( 0 == Represent[BiCCCnt] || edge < Represent[BiCCCnt] ) Represent[BiCCCnt] = edge;
                }while( edge != next );
            }
        }else if ( v != pre && Dfn[v] < Dfn[u] ){
            Low[u] = min(Low[u],Dfn[v]);
            Stack[StackTop++] = next;
        }
    }
}

void Tarjan(int vn){
    fill(Dfn,Dfn+vn+1,0);
    fill(Belong2BiCC,Belong2BiCC+ECnt,0);
    fill(Represent,Represent+ECnt,0);
    TimeStamp = BiCCCnt = StackTop = 0;
    for(int i=1;i<=vn;++i)if ( 0 == Dfn[i] )dfs(i,i);
}

int H, W;
char A[SIZE_OF_VERTICES];

bool proc(){
    int vn = H*W;
    initGraph(vn);
    char * ch;
    int idx;
    vector<int> es; // 保存跟起点有关的边的编号
    for(int i=0;i<H;++i)for(int j=0;j<W;++j){
        if('#' == *(ch=A+(idx=i*W+j))) continue;

        ++idx;
        if(i != H - 1 && '#' != *(ch+W)){           
            if('S' == *(ch+W) || 'S' == *ch) es.push_back(ECnt); 
            mkEdge(idx, idx+W);
        }
        if(j != W - 1 && '#' != *(ch + 1)){
            if('S' == *(ch+1) || 'S' == *ch) es.push_back(ECnt);
            mkEdge(idx, idx + 1);
        }

        
    }
    assert(es.size() <= 4);
    if(es.size() <= 1) return false;

    Tarjan(vn);
    set<int> ss;
    for(auto i : es){
        if(ss.count(Belong2BiCC[i])) return true;
        ss.insert(Belong2BiCC[i]);
    }
    return false;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r" ,stdin);
#endif
    scanf("%d%d", &H, &W);
    char * p = A;
    for(int i=0;i<H;++i) {
        scanf("%s", p);
        p += W;    
    }
    puts(proc()?"Yes":"No");
    return 0;
}