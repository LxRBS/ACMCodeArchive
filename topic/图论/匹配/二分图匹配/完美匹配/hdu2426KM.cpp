/*
    N个人，M间房，人与房为一对一关系
    每个人对某些房有喜好度
    进行分配，要求每个人都有房住且总喜好度最大
    如果喜欢度为负数或者没有喜好度，则不能分配该房间

    2 2 4
    0 0 1
    0 1 4
    1 0 -1
    1 1 1

    这组数据是2，而不是-1

    所有不能建边的边建一个负无穷
    做一个最大权匹配
    检查1~N的每个点，如果匹配边为负无穷，则说明该点实际上没有匹配
    否则，减去多余的负边，就是答案
*/
#include <stdio.h>
#include <algorithm>
using namespace std;

typedef int weight_t;

int const SIZE = 510;
weight_t const INF = 1000000000;
weight_t const NEG = -20000;

weight_t Graph[SIZE][SIZE];//二分图的邻接矩阵，A/B点数要求一样多
//LinkAi表示与Ai相连的点，LinkBi表示与Bi相连的点
int LinkA[SIZE],  LinkB[SIZE];
//辅助标记数组
bool FlagA[SIZE], FlagB[SIZE];
int Pre[SIZE];

inline void initGraph(int n){
    for(int i=1;i<=n;++i)fill(Graph[i],Graph[i]+n+1,NEG);
}

weight_t LabelA[SIZE], LabelB[SIZE];
weight_t Slack[SIZE];

int Q[SIZE<<1];//辅助队列
inline void bfs(int u,int n) {
    weight_t tmp;
    int v, head=0, tail = 0;
    FlagA[Q[tail++] = u] = true;

DEAD_LOOP:
    while(head < tail) {

        for(u = Q[head++],v=1;v<=n;++v)if(!FlagB[v]){
            if ( (tmp = LabelA[u]+LabelB[v]-Graph[u][v]) > Slack[v] ) continue;

            Pre[v] = u;
            if(!tmp) {
                FlagB[v] = true;
                if(!LinkB[v]) {
                    while(v) LinkB[v] = Pre[v], swap(LinkA[Pre[v]], v);
                    return;
                }
                FlagA[ Q[tail++]=LinkB[v] ] = true;
            }else{
                Slack[v] = tmp;
            }
        }
    }

    tmp = INF;
    for(int i=1;i<=n;++i) if(!FlagB[i]&&Slack[i]<tmp) tmp = Slack[i];
    for(int i=1;i<=n;++i) {
        if(FlagA[i]) LabelA[i] -= tmp;
        if(FlagB[i]) LabelB[i] += tmp;
        else Slack[i] -= tmp;
    }

    for(v = 1; v <= n; ++v) {
        if(!FlagB[v] && !Slack[v]) {
            FlagB[v] = true;
            if(!LinkB[v]) {
                while(v) LinkB[v] = Pre[v], swap(LinkA[Pre[v]], v);
                return;
            }
            FlagA[ Q[tail++] = LinkB[v] ] = true;
        }
    }
    goto DEAD_LOOP;
}

weight_t KM(int n){
    fill(LinkA,LinkA+n+1,0);
    fill(LinkB,LinkB+n+1,0);
    fill(LabelB,LabelB+n+1,0);
    fill(Pre,Pre+n+1,0);
    for(int i=1;i<=n;++i) LabelA[i] = *max_element(Graph[i]+1,Graph[i]+n+1);

    for(int i=1;i<=n;++i){
        fill(Slack,Slack+n+1,INF);
        fill(FlagA,FlagA+n+1,false);
        fill(FlagB,FlagB+n+1,false);
        bfs(i,n);
    }

    weight_t ret = 0;
    for(int i=1;i<=n;++i) ret += LabelA[i] + LabelB[i];
    return ret;
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

int N,M,E;
bool read(){
    if ( 1 != scanf("%d",&N) ) return false;
    M = getInt();
    E = getInt();

    initGraph(M);

    int a,b,w;
    for(int i=0;i<E;++i){
        a = getInt() + 1;
        b = getInt() + 1;
        w = getInt();
        if ( w >= 0 ) Graph[a][b] = w;
    }

    return true;
}

int main(){
    //freopen("1.txt","r",stdin);
    for(int kase=1;read();++kase){
        printf("Case %d: ",kase);

        if ( M < N ){
            puts("-1");
            continue;
        }

        weight_t ans = KM(M);

        //检查是否每个人都有分配的房间
        bool flag = true;
        for(int i=1;i<=N;++i)if(NEG==Graph[i][LinkA[i]]){
            flag = false;
            break;
        }

        if ( flag ) printf("%d\n",ans - ( M - N ) * NEG);
        else puts("-1");
    }
    return 0;
}