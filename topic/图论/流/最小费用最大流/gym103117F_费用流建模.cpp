/**
    һ������ͼ��ÿ������һ��Ȩֵai���������б߶�һ�����򣬸ĳ�����ͼ��
    ��С��SIGMA(max(0, di-ai))������di�����
    ��Ȼ��ai�Ƚϴ�ĵ�Ӧ�ö����ߣ���һ���ߵ������ڵ�ֻ��ѡһ�������
    ��һ���������������i���ߵ��ڵ���u��v����i��u��i��v�ֱ���һ���ߣ�����Ϊ1������Ϊ0
    S��i��һ���ߣ�����Ϊ1����Ϊ0
    ��ԭͼ�ϵ�ÿ���ڵ�u����T��2���ߣ��ֱ���(au, 0)��(INF, 1)
    �����Ļ�������0�����ߣ������Ժ�����1�����ߣ�ÿ���߸���һ������
*/
#include <bits/stdc++.h>
using namespace std;

char *__abc147, *__xyz258, __ma369[100000];
#define __hv007() ((__abc147==__xyz258) && (__xyz258=(__abc147=__ma369)+fread(__ma369,1,100000,stdin),__abc147==__xyz258) ? EOF : *__abc147++)

int getUnsigned(){
	char ch = __hv007();
	while( ch < '0' || ch > '9' ) ch = __hv007();

	int ret = (int)(ch-'0');
	while( '0' <= ( ch = __hv007() ) && ch <= '9' ) ret = (ret<<1) + (ret<<3) + (int)(ch-'0');
	return ret;
}

typedef int weight_t;

int const SIZE_OF_VERTICES = 1550;//���������ֵ
int const SIZE_OF_EDGES = 15000;//���������ֵ
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

#define mp make_pair
#define fi first
#define se second

typedef pair<int,int> pii;

int N,M,S,T;
weight_t D[SIZE_OF_VERTICES];
int Pre[SIZE_OF_VERTICES];
bool Flag[SIZE_OF_VERTICES];

int main(){
    //freopen("1.txt","r",stdin);
    int nofkase = getUnsigned();
    while(nofkase--){
        N = getUnsigned();
        M = getUnsigned();
        initGraph(T=N+M+2);
        S = T - 1;

        /// �㵽T��һ����
        for(int ai,i=1;i<=N;++i){
            mkEdge(i, T, getUnsigned(), 0);
            mkEdge(i, T, INF, 1);
        }

        /// ��i���ߵ��ڵ��б�
        for(int u,v,i=1;i<=M;++i){
            u = getUnsigned();
            v = getUnsigned();
            mkEdge(N+i, u, 1, 0);
            mkEdge(N+i, v, 1, 0);
        }

        /// S����һ������һ����
        for(int i=N+1;i<=N+M;++i){
            mkEdge(S, i, 1, 0);
        }

        pii pp = mcmf(S, T, T, D, Pre, Flag);
        printf("%d\n", pp.se);
        /// ���ÿ���ߵĳ��򣬱���Ŵ�2��ʼ
        for(int u,v,i=2+4*N;i<2+4*N+4*M;i+=4){
            u = i ^ 1;     // �鿴����߱ȽϺ�
            v = (i+2) ^ 1;
            if(Edge[u].cap+Edge[v].cap!=1){
                throw runtime_error("not 1");
            }
            if(Edge[u].cap){ // ˵��u���ˣ�ָ��u
                putchar('1');
            }else if(Edge[v].cap){
                putchar('0');
            }else{
                throw runtime_error("XXXX");
            }
        }
        puts("");
    }
    return 0;
}
