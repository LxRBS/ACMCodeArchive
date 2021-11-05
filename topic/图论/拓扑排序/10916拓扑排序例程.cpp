#include <cstdio>
#include <set>
#include <algorithm>
using namespace std;
#define SIZE 10001

struct edge_t{
    int node;
    edge_t* next;
}Edge[SIZE*100];
edge_t* Vertex[SIZE];
int InDeg[SIZE];

int Ans[SIZE];
int Cnt;
//拓扑排序，n为顶点个数
//直接输出结果
void topoSort(int n){
    Cnt = 0;
    set<int> s;
    for(int i=1;i<=n;++i)
        if ( 0 == InDeg[i] )
            s.insert(i);

    while( !s.empty() ){
        int u = *s.begin();
        Ans[Cnt++] = u;
        s.erase(s.begin());

        //将u指向点入度减一
        edge_t* p = Vertex[u];
        while(p){
            int &v = p->node;
            if ( 0 == --InDeg[v] ) s.insert(v);
            p = p->next;
        }
    }

    if ( n != Cnt ){
        printf("FALSE\n");
        return;
    }

    printf("%d",*Ans);
    for(int i=1;i<Cnt;++i)printf(" %d",Ans[i]);
    printf("\n");
}

int main(){
    int n,m;
    while( EOF != scanf("%d%d",&n,&m) ){
        fill(InDeg,InDeg+n,0);
        fill(Vertex,Vertex+n,(edge_t*)0);

        for(int i=0;i<m;++i){
            int x,y;
            scanf("%d%d",&x,&y);

            Edge[i].node = y;
            Edge[i].next = Vertex[x];
            Vertex[x] = Edge + i;
            ++InDeg[y];
        }
        topoSort(n);
    }
    return 0;
}
