/*
    N�����ӣ�M����Ӧ�̣�K����Ʒ
    ��Ӧ�̹�Ӧ��������֪
    ����������������֪
    �����ӹ�Ӧ���û���Ҫ����
    ���ܷ�Ӧ����������С����
*/

#include <stdio.h>
#include <queue>
#include <utility>
#include <algorithm>
using namespace std;

typedef int weight_t;

int const SIZE_OF_VERTICES = 100010;//���������ֵ
int const SIZE_OF_EDGES = 100010<<2;//���������ֵ
weight_t const INF = 0x3f3f3f3f;

struct edge_t{
    int from,to;
    weight_t cap;//����
    weight_t cost;//����
    int next;
}Edge[SIZE_OF_EDGES];
int ECnt;

int Vertex[SIZE_OF_VERTICES];

//��ʼ��
inline void initGraph(int n){
    ECnt = 2;//ECnt��2��ʼ����ָ����0��ʾ���������^1����
    fill(Vertex,Vertex+n+1,0);
}

//���ɱ�
inline void mkEdge(int a,int b,weight_t capa,weight_t cost){
    Edge[ECnt].from = a;
    Edge[ECnt].to = b;
    Edge[ECnt].cap = capa;
    Edge[ECnt].cost = cost;
    Edge[ECnt].next = Vertex[a];
    Vertex[a] = ECnt++;

    Edge[ECnt].from = b;
    Edge[ECnt].to = a;
    Edge[ECnt].cap = 0;
    Edge[ECnt].cost = -cost;
    Edge[ECnt].next = Vertex[b];
    Vertex[b] = ECnt++;
}

//s��ʾԴ��vnΪ��������������Ϊ��������
void spfa(int s,int vn,weight_t d[],int pre[],bool flag[]){
    fill(d,d+vn+1,INF);
    fill(flag,flag+vn+1,false);
    fill(pre,pre+vn+1,0);

    queue<int> q;
    q.push(s);

    d[s] = 0;
    flag[s] = true;

    int u,v;
    weight_t tmp;
    while( !q.empty() ){
        flag[ u = q.front() ] = false;
        q.pop();

        for(int p=Vertex[u];p;p=Edge[p].next){
            if ( Edge[p].cap > 0 && ( tmp = d[u] + Edge[p].cost ) < d[ v=Edge[p].to ] ){
                d[v] = tmp;pre[v] = p;
                if ( !flag[v] ) q.push(v), flag[v] = true;
            }
        }
    }
}

//��С�����������sΪԴ��tΪ�㣬vnΪ�ܵ���
//����Ϊ��������
pair<weight_t,weight_t> mcmf(int s,int t,int vn,weight_t d[],int pre[],bool flag[]){
    weight_t miniCost = 0;
    weight_t maxFlow = 0;
    while(1){
        spfa(s,vn,d,pre,flag);
        //˵���Ҳ�������·
        if ( INF == d[t] ) break;

        //�ҳ�������·�ϵĿ�����
        weight_t curFlow = INF;
        for(int p=pre[t];p;p=pre[Edge[p].from])if(curFlow>Edge[p].cap)curFlow = Edge[p].cap;

        //�䶯����
        for(int p=pre[t];p;p=pre[Edge[p].from]){
            Edge[p].cap -= curFlow;
            Edge[p^1].cap += curFlow;
        }

        //���������ͷ���
        miniCost += d[t] * curFlow;
        maxFlow += curFlow;
    }

    return make_pair(maxFlow,miniCost);
}

int N,M,K;
int Need[55][55],Supply[55][55],Cost[55][55][55];
int TotalNeed[55];
bool read(){
    scanf("%d%d%d",&N,&M,&K);
    if ( 0 == N && 0 == M && 0 == K ) return false;

    fill(TotalNeed,TotalNeed+K+1,0);
    for(int i=1;i<=N;++i)for(int j=1;j<=K;++j)scanf("%d",Need[i]+j),TotalNeed[j]+=Need[i][j];
    for(int i=1;i<=M;++i)for(int j=1;j<=K;++j)scanf("%d",Supply[i]+j);
    for(int k=1;k<=K;++k)for(int i=1;i<=N;++i)for(int j=1;j<=M;++j)scanf("%d",Cost[k][i]+j);

    return true;
}

int D[200],Pre[200];
bool Flag[200];

int main(){
    //freopen("1.txt","r",stdin);
    while( read() ){
        int s,t,ans = 0;

        //��ÿһ����Ʒ������ͼ����
        for(int k=1;k<=K;++k){
            s = N + M + 1;
            initGraph(t=N+M+2);

            //S����Ӧ����һ����
            for(int i=1;i<=M;++i) mkEdge(s,i,Supply[i][k],0);

            //���ӵ�T��һ����
            for(int i=1;i<=N;++i) mkEdge(i+M,t,Need[i][k],0);

            //��Ӧ�̵�������һ����
            for(int i=1;i<=N;++i)for(int j=1;j<=M;++j)mkEdge(j,i+M,INF,Cost[k][i][j]);

            pair<int,int> pp = mcmf(s,t,t,D,Pre,Flag);

            if ( TotalNeed[k] != pp.first ){
                ans = -1;
                break;
            }

            ans += pp.second;
        }

        printf("%d\n",ans);
    }
    return 0;
}
