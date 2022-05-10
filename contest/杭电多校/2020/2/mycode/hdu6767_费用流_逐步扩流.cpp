/**
    N���ˣ�ÿ��������������a/b/c��N��50
    M����������1��M��M��Ȼ��N��M��1��
    ��j�������������i���˵Ĵ���Ϊa*j^2+bj+c
    ��ǡ��Ҫ�����K����������С�����Ƕ��٣�K��1��N
    ���͵Ķ���ͼ���ƥ��
    �����N���ˣ��ұ���M��������
    ��������һ���ߣ�Ȩֵ������Ŀ�������
    Ȼ����һ����Сƥ�伴��
    ����M�ر�޴󣬲������������
    ��ÿ����ֻ��ȡ����ǰNС��Ȩֵ����
    ���ö��κ���������ȷ����һ��
    ����K��1��N��ÿ����һ��������
*/
#include<bits/stdc++.h>
using namespace std;
typedef long long llt;

typedef llt weight_t;

int const SIZE_OF_VERTICES = 100010;//���������ֵ
int const SIZE_OF_EDGES = 100010<<2;//���������ֵ
weight_t const INF = 0x7fffffffffffffff;

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


int N,M;
llt A[52],B[52],C[52];
llt MM[59][59];

llt D[2700];
int Pre[2700];
bool Flag[2700];

map<int,vector<int> > Map;//���굽���˵�ӳ��

//����a/b/c����x����[1,M]��Χ���ҵ���С��N��ֵax^2+bx+c
void f(int index){
    llt const&a = A[index];//a��Ȼ������
    llt const&b = B[index];
    llt const&c = C[index];

    //�Գ����Ȼ��1��ߣ����������[1...N]
    if(b>=0||(b<0&&-b<=(a+a))){
        for(int i=1;i<=N;++i){
            Map[i].push_back(index);
        }
        return;
    }
    if(-b>2*a*M){//����Գ������ұߵ����
        //���������[M...M-N+1]
        for(int i=M;i>=M-N+1;--i){
            Map[i].push_back(index);
        }
        return;
    }
    llt start_x, end_x;
    //���������λ��[1...M]֮��
    if(0==-b%(a+a)){//������ǡ��������
        llt x = -b/(a+a);
        if(N&1){//Nǡ��������
            start_x = x - N/2;
            end_x = x + N/2;
        }else{//N��ż�������Զ�ȡһ��
            start_x = x - N/2;
            end_x = x + N/2;
        }
    }else{//��������С��
        llt x = -b/(a+a);
        start_x = x - N/2;
        end_x = x + N/2 + 1;
    }
    if(start_x<1){
        end_x += 1 - start_x;
        start_x = 1;
        if(end_x>M) end_x = M;
    }
    if(end_x>M){
        start_x -= end_x - M;
        end_x = M;
        if(start_x<1) start_x = 1;
    }
    for(int x=start_x;x<=end_x;++x)Map[x].push_back(index);
}

llt f(int index,llt x){
    llt const&a = A[index];//a��Ȼ������
    llt const&b = B[index];
    llt const&c = C[index];
    return a*x*x+b*x+c;
}

int main() {
    //freopen("1.txt","r",stdin);
    //freopen("2.txt","w",stdout);
    int nofkase;
    scanf("%d",&nofkase);
    while(nofkase--){
        Map.clear();

        scanf("%d%d",&N,&M);
        for(int i=1;i<=N;++i){
            scanf("%lld%lld%lld",A+i,B+i,C+i);
            f(i);
        }

        //��ͼ
        int n1 = Map.size();
        int s = N + n1 + 1;
        int t = s + 1;
        initGraph(t);

        //��㵽ÿ��worker��һ����
        for(int i=1;i<=N;++i){
            mkEdge(s,i,1,0);
        }

        int k = N;
        for(map<int, vector<int> >::const_iterator it=Map.begin();it!=Map.end();++it){
            vector<int> const&v = it->second;
            ++k;//k��ʾ�豸��ͼ�еı��
            for(vector<int>::const_iterator jt=v.begin();jt!=v.end();++jt){
                //*jt��ʾ����
                mkEdge(*jt,k,1,f(*jt,it->first));
            }
            //ÿ���豸���յ���һ����
            mkEdge(k,t,1,0);
        }

        llt maxFlow = 0;
        llt miniCost = 0;
        for(int i=1;i<=N;++i){
            spfa(s,t,D,Pre,Flag);
            //˵���Ҳ�������·
            //if ( INF == d[t] ) break;

            //��������Ȼ��1
            //�䶯����
            for(int p=Pre[t];p;p=Pre[Edge[p].from]){
                Edge[p].cap -= 1;
                Edge[p^1].cap += 1;
            }

            //���������ͷ���
            miniCost += D[t];
            maxFlow += 1;

            printf("%lld",miniCost);
            if(i!=N)putchar(' ');
        }
        printf("\n");
    }
    return 0;
}
