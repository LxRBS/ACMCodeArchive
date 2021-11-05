/*
    求最小生成树和次小生成树
*/

#include <stdio.h>
#include <algorithm>
using namespace std;

typedef int weight_t;
int const SIZE = 110;
weight_t const INF = 1000000000;

//求次小生成树的Prim算法，可以同时求出MST
//g为图，1base；vn为图的顶点数
//mst为返回参数，MST的权值；mst2位返回参数，次小生成树的权值
//d为辅助数组，di记录i到中间结果的最短距离，求MST用
//flag为辅助数组，标记用
//pre为辅助数组，prei与i为MST中的一条边
//used为辅助数组，usedij表示ij为MST中的一条边
//maxe为辅助数组，maxeij记录MST上i到j路径上的最长的边，求次小生成树用
int Prim42ndMST(weight_t const g[][SIZE],int vn,weight_t&mst,weight_t&mst2,weight_t d[],bool flag[],int pre[],bool used[][SIZE],weight_t maxe[][SIZE]){
    //初始化
    fill(d,d+vn+1,INF);
    fill(flag,flag+vn+1,false);
    for(int i=1;i<=vn;++i){
        fill(maxe[i],maxe[i]+vn+1,0);
        fill(used[i],used[i]+vn+1,false);
    }
    mst = 0;

    //第一个顶点
    fill(pre,pre+vn+1,1);
    for(int i=2;i<=vn;++i)if(g[1][i])d[i]=g[1][i];
    d[1] = 0;
    flag[1] = true;
    pre[1] = 0;

    //一次加入一个顶点
    for(int i=2;i<=vn;++i){
        int k = -1;

        //对每一个顶点j
        for(int j=1;j<=vn;++j){
            //如果j不在MST中，且j到当前MST的距离是最短的
            if ( !flag[j] && ( -1 == k || d[j] < d[k] ) ){
                k = j;
            }
        }

        //不连通，没有生成树
        //if ( INF == d[k] ) return -1;

        //将k加入MST
        mst += d[k];
        flag[k] = true;
        used[k][pre[k]] = used[pre[k]][k] = true;

        //更新
        for(int j=1;j<=vn;++j)if(j!=k){
            //如果j是中间结果的点，可以更新kj路径之间的最长边
            if ( flag[j] ){
                maxe[j][k] = maxe[k][j] = max(maxe[j][pre[k]],d[k]);
            }

            //如果j不是中间结果，有可能更新dj
            if ( !flag[j] && g[k][j] && g[k][j] < d[j] ){
                d[j] = g[k][j];
                pre[j] = k;
            }
        }
    }

    mst2 = INF;
    //枚举每一条不在MST中的边
    for(int i=1;i<vn;++i)for(int j=i+1;j<=vn;++j)if(g[i][j]&&!used[i][j]){
        mst2 = min(mst2,mst-maxe[i][j]+g[i][j]);
    }

    return 1;
}

weight_t Graph[SIZE][SIZE];//1 base
inline void initGraph(int vn){
    for(int i=1;i<=vn;++i)fill(Graph[i],Graph[i]+vn+1,0);
}
inline void mkEdge(int a,int b,weight_t w){
    Graph[a][b] = Graph[b][a] = w;
}

weight_t D[SIZE];
bool Flag[SIZE];
int Pre[SIZE];
bool Used[SIZE][SIZE];
weight_t Maxe[SIZE][SIZE];

int main(){
    //freopen("1.txt","r",stdin);
    int nofkase,n,m,a,b,c;
    weight_t mst,mst2;
    scanf("%d",&nofkase);
    while(nofkase--){
        scanf("%d%d",&n,&m);

        initGraph(n);
        for(int i=0;i<m;++i){
            scanf("%d%d%d",&a,&b,&c);
            mkEdge(a,b,c);
        }

        Prim42ndMST(Graph,n,mst,mst2,D,Flag,Pre,Used,Maxe);

        printf("%d %d\n",mst,mst2);
    }
    return 0;
}