/*
����N���������ÿ��������Ҫִ��p�죬����е�ʱ�����[s,e]֮��
ֻ��M����������ִ������
���Ƿ����
*/
#include <cstdio>
#include <algorithm>
using namespace std;

typedef int weight_t;

int const SIZE_OF_VERTICES = 2000;//���������ֵ
int const SIZE_OF_EDGES = 100010<<2;//���������ֵ
weight_t const INF = 0x3f3f3f3f;

struct edge_t{
    int to;
    weight_t cap;//����
    weight_t flow;//����
    int next;
}Edge[SIZE_OF_EDGES];//ע����MAXM
int ECnt;

int Vertex[SIZE_OF_VERTICES];

//��ʼ��
inline void initGraph(int n){
    ECnt = 2;//ECnt��2��ʼ����ָ����0��ʾ���������^1����
    fill(Vertex,Vertex+n+1,0);
}

//���ɱ�
inline void mkEdge(int a,int b,weight_t w){
    Edge[ECnt].to = b;
    Edge[ECnt].cap = w;
    Edge[ECnt].flow = 0;
    Edge[ECnt].next = Vertex[a];
    Vertex[a] = ECnt++;

    Edge[ECnt].to = a;
    Edge[ECnt].cap = 0;//�����
    Edge[ECnt].flow = 0;
    Edge[ECnt].next = Vertex[b];
    Vertex[b] = ECnt++;
}

int D[SIZE_OF_VERTICES];//Di��ʾi����ľ���
int Cnt[SIZE_OF_VERTICES];//Cnti��ʾ����Ϊi�Ķ���ĸ���
int Queue[SIZE_OF_VERTICES];//��������

//����BFS���������㵽��ľ��룬tΪ�㣬nΪ��������
void bfs(int t,int n){
    fill(D,D+n+1,-1);
    fill(Cnt,Cnt+n+1,0);

    int u,v, head = 0, tail = 0;
    Cnt[ D[ Queue[tail++]=t ] = 0 ] = 1;

    while(head != tail){
        for(int p = Vertex[ u = Queue[head++] ]; p ; p = Edge[p].next){
            if ( -1 == D[ v = Edge[p].to ] ){
                ++ Cnt[ D[ Queue[tail++]=v ] = D[u] + 1 ];
            }
        }
    }
}

int Cur[SIZE_OF_VERTICES];//��ǰ��
int Stack[SIZE_OF_VERTICES];//����ջ

//Improved shortest argument path algorithm
//sΪԴ��tΪ�㣬nΪ�������
weight_t isap(int s,int t,int n){
    bfs(t,n);
    copy(Vertex,Vertex+n+1,Cur);

    weight_t ans = 0;
    int u = s, top = 0;

    while(D[s] < n){
        if(u == t){//�ҵ�һ������·
            int inser,flow = INF;
            weight_t wtmp;
            for(int i=0;i<top;++i)if( flow > ( wtmp = Edge[Stack[i]].cap - Edge[Stack[i]].flow ) ){
                flow = wtmp, inser = i;
            }
            for(int i=0;i<top;++i){
                Edge[Stack[i]].flow += flow;  //�����
                Edge[Stack[i]^1].flow -= flow;//�����
            }
            ans += flow;
            top = inser;
            u = Edge[Stack[top]^1].to;
            continue;
        }

        //���ҿ��л�
        int v, ava = 0;
        for(int p=Cur[u];p;p=Edge[p].next){
            if(Edge[p].cap - Edge[p].flow && D[ v = Edge[p].to ] + 1 == D[u]){
                Cur[u] = ava = p;
                break;
            }
        }

        if(ava){//�ҵ����л��Ժ��ƽ�
            Stack[top++] = Cur[u];
            u = v;
            continue;
        }

        //�Ҳ������л�������
        int tmpd = n;
        for(int p=Vertex[u];p;p=Edge[p].next)
        if( Edge[p].cap - Edge[p].flow && D[Edge[p].to] < tmpd ){
            tmpd = D[Edge[p].to];
            Cur[u] = p;
        }
        --Cnt[D[u]];

        if(!Cnt[D[u]])return ans;

        ++Cnt[ D[u] = tmpd + 1 ];

        if(u != s) u = Edge[Stack[--top]^1].to;
    }

    return ans;
}

int N,M;
int SRC,DST;
int TotalDays;
void read(){
    scanf("%d%d",&N,&M);

    initGraph(N+500+2);

    SRC = N+500+1;
    DST = SRC + 1;
    TotalDays = 0;

    //��ÿһ�쵽�㽨һ����
    for(int i=1;i<=500;++i) mkEdge(i+N,DST,M);

    int p,s,e;
    for(int i=1;i<=N;++i){
        scanf("%d%d%d",&p,&s,&e);
        TotalDays += p;

        //��ÿ�����񣬴�Դ����һ����
        mkEdge(SRC,i,p);

        //ÿ������ִ�е�ʱ��ν���һ����
        for(int j=s;j<=e;++j) mkEdge(i,j+N,1);
    }

}

int main(){
    //freopen("1.txt","r",stdin);
    int nofkase;
    scanf("%d",&nofkase);
    for(int kase=1;kase<=nofkase;++kase){
        read();
        printf("Case %d: ",kase);
        printf(isap(SRC,DST,N+500+2)==TotalDays?"Yes\n\n":"No\n\n");
    }
    return 0;
}
