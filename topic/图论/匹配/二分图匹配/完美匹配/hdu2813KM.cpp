/*
    最小权匹配
    
    用cin超时，用scanf过。
*/
#include <stdio.h>
#include <iostream>
#include <string>
#include <map>
#include <algorithm>
#include <algorithm>
using namespace std;

typedef int weight_t;

int const SIZE = 510;
weight_t const INF = 1000000000;
weight_t const MAG = 10000;

weight_t Graph[SIZE][SIZE];//二分图的邻接矩阵，A/B点数要求一样多
//LinkAi表示与Ai相连的点，LinkBi表示与Bi相连的点
int LinkA[SIZE],  LinkB[SIZE];
//辅助标记数组
bool FlagA[SIZE], FlagB[SIZE];
int Pre[SIZE];

inline void initGraph(int n){
    for(int i=1;i<=n;++i)fill(Graph[i],Graph[i]+n+1,0);
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

int N,M,K;
map<string,int> S2IA,S2IB;
bool read(){
    if ( 3 != scanf("%d%d%d",&N,&M,&K) ) return false;

    initGraph(M);
    S2IA.clear();
    S2IB.clear();

    char a[100],b[100];
    int aa,bb,w;
    for(int i=0;i<K;++i){
        scanf("%s%s%d",a,b,&w);
        map<string,int>::iterator it = S2IA.find(a);
        if ( S2IA.end() == it ){
            S2IA.insert(make_pair(a,aa=S2IA.size()+1));
        }else{
            aa = it->second;
        }

        it = S2IB.find(b);
        if ( S2IB.end() == it ){
            S2IB.insert(make_pair(b,bb=S2IB.size()+1));
        }else{
            bb = it->second;
        }

        Graph[aa][bb] = max(Graph[aa][bb],MAG-w);
    }
    return true;
}

int main(){
    //freopen("1.txt","r",stdin);
    while( read() ){
        printf("%d\n",MAG*N-KM(M));
    }
    return 0;
}