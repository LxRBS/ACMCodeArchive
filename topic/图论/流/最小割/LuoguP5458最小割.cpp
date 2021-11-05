/**
   密铺六边形的地图，坐标(x,y,z)
   坐标和为3的倍数的点称为能量源，收益额外加10%
   能够构成三角形的点称为a共振
   能量源在中间，两边各有一个点称为b共振
   现在要求拆除一些点，使得不存在共振，且留存的收益最大
   注意到共振必包含能量点，以能量点为中心，将周围6格分为2组
   两组不能同时取到
   按模3分为0/1/2三组，拆点以后，S连接1连接0连接2连接T，
   这样跑出来的最大流是形成共振的值
   用整个和值减去这个值，就是去掉共振以后的最大值
   注意有一样的点存在
*/
#include <bits/stdc++.h>
using namespace std;
typedef int weight_t;

int const SIZE_OF_VERTICES = 100010;//点数的最大值
int const SIZE_OF_EDGES = 100010<<2;//边数的最大值
weight_t const INF = 0x3f3f3f3f;

struct edge_t{
    int to;
    weight_t cap;//容量
    weight_t flow;//流量
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
inline void mkEdge(int a,int b,weight_t w){
    Edge[ECnt].to = b;
    Edge[ECnt].cap = w;
    Edge[ECnt].flow = 0;
    Edge[ECnt].next = Vertex[a];
    Vertex[a] = ECnt++;

    Edge[ECnt].to = a;
    Edge[ECnt].cap = 0;//有向图的反向边为0，无向图的反向边同正向边
    Edge[ECnt].flow = 0;
    Edge[ECnt].next = Vertex[b];
    Vertex[b] = ECnt++;
}

int __D[SIZE_OF_VERTICES];//Di表示i到汇的距离
int __Cnt[SIZE_OF_VERTICES];//Cnti表示距离为i的顶点的个数
int Queue[SIZE_OF_VERTICES];//辅助队列

//反向BFS，搜索各点到汇的距离，t为汇，n为顶点总数
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

int Cur[SIZE_OF_VERTICES];//当前弧
int Stack[SIZE_OF_VERTICES];//辅助栈

//Improved shortest argument path algorithm
//s为源，t为汇，n为顶点个数
weight_t isap(int s,int t,int n){
    bfs(t,n);
    copy(Vertex,Vertex+n+1,Cur);

    weight_t ans = 0;
    int u = s, top = 0;

    while(__D[s] < n){
        if(u == t){//找到一条增广路
            int inser;
            weight_t wtmp,flow = INF;
            for(int i=0;i<top;++i)if( flow > ( wtmp = Edge[Stack[i]].cap - Edge[Stack[i]].flow ) ){
                flow = wtmp, inser = i;
            }
            for(int i=0;i<top;++i){
                Edge[Stack[i]].flow += flow;  //正向边
                Edge[Stack[i]^1].flow -= flow;//反向边
            }
            ans += flow;
            top = inser;
            u = Edge[Stack[top]^1].to;
            continue;
        }

        //查找可行弧
        int v, ava = 0;
        for(int p=Cur[u];p;p=Edge[p].next){
            if(Edge[p].cap - Edge[p].flow && __D[ v = Edge[p].to ] + 1 == __D[u]){
                Cur[u] = ava = p;
                break;
            }
        }

        if(ava){//找到可行弧以后，推进
            Stack[top++] = Cur[u];
            u = v;
            continue;
        }

        //找不到可行弧，回溯
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
int getInt(){
	int sgn = 1;
	char ch = getchar();
	while( ch != '-' && ( ch < '0' || ch > '9' ) ) ch = getchar();
	if ( '-' == ch ) {sgn = 0;ch=getchar();}

	int ret = (int)(ch-'0');
	while( '0' <= (ch=getchar()) && ch <= '9' ) ret = ret * 10 + (int)(ch-'0');
	return sgn ? ret : -ret;
}

map<pair<int,int>,int> Map;
map<pair<int,int>,int>::iterator It;
int W[51000];
int main(){
    //freopen("1.txt","r",stdin);
    int x,y,z,n = getInt();
    int cnt = 0;
    for(int i=1;i<=n;++i){
        x = getInt();
        y = getInt();
        z = getInt();
        x -= z, y -= z;
        if(Map.end()!=(It=Map.find(make_pair(x,y)))){
            W[It->second] += getInt();
        }else{
            Map.insert(It,make_pair(make_pair(x,y),++cnt));
            W[cnt] = getInt();
        }
    }
    n = cnt;
    int vn = n + n + 2;
    int s = vn - 1, t = vn;
    initGraph(vn);
    //对每一个能源点
    int sum = 0;
    for(map<pair<int,int>,int>::const_iterator it=Map.begin();it!=Map.end();++it){
        x = it->first.first;
        y = it->first.second;
        int index = it->second;
        int mod = ((x+y)%3+3)%3;
        if(0==mod){
            sum += W[index]*11;
            mkEdge(index,index+n,W[index]*11);
            if((It=Map.find(make_pair(x+1,y)))!=Map.end()){
                mkEdge(It->second+n,index,INF);
            }
            if((It=Map.find(make_pair(x,y+1)))!=Map.end()){
                mkEdge(It->second+n,index,INF);
            }
            if((It=Map.find(make_pair(x-1,y-1)))!=Map.end()){
                mkEdge(It->second+n,index,INF);
            }
            if((It=Map.find(make_pair(x-1,y)))!=Map.end()){
                mkEdge(index+n,It->second,INF);
            }
            if((It=Map.find(make_pair(x,y-1)))!=Map.end()){
                mkEdge(index+n,It->second,INF);
            }
            if((It=Map.find(make_pair(x+1,y+1)))!=Map.end()){
                mkEdge(index+n,It->second,INF);
            }
        }else if(1==mod){
            sum += W[index]*10;
            mkEdge(index,index+n,W[index]*10);
            mkEdge(s,index,INF);
        }else if(2==mod){
            sum += W[index]*10;
            mkEdge(index,index+n,W[index]*10);
            mkEdge(index+n,t,INF);
        }else{
            throw runtime_error("XXX");
        }
    }
    printf("%.1f\n",(sum-isap(s,t,vn))/10.0);
    return 0;
}
