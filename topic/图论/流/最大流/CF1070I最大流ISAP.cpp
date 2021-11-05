/**
    һ��ͼ��Ҫ��
    1 ÿ����Ⱦһ����ɫ��һ����100500����ɫ
    2 ÿ����ɫ���Ⱦ������
    3 ÿ���������k����ɫ�ı�����
    �����ͱ�����600�������ɫ����������Ϊ�����k�ڵ�������
    ��ÿһ���㣬�����������2k�����Ȼʧ��
    �������С�ڵ���k����������迼��
    ���ڶ�����(k, 2k]�ĵ㣬��Ȼ��i-k�Ա���ɫ����ͬ�ģ��ɶԳ��֣���ֻ�����������
    ���Զ���ÿ���㣬Ҫ��2*(i-k)����ƥ��
    ������һ������ƥ�����⣬��������������
    ����ܹ��ܳ����������ƥ��ı�ÿһ��Ⱦһ����ɫ��ʣ�µı�����Ⱦ��ͬ��ɫ����
    ISAPֱ��������߼����ж������ʱ������Щ��
*/
#include <bits/stdc++.h>
using namespace std;

typedef int llt;

int getUnsigned(){
	char ch = getchar();
	while( ch < '0' || ch > '9' ) ch = getchar();

	int ret = (int)(ch-'0');
	while( '0' <= ( ch = getchar() ) && ch <= '9' ) ret = ret * 10 + (int)(ch-'0');
	return ret;
}

typedef int weight_t;

int const SIZE_OF_VERTICES = 100010;//���������ֵ
int const SIZE_OF_EDGES = 100010<<2;//���������ֵ
weight_t const INF = 0x3f3f3f3f;

struct edge_t{
    int from, to;
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
    Edge[ECnt].from = a;
    Edge[ECnt].to = b;
    Edge[ECnt].cap = w;
    Edge[ECnt].flow = 0;
    Edge[ECnt].next = Vertex[a];
    Vertex[a] = ECnt++;

    Edge[ECnt].from = b;
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
            int inser;
            weight_t wtmp,flow = INF;
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

typedef pair<int,int> pii;
int N,M,K;
int Degree[610];
vector<int> Dian;
vector<int> E[610];
vector<int> Ans[610];

bool f_degree(){
    for(int i=1,k2=K+K;i<=N;++i){
        if(Degree[i]>k2) return false;
        if(Degree[i]>K) Dian.push_back(i);
    }
    return true;
}

int main(){
    //freopen("1.txt","r",stdin);
    int nofkase = getUnsigned();
    while(nofkase--){
        N = getUnsigned();
        M = getUnsigned();
        K = getUnsigned();

        fill(Degree,Degree+N+1,0);
        for(int i=1;i<=N;++i){
            E[i].clear();
            Ans[i].clear();
        }
        Dian.clear();

        for(int a,b,i=1;i<=M;++i){
            ++Degree[a = getUnsigned()];
            ++Degree[b = getUnsigned()];
            E[a].push_back(i);
            E[b].push_back(i);
        }

        ///ͳ�Ƶ�Ķ���
        if(!f_degree()){//�޽�
            printf("0");
            for(int i=1;i<M;++i)printf(" 0");
            printf("\n");
            continue;
        }

        ///��ͼ
        int vn = N + M + 2;
        int s = vn - 1, t = vn;
        initGraph(vn);
        ///��ÿһ����
        int tmp = 0;
        for(auto i: Dian){
            ///��ÿһ�����������ı�
            for(auto j: E[i]){
                mkEdge(i, j+N, 1);
            }
            ///��㵽����һ����
            mkEdge(s, i, (Degree[i]-K)*2);
            tmp += (Degree[i]-K)*2;
        }
        ///ÿ���ߵ��յ���һ����
        for(int i=1;i<=M;++i){
            mkEdge(i+N, t, 1);
        }
        ///��һ�������
        weight_t ans = isap(s, t, vn);
        if(ans!=tmp){//�޽�
            printf("0");
            for(int i=1;i<M;++i)printf(" 0");
            printf("\n");
            continue;
        }
        ///�н⣬��鷴��ߣ����õ���һ��
        for(auto i: Dian){
            ///����i��ص�ÿһ��������ߣ�����Ƿ�ʹ��������
            for(int p=Vertex[i];p;p=Edge[p].next)if(!(p&1)){
                if(Edge[p].flow==1){
                    Ans[i].push_back(Edge[p].to-N);
                }
            }
        }
        ///���
        int c[610]={0},cc=0;
        for(auto i: Dian){
                /*
            printf("%d %d\n",i, (int)Ans[i].size());
            for(auto j: Ans[i]){
                printf("%d ",j);
            }
            printf("\n");//*/
            int tmp = 2*(Degree[i]-K);

            for(unsigned j=0,n=Ans[i].size();j<n;j+=2){
                if(j<tmp){
                    c[Ans[i][j]] = ++cc;
                    c[Ans[i][j+1]] = cc;
                }
            }
        }
        ///ʣ�µ�
        for(int i=1;i<=M;++i)if(0==c[i])c[i] = ++cc;
        printf("%d", c[1]);
        for(int i=2;i<=M;++i)printf(" %d",c[i]);
        printf("\n");
    }
    return 0;
}
