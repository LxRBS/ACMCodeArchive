/**
   �����޻�ͼ��N���㣬M����
   ���ĳ����һ����3�ַ���
   1 ���������ǰ����ÿ������һ�����ۣ�����Wi
   2 ɾ����������ߣ�ÿ������һ�����ۣ�����wij
   3 ����ֱ�ӷ��ã�����Ke
   3�ַ������Ի��ʹ�ã��ʻ��S����С�����Ƕ���
   ����С������ģ���������������ʵ��
   ����ÿ����u�������u��u'
   1 Դ��u��һ���ߣ�����ΪWu
   2 ���v��u��ǰ������v'��u��һ���ߣ�������wij
   3 u��u'�����ߣ�������Ke[u]
   �����Դ��S'�����������
*/
#include <stdio.h>
#include <queue>
#include <algorithm>
using namespace std;

int getUnsigned(){
	char ch = getchar();
	while( ch < '0' || ch > '9' ) ch = getchar();

	int ret = (int)(ch-'0');
	while( '0' <= ( ch = getchar() ) && ch <= '9' ) ret = ret * 10 + (int)(ch-'0');
	return ret;
}

//*
typedef int weight_t;

int const SIZE_OF_VERTICES = 1200;//���������ֵ
int const SIZE_OF_EDGES = 10010<<2;//���������ֵ
weight_t const INF = 0x3f3f3f3f;

struct edge_t{
    int to;
    weight_t cap;//����
    weight_t flow;//����
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
inline void mkEdge(int a,int b,weight_t w){
    Edge[ECnt].to = b;
    Edge[ECnt].cap = w;
    Edge[ECnt].flow = 0;
    Edge[ECnt].next = Vertex[a];
    Vertex[a] = ECnt++;

    Edge[ECnt].to = a;
    Edge[ECnt].cap = 0;//����ͼ�ķ����Ϊ0������ͼ�ķ����ͬ�����
    Edge[ECnt].flow = 0;
    Edge[ECnt].next = Vertex[b];
    Vertex[b] = ECnt++;
}

int __D[SIZE_OF_VERTICES];//Di��ʾi����ľ���
int __Cnt[SIZE_OF_VERTICES];//Cnti��ʾ����Ϊi�Ķ���ĸ���
int Queue[SIZE_OF_VERTICES];//��������

//����BFS���������㵽��ľ��룬tΪ�㣬nΪ��������
void bfs(int t,int n){
    fill(__D,__D+n+1,-1);
    fill(__Cnt,__Cnt+n+1,0);

    int u,v, head = 0, tail = 0;
    __Cnt[ __D[ Queue[tail++]=t ] = 0 ] = 1;

    while(head != tail){
        for(int p = Vertex[ u = Queue[head++] ]; p ; p = Edge[p].next){
            if ( -1 == __D[ v = Edge[p].to ] ){
                ++ __Cnt[ __D[ Queue[tail++]=v ] = __D[u] + 1 ];
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

    while(__D[s] < n){
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
            if(Edge[p].cap - Edge[p].flow && __D[ v = Edge[p].to ] + 1 == __D[u]){
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
        if( Edge[p].cap - Edge[p].flow && __D[Edge[p].to] < tmpd ){
            tmpd = __D[Edge[p].to];
            Cur[u] = p;
        }
        --__Cnt[__D[u]];

        if(!__Cnt[__D[u]])return ans;

        ++__Cnt[ __D[u] = tmpd + 1 ];

        if(u != s) u = Edge[Stack[--top]^1].to;
    }

    return ans;
}
//*/

int N,M,S;

int main(){
    //freopen("1.txt","r",stdin);
    int nofkase = getUnsigned();
    while(nofkase--){
        N = getUnsigned();
        M = getUnsigned();
        S = getUnsigned();

        //n��ʾͼ�Ķ�������
        int n = (N<<1)|1;
        initGraph(n);

        int a,b,w;
        for(int i=0;i<M;++i){
            a = getUnsigned();
            b = getUnsigned();
            //a'��b��һ����
            mkEdge(a+N,b,getUnsigned());
        }
        for(int i=1;i<=N;++i){
            //Դ��i��һ����
            mkEdge(n,i,getUnsigned());
        }
        for(int i=1;i<=N;++i){
            //i��i'��һ����
            mkEdge(i,i+N,getUnsigned());
        }

        printf("%d\n",isap(n,S+N,n));
    }
    return 0;
}
