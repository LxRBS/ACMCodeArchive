/**
    һ��������������һ��Ȩֵ
    �����ɸ������˿��Դ�ĳЩ�������Ȼ��ĳЩ����Ϊ�յ�
    ������ֻ�����һ���������
    ������ܹ���õ�Ȩֵ���Ƕ���
*/
#include <bits/stdc++.h>
using namespace std;

typedef long long llt;

int getUnsigned(){
	char ch = getchar();
	while( ch < '0' || ch > '9' ) ch = getchar();

	int ret = (int)(ch-'0');
	while( '0' <= ( ch = getchar() ) && ch <= '9' ) ret = ret * 10 + (int)(ch-'0');
	return ret;
}

typedef llt weight_t;
typedef pair<int, weight_t> pii;

int const SIZE_OF_VERTICES = 100010;//���������ֵ
int const SIZE_OF_EDGES = 100010<<2;//���������ֵ
weight_t const INF = 2000000000000000LL;

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

int VN;
weight_t D[SIZE_OF_VERTICES];
int Pre[SIZE_OF_VERTICES];
bool Flag[SIZE_OF_VERTICES];

llt const M3 = 1000000000LL;

int main(){
    //freopen("1.txt","r",stdin);
    int a = getUnsigned();
    int b = getUnsigned();
    int p = getUnsigned();
    int q = getUnsigned();

    ///��ʼ��
    initGraph(VN=(p+1)*(q+1)+2);
    int s = VN - 1, t = VN; //����յ�

    ///ͼ�еĵ��ˮƽ��ʼ���
    ///1,2,3,...,q+1
    ///(q+1)+1,(q+1)+2,...,(q+1)+q+q
    ///(q+1)*p+1,(q+1)*p+2,...,(q+1)*p+q+1

    ///դ����ˮƽ�ߵ�Ȩֵ��һ����(p+1)*q��
    for(int i=0;i<p+1;++i){
        ///ÿ��q������
        for(int j=1;j<=q;++j){
            int w = getUnsigned();
            int idx = (q+1)*i+j;
            mkEdge(idx,idx+1,1,-w);
            mkEdge(idx,idx+1,10000,0);
        }
    }

    ///դ������ֱ�ߵ�Ȩֵ��һ����(q+1)*p��
    for(int i=1;i<=q+1;++i){
        for(int j=0;j<p;++j){
            int w = getUnsigned();
            int idx = (q+1)*j+i;
            int jdx = idx + q + 1;
            mkEdge(idx,jdx,1,-w);
            mkEdge(idx,jdx,10000,0);
        }
    }

    ///����Դ��a�����
    for(int i=0;i<a;++i){
        int k = getUnsigned();
        int y = getUnsigned();
        int x = getUnsigned();
        mkEdge(s,y*(q+1)+x+1,k,M3);
    }

    ///b���յ㵽������
    for(int i=0;i<b;++i){
        int r = getUnsigned();
        int y = getUnsigned();
        int x = getUnsigned();
        mkEdge(y*(q+1)+x+1,t,r,0);
    }

    pii ans = mcmf(s,t,VN,D,Pre,Flag);
    //cout<<M3<<endl;
    //cout<<ans.first<<" "<<ans.second<<endl;
    cout<<M3*ans.first-ans.second<<endl;
    return 0;
}
