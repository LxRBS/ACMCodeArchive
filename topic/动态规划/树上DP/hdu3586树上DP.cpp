/*
    һ������Ҫ�г�һЩ�ߣ�ʹ��ÿ��Ҷ�Ӷ�����������
    �г��ߵ��ܷ��ò��ܳ���m
    ����������£�Ҫ���г��ߵ���������С

    ���г�������limit
    ��DiΪ�ж�i��������Ҷ�������С�����ܺͣ���
          SIGMA(min(wij,Dj)) wij<=limit��j��i�Ķ���
    Di =
          SIGMA(Dj) wij>limit��j��i�Ķ���

    ÿ����һ�����ޣ����Լ����Di��������������
*/

#include <stdio.h>
#include <string.h>
#include <algorithm>

using namespace std;

typedef long long llt;

int const SIZE = 2100;
llt const INF = 100000000;

struct edge_t{
    int from,to;
    int weight;
    int next;
}Edge[SIZE];
int ECnt;
int Vertex[SIZE];

inline void initTree(int n){
    fill(Vertex,Vertex+n+1,0);
    ECnt = 1;
}

inline void mkEdge(int a,int b,int w){
    Edge[ECnt].from = a;
    Edge[ECnt].to = b;
    Edge[ECnt].weight = w;
    Edge[ECnt].next = Vertex[a];
    Vertex[a] = ECnt++;
}

int N,M;
llt D[SIZE];
int Limit;

void dfs(int u){
    //�ж��Ƿ�ΪҶ��
    if ( 0 == Vertex[u] ){
        D[u] = INF;
        return;
    }

    D[u] = 0LL;
    for(int v,w,next=Vertex[u];next;next=Edge[next].next){
        dfs(v=Edge[next].to);

        D[u] += (w=Edge[next].weight) <= Limit ? min((llt)w,D[v]) : D[v];
    }
}

//��limit��Ϊ���ޣ��Ƿ����������
bool check(int limit){
    Limit = limit;
    dfs(1);
    return D[1] <= M;
}

int proc(){
    int left = 0, right = 1010, mid;
    do{
        mid = ( left + right ) >> 1;
        if ( check(mid) ) right = mid - 1;
        else left = mid + 1;
    }while(left<=right);
    return left<=1000?left:-1;
}

int main(){
    //freopen("1.txt","r",stdin);

    int a,b,w;
    while( scanf("%d%d",&N,&M),N ){
        initTree(N);
        for(int i=1;i<N;++i){
            scanf("%d%d%d",&a,&b,&w);
            mkEdge(a,b,w);
        }

        printf("%d\n",proc());
    }

    return 0;
}
