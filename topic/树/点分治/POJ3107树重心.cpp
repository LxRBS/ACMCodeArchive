/*
    在树上找到这样一个节点
    它的size最大的儿子最小
    实际上就是找重心
*/

#include <stdio.h>
#include <vector>
#include <string.h>
#include <algorithm>

using namespace std;

int const SIZE = 100100;

struct edge_t{
    int from,to;
    int next;
}Edge[SIZE];
int ECnt;
int Vertex[SIZE];

inline void initTree(int n){
    fill(Vertex,Vertex+n+1,0);
    ECnt = 1;
}

inline void mkEdge(int a,int b){
    Edge[ECnt].from = a;
    Edge[ECnt].to = b;
    Edge[ECnt].next = Vertex[a];
    Vertex[a] = ECnt++;
}

int N;
int TmpSize[SIZE];
int T4Center;
vector<int> Ans;

void dfs4Center(int u,int parent){
    TmpSize[u] = 1;

    int tmp = 0;//记录最大的儿子的size
    for(int v,next=Vertex[u];next;next=Edge[next].next){
        if ( (v=Edge[next].to) != parent ){
            dfs4Center(v,u);
            TmpSize[u] += TmpSize[v];
            if ( tmp < TmpSize[v] ) tmp = TmpSize[v];
        }
    }

    //如果把u作为根，parent作为儿子，能够得到的size
    //tmp最后是u的所有可能的儿子的size最大的
    if ( tmp < N - TmpSize[u] ) tmp = N - TmpSize[u];

    //记录答案
    if ( tmp < T4Center ) {
        Ans.clear();
        Ans.push_back(u);
        T4Center = tmp;
    }else if ( tmp == T4Center ){
        Ans.push_back(u);
    }
}

int main(){
    //freopen("1.txt","r",stdin);

    int a,b;
    while( 1 == scanf("%d",&N) ){
        initTree(N);
        for(int i=1;i<N;++i){
            scanf("%d%d",&a,&b);
            mkEdge(a,b);
            mkEdge(b,a);
        }

        T4Center = 100100;
        dfs4Center(1,0);

        sort(Ans.begin(),Ans.end());
        printf("%d",*Ans.begin());
        for(vector<int>::iterator it=++Ans.begin();it!=Ans.end();++it)printf(" %d",*it);
        putchar('\n');
    }

    return 0;
}
