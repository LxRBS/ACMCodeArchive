/**
    N个人，每个人有三个参数a/b/c，N在50
    M个东西，从1到M，M必然比N大，M在1亿
    第j个东西分配给第i个人的代价为a*j^2+bj+c
    问恰好要分配出K个东西的最小代价是多少？K从1到N
    典型的二分图最佳匹配
    左边是N个人，右边是M个东西，
    从左到右有一条边，权值根据题目定义计算
    然后求一个最小匹配即可
    但是M特别巨大，不可能算出所有
    对每个人只需取出其前N小的权值即可
    利用二次函数很容易确定这一点
    至于K从1到N，每次扩一个流即可
*/
#include<bits/stdc++.h>
using namespace std;
typedef long long llt;

typedef llt weight_t;

int const SIZE_OF_VERTICES = 100010;//点数的最大值
int const SIZE_OF_EDGES = 100010<<2;//边数的最大值
weight_t const INF = 0x7fffffffffffffff;

struct edge_t{
    int from,to;
    weight_t cap;//容量
    weight_t cost;//费用
    int next;
}Edge[SIZE_OF_EDGES];
int ECnt;

int Vertex[SIZE_OF_VERTICES];

//初始化
inline void initGraph(int n){
    ECnt = 2;//ECnt从2开始，空指针用0表示，反向边用^1计算
    fill(Vertex,Vertex+n+1,0);
}

//生成边
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

//s表示源，vn为顶点数量，其余为辅助数组
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

map<int,vector<int> > Map;//坐标到工人的映射

//给定a/b/c，在x属于[1,M]范围内找到最小的N个值ax^2+bx+c
void f(int index){
    llt const&a = A[index];//a必然是正数
    llt const&b = B[index];
    llt const&c = C[index];

    //对称轴必然在1左边，则坐标就是[1...N]
    if(b>=0||(b<0&&-b<=(a+a))){
        for(int i=1;i<=N;++i){
            Map[i].push_back(index);
        }
        return;
    }
    if(-b>2*a*M){//如果对称轴在右边的外边
        //则坐标就是[M...M-N+1]
        for(int i=M;i>=M-N+1;--i){
            Map[i].push_back(index);
        }
        return;
    }
    llt start_x, end_x;
    //如果坐标轴位于[1...M]之间
    if(0==-b%(a+a)){//坐标轴恰好是整数
        llt x = -b/(a+a);
        if(N&1){//N恰好是奇数
            start_x = x - N/2;
            end_x = x + N/2;
        }else{//N是偶数，可以多取一个
            start_x = x - N/2;
            end_x = x + N/2;
        }
    }else{//坐标轴是小数
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
    llt const&a = A[index];//a必然是正数
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

        //建图
        int n1 = Map.size();
        int s = N + n1 + 1;
        int t = s + 1;
        initGraph(t);

        //起点到每个worker有一条边
        for(int i=1;i<=N;++i){
            mkEdge(s,i,1,0);
        }

        int k = N;
        for(map<int, vector<int> >::const_iterator it=Map.begin();it!=Map.end();++it){
            vector<int> const&v = it->second;
            ++k;//k表示设备在图中的编号
            for(vector<int>::const_iterator jt=v.begin();jt!=v.end();++jt){
                //*jt表示工人
                mkEdge(*jt,k,1,f(*jt,it->first));
            }
            //每个设备到终点有一条边
            mkEdge(k,t,1,0);
        }

        llt maxFlow = 0;
        llt miniCost = 0;
        for(int i=1;i<=N;++i){
            spfa(s,t,D,Pre,Flag);
            //说明找不到增广路
            //if ( INF == d[t] ) break;

            //可行流必然是1
            //变动流量
            for(int p=Pre[t];p;p=Pre[Edge[p].from]){
                Edge[p].cap -= 1;
                Edge[p^1].cap += 1;
            }

            //更新流量和费用
            miniCost += D[t];
            maxFlow += 1;

            printf("%lld",miniCost);
            if(i!=N)putchar(' ');
        }
        printf("\n");
    }
    return 0;
}
