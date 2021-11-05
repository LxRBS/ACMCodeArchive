/*
    给定图，图上有3个特殊点A/B/C
    要求找到一条从A到C再到B的最短路径，且没有点会被重复经过
    最小费用最大流
    每个点拆成i和i'。
    原图中a到b有一条边长度为w，等价于a'到b有一条边容量为1，费用为w。
    每个i到i'有一条边容量为1费用为0。
    建立一个超级源S，S到A有一条边，容量为1费用为0，S到B有一条边，容量为1费用为0。
    最后，把C到C'的边容量设置为2，费用为0。
    跑一遍最小费用最大流，如果最大流为2，则最小费用为答案。
    否则无解。
    建图可以使用字典树或者hash。目测字符串长度不超过1000，且只含大小写字母。
*/

#include <stdio.h>
#include <string.h>
#include <queue>
#include <utility>
#include <algorithm>
using namespace std;

//Just as its name
int const SIZE_OF_TRIE = 20010;//TODO
//The count of all valid letters
int const ALPHA_SIZE = 52;//TODO
//The map from letters to ints
int L2I[256];
//To initialize L2I array, don't forget calling it!!!
void initL2I(){
    for(int i=0;i<26;++i) L2I[i + 'a'] = i;//TODO
    for(int i=0;i<26;++i) L2I[i+'A'] = i + 26;
}

//The transition matrix of DFA
int Trie[SIZE_OF_TRIE][ALPHA_SIZE];
int Flag[SIZE_OF_TRIE];
int SCnt;

int StartState;
int ErrorState;

//to new a state
inline int _newState(){
    fill(Trie[SCnt],Trie[SCnt]+ALPHA_SIZE,0);
    Flag[SCnt] = 0;
    return SCnt++;
}

int insertAndFind(char const word[]){
    int state = StartState;
    for(char const*p=word;*p;++p){
        int sn = L2I[(int)*p];
        if ( 0 == Trie[state][sn] ) Trie[state][sn] = _newState();
        state = Trie[state][sn];
    }
    return state;
}

void initTrie(){
    SCnt = 0;
    ErrorState = _newState();
    StartState = _newState();
}

typedef int weight_t;
int const SIZE_OF_VERTICES = 20010<<1;//点数的最大值
int const SIZE_OF_EDGES = 100010<<2;//边数的最大值
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

//最小费用最大流，s为源，t为汇，vn为总点数
//其余为辅助数组
pair<weight_t,weight_t> mcmf(int s,int t,int vn,weight_t d[],int pre[],bool flag[]){
    weight_t miniCost = 0;
    weight_t maxFlow = 0;
    while(1){
        spfa(s,vn,d,pre,flag);
        //说明找不到增广路
        if ( INF == d[t] ) break;

        //找出该增广路上的可行流
        weight_t curFlow = INF;
        for(int p=pre[t];p;p=pre[Edge[p].from])if(curFlow>Edge[p].cap)curFlow = Edge[p].cap;

        //变动流量
        for(int p=pre[t];p;p=pre[Edge[p].from]){
            Edge[p].cap -= curFlow;
            Edge[p^1].cap += curFlow;
        }

        //更新流量和费用
        miniCost += d[t] * curFlow;
        maxFlow += curFlow;
    }

    return make_pair(maxFlow,miniCost);
}


int getUnsigned(){
	char ch = getchar();
	while( ch < '0' || ch > '9' ) ch = getchar();

	int ret = (int)(ch-'0');
	while( '0' <= ( ch = getchar() ) && ch <= '9' ) ret = ret * 10 + (int)(ch-'0');
	return ret;
}

char const Dalian[]="Dalian";
char const Xian[]="Xian";
char const Shanghai[]="Shanghai";

char City[2][1001];
int M,N;
int A,B,C;
void read(){
    M = getUnsigned();

    initTrie();
    initGraph(40000+1);

    N = 0;
    int a,b,w;
    int state;
    for(int i=0;i<M;++i){
        scanf("%s%s%d",City[0],City[1],&w);

        state = insertAndFind(City[0]);
        if ( !Flag[state] ) Flag[state] = ++N,++N;
        a = Flag[state];

        state = insertAndFind(City[1]);
        if ( !Flag[state] ) Flag[state] = ++N,++N;
        b = Flag[state];

        mkEdge(a+1,b,1,w);
        mkEdge(b+1,a,1,w);

        if ( 0==strcmp(City[0],Dalian) ) A = a;
        else if ( 0==strcmp(City[0],Xian) ) B = a;
        else if ( 0==strcmp(City[0],Shanghai) ) C = a;

        if ( 0==strcmp(City[1],Dalian) ) A = b;
        else if ( 0==strcmp(City[1],Xian) ) B = b;
        else if ( 0==strcmp(City[1],Shanghai) ) C = b;
    }

    for(int i=1;i<=N+N;i+=2) mkEdge(i,i+1,1,0);
    mkEdge(C,C+1,1,0);

    //超级源
    mkEdge(N+N+1,A,1,0);
    mkEdge(N+N+1,B,1,0);
}

int D[SIZE_OF_VERTICES];
int Pre[SIZE_OF_VERTICES];
bool F[SIZE_OF_VERTICES];

int main(){
    //freopen("1.txt","r",stdin);
    initL2I();
    int nofkase = getUnsigned();
    while(nofkase--){
        read();
        pair<int,int> ans = mcmf(N+N+1,C+1,N+N+1,D,Pre,F);
        if ( 2 == ans.first ) printf("%d\n",ans.second);
        else printf("-1\n");
    }
    return 0;
}

