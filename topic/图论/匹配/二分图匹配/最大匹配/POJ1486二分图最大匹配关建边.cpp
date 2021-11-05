/*
    若干个矩形叠在一起，每个矩形上有一个数字
    给定坐标问哪些矩形和数字可以唯一确定
    最大匹配的关建边
    关建边即构成最大匹配所必需的边
    将其删除，则剩下的最大匹配就比原来少1
*/

#include <stdio.h>
#include <algorithm>
using namespace std;

//just as its names
int const SIZE_OF_VERTICES = 35;
int const SIZE_OF_EDGES = 20000;
int const INF = 0x3F3F3F3F;

struct edge_t{
	int from,to;
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

//单向边
inline void mkEdge(int a,int b){
	Edge[ECnt].from = a;
	Edge[ECnt].to = b;
	Edge[ECnt].next = Vertex[a];
	Vertex[a] = ECnt ++;
}

int TA,TB;//表示剔除的关建边

int LinkA[SIZE_OF_VERTICES];//LinkAi is the link of Ai in B
int LinkB[SIZE_OF_VERTICES];//LinkBi is the link of Bi in A

int DA[SIZE_OF_VERTICES],DB[SIZE_OF_VERTICES];//A部分的距离，B部分的距离
int _Q[SIZE_OF_VERTICES];//辅助队列
int _Dis;
bool bfs(int na,int nb){
    fill(DA,DA+na+1,0);
    fill(DB,DB+nb+1,0);

    int *head = _Q, *tail = _Q;
    for(int i=1;i<=na;++i) if ( !LinkA[i] ) *tail++ = i;//入队

    _Dis = INF;
    int u,v;
    while( head < tail ){
        if ( DA[u = *head++] > _Dis ) continue;

        for(int p=Vertex[u];p;p=Edge[p].next)if(TA!=Edge[p].from||TB!=Edge[p].to){
            if ( 0 == DB[ v = Edge[p].to ] ){
                DB[v] = DA[u] + 1;
                if ( LinkB[v] ) DA[ *tail++ = LinkB[v] ] = DB[v] + 1;
                else _Dis = DB[v];
            }
        }
    }
    return _Dis < INF;
}

bool _Flag[SIZE_OF_VERTICES];//辅助标记数组
bool dfs(int u){
    int v;
    for(int p=Vertex[u];p;p=Edge[p].next)if(TA!=Edge[p].from||TB!=Edge[p].to){
        if ( !_Flag[v=Edge[p].to] && DB[v] == DA[u] + 1 ){
            _Flag[v] = true;
            if ( !LinkB[v] || ( DB[v] != _Dis && dfs(LinkB[v]) ) ){
                LinkA[ LinkB[v] = u ] = v;
                return true;
            }
        }
    }
    return false;
}

//na是A的数量，nb是B的数量
int HopcroftKarp(int na,int nb){
	fill(LinkA,LinkA+na+1,0);
	fill(LinkB,LinkB+nb+1,0);

    int ret = 0;
    while( bfs(na,nb) ){
        fill(_Flag,_Flag+nb+1,false);
        for(int i=1;i<=na;++i){
            if ( !LinkA[i] ) ret += dfs(i);
        }
    }
    return ret;
}

int getInt(){
	int sgn = 1;
	char ch = getchar();
	while( ch != '-' && ( ch < '0' || ch > '9' ) ) ch = getchar();
	if ( '-' == ch ) {sgn = 0;ch=getchar();}

	int ret = (int)(ch-'0');
	while( '0' <= (ch=getchar()) && ch <= '9' ) ret = ret * 10 + (int)(ch-'0');
	return sgn ? ret : -ret;
}

int Xmin[30],Ymin[30],Xmax[30],Ymax[30];
int TLink[30];
int main(){
    //freopen("1.txt","r",stdin);
    int n,x,y;
    for(int kase=1;n = getInt();++kase){
        TA = TB = 0;
        initGraph(n);
        for(int i=1;i<=n;++i) Xmin[i] = getInt(),Xmax[i] = getInt(), Ymin[i] = getInt(), Ymax[i] = getInt();
        for(int i=1;i<=n;++i){
            x = getInt(), y = getInt();
            for(int j=1;j<=n;++j){
                if ( Xmin[j] <= x && x <= Xmax[j] && Ymin[j] <= y && y <= Ymax[j] ) mkEdge(j,i);
            }
        }

        printf("Heap %d\n",kase);

        int ans = HopcroftKarp(n,n);
        bool flag = true;
        copy(LinkA,LinkA+n+1,TLink);
        for(int i=1;i<=n;++i){
            TA = i, TB = TLink[i];
            if ( HopcroftKarp(n,n) < ans ){
                printf("(%c,%d) ",'A'-1+i,TB);
                flag = false;
            }
        }
        if ( flag ) printf("none");
        printf("\n\n");
    }
    return 0;
}
