/*
    给定根，求有向图的最小树形图
*/

#include <stdio.h>
#include <algorithm>
using namespace std;

//type of edge's weight
typedef int weight_t;

//just as its names
int const SIZE_OF_VERTICES = 2000;
int const SIZE_OF_EDGES = 100000;
weight_t const INF = 1000000000;

struct edge_t{
    int from,to;
    weight_t weight;
}Edge[SIZE_OF_EDGES];
int ECnt;

//Don't forget calling it
//n is the amount of vertices
inline void initGraph(int n){
	ECnt = 1;
}

inline void mkEdge(int a,int b,weight_t w=weight_t()){
	Edge[ECnt].from = a;
	Edge[ECnt].to = b;
	Edge[ECnt++].weight = w;
}

//有向图的最小树形图，返回权值
//s为根
//vn为点的数量，从1开始
//en为边的数量，从1开始
//edge为边表，从1开始，在函数中会被改变
//in是辅助数组，用来记录各节点的最小入边
//pre是辅助数组，用来就各节点最小入边的出点
//flag和idx都是辅助数组
weight_t ZhuLiu(int s,int vn,int en,edge_t edge[],weight_t in[],int pre[],int flag[],int idx[]){
    weight_t ans = 0;

    int u,v;
    while(1){
        //确定最小入边
        fill(in+1,in+vn+1,INF);
        for(int i=1;i<=en;++i)if((u=edge[i].from)!=(v=edge[i].to)&&edge[i].weight<in[v]){
            pre[v] = u;
            in[v] = edge[i].weight;
        }

        //没有树形图
        for(int i=1;i<=vn;++i)if(i!=s&&INF==in[i])return -1;

        in[s] = 0;
        fill(idx+1,idx+vn+1,-1);
        fill(flag+1,flag+vn+1,-1);

        //找环
        int cnt = 1;
        for(int i=1;i<=vn;++i){
            ans += in[v=i];
            while( flag[v] != i && -1 == idx[v] && v != s ){
                flag[v] = i;
                v = pre[v];
            }

            if ( v != s && -1 == idx[v] ){
                for(u=pre[v];u!=v;u=pre[u]){
                    idx[u] = cnt;
                }
                idx[v] = cnt++;
            }
        }

        //没有环
        if ( 1 == cnt ) break;

        for(int i=1;i<=vn;++i)if(-1==idx[i])idx[i]=cnt++;

        //缩点，重标记
        for(int i=1;i<=en;){
            edge[i].from = idx[edge[i].from];
            edge[i].to = idx[v = edge[i].to];
            if ( edge[i].from != edge[i].to ){
                edge[i++].weight -= in[v];
            }else{
                swap(edge[i],edge[en--]);
            }
        }

        vn = cnt - 1;
        s = idx[s];
    }
    return ans;
}

int N,M;
void read(){
    scanf("%d%d",&N,&M);

    initGraph(N);
    int a,b,w;
    for(int i=0;i<M;++i){
        scanf("%d%d%d",&a,&b,&w);
        mkEdge(a+1,b+1,w);
    }
}

int In[SIZE_OF_VERTICES];
int Pre[SIZE_OF_VERTICES];
int Flag[SIZE_OF_VERTICES];
int Idx[SIZE_OF_VERTICES];

int main(){
    //freopen("1.txt","r",stdin);
    int nofkase;
    scanf("%d",&nofkase);
    for(int kase=1;kase<=nofkase;++kase){
        read();

        int ans = ZhuLiu(1,N,M,Edge,In,Pre,Flag,Idx);

        printf("Case #%d: ",kase);
        if ( -1 != ans ) printf("%d\n",ans);
        else puts("Possums!");
    }
    return 0;
}
