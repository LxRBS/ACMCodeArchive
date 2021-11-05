//��������ͼ����ͼ���Ƿ��ܻ��ֳ����ɸ�Hamilton��·����Ҫ���л�·��Ȩֵ����С
//��ÿ�����������������֣������������ͼ��ÿһ�����ƥ��ͱ�ʾ��һ��Hamilton��·

#include <stdio.h>
#include <string.h>
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

int N,M,Vn;
bool read(){
    if (EOF==scanf("%d%d",&N,&M)) return false;

    initGraph(Vn=N+N+2);
    int a,b,c;
    for(int i=0;i<M;++i){
        scanf("%d%d%d",&a,&b,&c);
        mkEdge(a,N+b,1,c);
    }
    for(int i=1;i<=N;++i){
        mkEdge(Vn-1,i,1,0);
        mkEdge(N+i,Vn,1,0);
    }
    return true;
}

int D[SIZE_OF_VERTICES],Pre[SIZE_OF_VERTICES];
bool Flag[SIZE_OF_VERTICES];
int main(){
    pair<int,int> ans;
    while( read() ){
        ans = mcmf(Vn-1,Vn,Vn,D,Pre,Flag);
        if ( N == ans.first ) printf("%d\n",ans.second);
        else printf("-1\n");
    }
    return 0;
}
