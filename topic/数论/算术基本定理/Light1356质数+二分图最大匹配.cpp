/*
    整数集合称为是质数独立的，
    如果任意元素不是另外一个元素的质数倍
    给定集合，求最大质数独立子集

    求在指定规则下的最大独立子集
    很容易联想到二分图的最大独立集
    但是首先要确定是否能建立二分图

    如果a是b的质数倍，毫无疑问a、b之间有一条边
    如果c也是b的质数倍，c、b之间也有一条边
    如果能够形成二分图，就要求a、c之间必然没有边，这一条是否成立？
    这是成立的
    所以可以构建一个二分图
*/

#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;

//just as its names
int const SIZE_OF_VERTICES = 40010;
int const SIZE_OF_EDGES = 251000;
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
	//Edge[ECnt].from = a;
	Edge[ECnt].to = b;
	Edge[ECnt].next = Vertex[a];
	Vertex[a] = ECnt ++;
}

int LinkA[SIZE_OF_VERTICES];//LinkAi is the link of Ai in B
int LinkB[SIZE_OF_VERTICES];//LinkBi is the link of Bi in A

int DA[SIZE_OF_VERTICES],DB[SIZE_OF_VERTICES];//A部分的距离，B部分的距离
int Q[SIZE_OF_VERTICES];//辅助队列
int _Dis;
bool bfs(int na,int nb){
    fill(DA,DA+na+1,0);
    fill(DB,DB+nb+1,0);

    int *head = Q, *tail = Q;
    for(int i=1;i<=na;++i) if ( !LinkA[i] ) *tail++ = i;//入队

    _Dis = INF;
    int u,v;
    while( head < tail ){
        if ( DA[u = *head++] > _Dis ) continue;

        for(int p=Vertex[u];p;p=Edge[p].next){
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
    for(int p=Vertex[u];p;p=Edge[p].next){
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


//线性筛法
int const SIZE = 500100;//一般只筛到30000+即可
bool isComp[SIZE] = {false};//isComp[i]为真说明i是合数
int P[SIZE];//P[i]为第i个素数，i从0开始
int PCnt = 0;//PCnt记录1~SIZE之间的素数的个数
void sieve(){
    for(int i=2;i<SIZE;++i){
        if ( !isComp[i] ) P[PCnt++] = i;

        for(int j=0;j<PCnt&&i*P[j]<SIZE;++j){
            isComp[i*P[j]] = true;
            if ( 0 == i % P[j] ) break;
        }
    }
}

int N;
int W[40010];
bool Flag[SIZE];

int AIdx[SIZE],BIdx[SIZE];
int ACnt,BCnt;

vector<int>Vec;
typedef vector<int>::iterator vit;

void read(){
    scanf("%d",&N);

    fill(Flag,Flag+SIZE,false);
    for(int i=0;i<N;++i)scanf("%d",W+i),Flag[W[i]] = true;

    ACnt = BCnt = 0;
    fill(AIdx,AIdx+SIZE,0);
    fill(BIdx,BIdx+SIZE,0);

    initGraph(N);

    for(int i=0;i<N;++i){
        //计算Wi的质因子个数
        Vec.clear();
        int ans = 0, a = W[i];
        for(int j=0;P[j]*P[j]<=a;++j){
            if ( 0 == a % P[j] ){
                while( 0 == a % P[j] ) a /= P[j], ++ans;
                Vec.push_back(P[j]);
            }
        }
        if ( a != 1 ) {Vec.push_back(a);++ans;}

        int b;
        if ( ans&1 ){//Wi拥有奇数个质因子，属于二分图的A部
            a = W[i];
            if ( 0 == AIdx[a] ) AIdx[a] = ++ACnt;
            //对每一个可能的质数倍
            for(vit it=Vec.begin();it!=Vec.end();++it){
                if ( Flag[ b = W[i] / *it ] ){
                    if ( 0 == BIdx[b] ) BIdx[b] = ++BCnt;
                    mkEdge(AIdx[a],BIdx[b]);
                }
            }
        }else{
            b = W[i];
            if ( 0 == BIdx[b] ) BIdx[b] = ++BCnt;

            for(vit it=Vec.begin();it!=Vec.end();++it){
                if ( Flag[ a = W[i] / *it ] ){
                    if ( 0 == AIdx[a] ) AIdx[a] = ++ACnt;
                    mkEdge(AIdx[a],BIdx[b]);
                }
            }
        }
    }
}
int main(){
    //freopen("1.txt","r",stdin);
    sieve();

    int nofkase;
    scanf("%d",&nofkase);
    for(int kase=1;kase<=nofkase;++kase){
        read();
        printf("Case %d: %d\n",kase,N-HopcroftKarp(ACnt,BCnt));
    }
    return 0;
}
