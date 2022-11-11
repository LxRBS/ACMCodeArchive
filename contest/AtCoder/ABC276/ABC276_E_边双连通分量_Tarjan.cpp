/**
 * 一个二维数组，#表示障碍物，点表示通路，S表示起点
 * 问是否存在从S开始且到S结束的简单路径，且长度大于等于4
 * 考虑到二维数组的图，如果S存在于一个点数不少于4的边双连通分量，则路径存在
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

int Stack[SIZE_OF_VERTICES],StackTop;//辅助栈
int TimeStamp;
int Dfn[SIZE_OF_VERTICES], Low[SIZE_OF_VERTICES];
//bool IsBridge[SIZE_OF_EDGES];//边i是否为桥
bool IsVisited[SIZE_OF_EDGES];//边的标记数组，有重边时需用此数组进行判断
int Belong2BiCC[SIZE_OF_VERTICES];//点i属于第Bi个双连通分量，从1开始
int Represent[SIZE_OF_VERTICES];//Ri表示第i个边双的代表，也就是编号最小的那个点
int BiCCCnt;//双连通分量的数量

void dfs(int u,int pre){
    Dfn[u] = Low[u] = ++TimeStamp;

    //入栈
    Stack[StackTop++] = u;

    //对u的每一条边
    int v,son=0;
    for(int next=Vertex[u];next;next=Edge[next].next)if( !IsVisited[next] ){
        IsVisited[next] = IsVisited[next^1] = true;

        if ( 0 == Dfn[v=Edge[next].to] ){
            ++son;
            dfs(v,u);
            if ( Low[v] < Low[u] ) Low[u] = Low[v];

            /*//桥
            if ( Dfn[u] < Low[v] ){
                IsBridge[next] = IsBridge[next^1] = true;
            }
            //*/

        }else if ( Dfn[v] < Low[u] ){
            Low[u] = Dfn[v];
        }
    }

    if ( Low[u] == Dfn[u] ){//u和其上的点在同一个分量中
        Represent[Belong2BiCC[u] = ++BiCCCnt] = u;
        do{
            Belong2BiCC[v=Stack[--StackTop]] = BiCCCnt;
            if ( v < Represent[BiCCCnt] ) Represent[BiCCCnt] = v;
        }while( v != u );
    }
}

void Tarjan(int vn){
    fill(Dfn,Dfn+vn+1,0);
    fill(Belong2BiCC,Belong2BiCC+vn+1,0);
    fill(IsVisited,IsVisited+ECnt,false);
    //fill(IsBridge,IsBridge+ECnt,false);
    BiCCCnt = StackTop = 0;

    TimeStamp = 0;

    for(int i=1;i<=vn;++i)if ( 0 == Dfn[i] )dfs(i,i);
}


int H, W;
char A[SIZE_OF_VERTICES];

bool proc(){
    int vn = H*W;
    initGraph(vn);
    char * ch;
    int idx;
    int sidx = -1;
    for(int i=0;i<H;++i)for(int j=0;j<W;++j){
        if('#' == *(ch=A+(idx=i*W+j))) continue;

        ++idx;
        if(i != H - 1 && '#' != *(ch+W)){            
            mkEdge(idx, idx+W);
        }
        if(j != W - 1 && '#' != *(ch + 1)){
            mkEdge(idx, idx + 1);
        }

        if('S' == *ch) sidx = idx;
    }
    assert(sidx != -1);

    Tarjan(vn);
    int cnt = 0;
    for(int i=1;i<=vn;++i){
        if(Belong2BiCC[i] == Belong2BiCC[sidx]){
            if(++cnt >= 4) return true;            
        }
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