/**
    如果字符串a和b，将a中任意两个字母交换就可以得到b
    则称a、b是可以swap的
    给定N个字符串的集合，要求从中找到一个最大的子集，
    使得子集中任意两个字符串都是不可以swap的
    最大独立集，求最大匹配，然后减一下（必须是二分图，一般图不满足这个定理）
    可以证明题目必然是二分图。
    
*/
#include <bits/stdc++.h>
using namespace std;
//just as its names
int const SIZE_OF_VERTICES = 1010;
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

#define mp make_pair
#define fi first
#define se second

int N;
string A[550];
unordered_map<string, int> Dic;
unordered_map<string, int>::iterator It;

int main(){
    //freopen("1.txt","r",stdin);
    cin>>N;
    for(int i=1;i<=N;++i){
        cin>>A[i];
        Dic.insert(mp(A[i], i));
    }

    //建图
    initGraph(N);
    for(int i=1;i<=N;++i){
        string& s = A[i];
        int n = s.length();
        for(int j=0;j<n;++j)for(int k=j+1;k<n;++k){
            swap(s[j], s[k]);
            if((It=Dic.find(s))!=Dic.end()){
                //i到x有一条边
                mkEdge(i, It->se);
            }
            swap(s[j], s[k]);
        }
    }

    int ans = HopcroftKarp(N+N,N+N)/2;
    printf("%d\n", N-ans);
    return 0;
}
