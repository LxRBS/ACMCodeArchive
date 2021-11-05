/**
    全局最小割，StoerWagner算法，模板题
*/
#include <bits/stdc++.h>
using namespace std;

typedef int weight_t;
int const SIZE_OF_VERTIECES = 650;
weight_t const INF = 2000000000;

weight_t Graph[SIZE_OF_VERTIECES][SIZE_OF_VERTIECES];//图的邻接表，索引从1开始
weight_t _W[SIZE_OF_VERTIECES];//权值数组，辅助数组
bool _Flag[SIZE_OF_VERTIECES];//辅助数组,Flag[i]为真表示点i已经处理过
bool _Behalf[SIZE_OF_VERTIECES];//辅助数组,Behalf[i]为真说明点i不是独立的而是被缩进了别的点中

inline void initGraph(int vn=0){
    memset(Graph,0,sizeof(Graph));
}

//收缩操作，求出本次搜索的最小割值以及S和T,O(N*N)
weight_t contract(int vn,int&s,int&t){
    fill(_W,_W+vn+1,0);
    fill(_Flag,_Flag+vn+1,false);

    weight_t ans;
    for(int j,k,i=1;i<=vn;++i){
        k = 0;
        //找到不在中间结果中且权值最大的点k
        for(j=1;j<=vn;++j)if(!_Behalf[j]&&!_Flag[j]&&(!k||_W[j]>_W[k])) k = j;
        if (!k) break;
        //滚动记录s和t，并且将k加入中间结果
        s = t; _Flag[t=k] = true;
        ans = _W[k];
        for(j=1;j<=vn;++j)if(!_Behalf[j]&&!_Flag[j]) _W[j] += Graph[k][j];
    }
    return ans;
}

//vn为顶点数量，w和flag、behalf是辅助数组
weight_t StoerWagner(int vn){
    weight_t ans = INF;
    fill(_Behalf,_Behalf+vn+1,0);

    for(int s,t,i=1;i<vn;++i){
        ans = min(ans,contract(vn,s,t));
        //说明图本身就不连通
        if ( 0 == ans ) return 0;
        //将t缩到s中
        _Behalf[t] = true;
        for(int j=1;j<=vn;++j)if(!_Behalf[j])Graph[s][j] += Graph[t][j],Graph[j][s] += Graph[j][t];
    }
    return ans;
}

int getUnsigned(){
	char ch = getchar();
	while( ch < '0' || ch > '9' ) ch = getchar();

	int ret = (int)(ch-'0');
	while( '0' <= ( ch = getchar() ) && ch <= '9' ) ret = ret * 10 + (int)(ch-'0');
	return ret;
}

int main(){
    int n = getUnsigned();
    int m = getUnsigned();
    while(m--){
        int a = getUnsigned();
        int b = getUnsigned();
        Graph[a][b] = Graph[b][a] = getUnsigned();
    }
    printf("%d\n",StoerWagner(n));
    return 0;
}
