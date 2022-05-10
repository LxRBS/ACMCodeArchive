/**
   50个点100条边的网络，给定费用
   再给定一个容量u/v，令所有边的容量都是u/v，
   问使得从1到N流为1的最小费用是多少
   假设每条边容量均为1，网络流量为x时的费用为C(x)
   则流量从x-1涨到x时，费用从C(x-1)到C(x)，是一个线性函数
   令这条直线为y=kx+b，则网络流量为v/u的费用是k(v/u)+b
   反过来，容量为u/v，网络流量为1的费用是上述费用的u/v，所以为
   k+bu/v
   封装有理数运算会超时
*/
#include <bits/stdc++.h>
using namespace std;
int getUnsigned(){
	char ch = getchar();
	while( ch < '0' || ch > '9' ) ch = getchar();

	int ret = (int)(ch-'0');
	while( '0' <= ( ch = getchar() ) && ch <= '9' ) ret = ret * 10 + (int)(ch-'0');
	return ret;
}
typedef long long int llt;

//iteration implementation
llt gcd(llt a,llt b){
    while( b ){
        llt r = b;
        b = a % b;
        a = r;
    }
    return a;
}
struct Rational{
    llt fenzi;
    llt fenmu;
    Rational(llt a=0,llt b=1):fenzi(a),fenmu(b){
        llt g = gcd(fenzi,fenmu);
        fenzi /= g;
        fenmu /= g;
    }
    void disp()const{printf("%lld/%lld ",fenzi,fenmu);}
}Slope[110],Inter[110],Flow[110],Cost[110];

bool operator < (const Rational&lhs,const Rational&rhs){
    return lhs.fenzi*rhs.fenmu<lhs.fenmu*rhs.fenzi;
}

const Rational operator + (const Rational&lhs,const Rational&rhs){
    return Rational(lhs.fenzi*rhs.fenmu+lhs.fenmu*rhs.fenzi,lhs.fenmu*rhs.fenmu);
}

const Rational operator * (const Rational&lhs,const Rational&rhs){
    return Rational(lhs.fenzi*rhs.fenzi,lhs.fenmu*rhs.fenmu);
}

void disp(const Rational a[],int s,int e){
    for(int i=s;i<e;++i)(a+i)->disp();
    printf("\n");
}

typedef int weight_t;

int const SIZE_OF_VERTICES = 60;//点数的最大值
int const SIZE_OF_EDGES = 301<<2;//边数的最大值
weight_t const INF = 0x3f3f3f3f;

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

int cnt;

llt SlopeFenzi[110],SlopeFenmu[110];
llt InterFenzi[110],InterFenmu[110];

void answer(){
    int u = getUnsigned();
    int v = getUnsigned();
    if(0==u){
        puts("NaN");
        return;
    }
    Rational f(v,u);
    //找到f属于哪一段
    pair<Rational*,Rational*> pp = equal_range(Flow+1,Flow+cnt,f);
    int p1 = pp.first - Flow;
    int pt = pp.second-Flow;
    if(p1==cnt){  //超出最大范围
        puts("NaN");
        return;
    }
    if(p1==cnt-1&&pt==cnt){ //刚好是最大的那个数
        /*
        Rational cost = Cost[cnt-1] * Rational(u,v);
        cost.disp();
        puts("");//*/
        llt a = Cost[cnt-1].fenzi * u;
        llt b = Cost[cnt-1].fenmu * v;
        llt g = gcd(a,b);
        printf("%lld/%lld\n",a/g,b/g);
        return;
    }
    /*
    Rational cost = Slope[pt] + Inter[pt]* Rational(u, v);
    cost.disp();
    puts("");//*/
    llt a = SlopeFenzi[pt]*InterFenmu[pt]*v+SlopeFenmu[pt]*InterFenzi[pt]*u;
    llt b = SlopeFenmu[pt]*InterFenmu[pt]*v;
    llt g = gcd(a,b);
    printf("%lld/%lld\n",a/g,b/g);
}

weight_t d[SIZE_OF_VERTICES];
int pre[SIZE_OF_VERTICES];
bool flag[SIZE_OF_VERTICES];
int main(){
    int vn, n, m;
    while(scanf("%d%d",&n,&m)!=EOF){
        initGraph(vn=n+2);
        for(int i=0;i<m;++i){
            int a = getUnsigned();
            int b = getUnsigned();
            mkEdge(a,b,1,getUnsigned());
        }

        int s = n + 1, t = n + 2;
        mkEdge(s,1,0,0);
        mkEdge(n,t,0,0);

        int es = ECnt-4;
        int et = ECnt-2;

        weight_t miniCost = 0;
        weight_t maxFlow = 0;

        weight_t lastx = 0, lasty = 0;

        cnt = 1;
        for(int i=1;i<=m;++i){
            //正向边容量加1
            Edge[es].cap += 1;
            Edge[et].cap += 1;

            //找增广路，基本上必然有,而且有的话扩流必然为1
            spfa(s,vn,d,pre,flag);
            //找不到增广路,说明原图已经满流
            if ( INF == d[t] ) break;

            //找出该增广路上的可行流
            //不用找可行流，因为必然为1
            //weight_t curFlow = INF;
            //for(int p=pre[t];p;p=pre[Edge[p].from])if(curFlow>Edge[p].cap)curFlow = Edge[p].cap;

            //变动流量
            for(int p=pre[t];p;p=pre[Edge[p].from]){
                 Edge[p].cap -= 1;
                 Edge[p^1].cap += 1;
            }

            //更新流量和费用
            miniCost += d[t];
            maxFlow += 1;

            weight_t x1 = maxFlow, y1 = miniCost;
            //Slope[cnt] = Rational(y1-lasty,x1-lastx);
            //Inter[cnt] = Rational(Slope[cnt].fenmu*y1-Slope[cnt].fenzi*x1,Slope[cnt].fenmu);
            InterFenzi[cnt] = (InterFenmu[cnt] = SlopeFenmu[cnt] = x1-lastx) * y1 - (SlopeFenzi[cnt] = y1-lasty) * x1;
            Flow[cnt] = Rational(x1,1);
            Cost[cnt++] = Rational(y1,1);

            lastx = x1, lasty = y1;
        }
        /*
        disp(Slope,1,cnt);
        disp(Inter,1,cnt);
        disp(Flow,1,cnt);
        disp(Cost,1,cnt);
        //*/
        //q个询问
        int q = getUnsigned();
        while(q--){
            answer();
        }
    }
    return 0;
}
