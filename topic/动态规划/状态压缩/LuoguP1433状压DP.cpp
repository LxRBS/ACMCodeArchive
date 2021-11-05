/*
    平面上有n个点，从原点出发，最少要多少距离可以每个点都访问到
    n<=15，可以使用状压DP
*/

#include <bits/stdc++.h>
using namespace std;

struct Point{
    double x,y;
}P[20];
double dist(const Point&a,const Point&b){
    double x=a.x-b.x,y=a.y-b.y;
    return sqrt(x*x+y*y);
}
const Point Origin = {0.0,0.0};

int N;
//Dij表示以i为起点、走遍状态j的点集的最小距离
//j中显然要包含i点，除此之外假设还包含了其他若干个点记作p
//Dij = min(Wip+D[p][j^(1<<i)])
double D[16][70000]={0};
double W[20][20];

double dfs(int pos,int state){
    if(D[pos][state]>=0) return D[pos][state];

    double ans = 1E100;
    int ns = state ^ (1<<pos);
    for(int i=0;i<N;++i)if(ns&(1<<i)){
        double tmp = dfs(i,ns) + W[pos][i];
        if(tmp<ans) ans = tmp;
    }
    return D[pos][state] = ans;
}
int main(){
    //freopen("1.txt","r",stdin);
    scanf("%d",&N);
    for(int i=0;i<N;++i){
        scanf("%lf%lf",&P[i].x,&P[i].y);
        for(int j=0;j<i;++j) W[i][j] = W[j][i] = dist(P[i],P[j]);

        fill(D[i],D[i]+(1<<N),-1.0);
        D[i][1<<i] = 0.0;
    }

    double ans = 1E100;
    for(int i=0;i<N;++i){
        double tmp = dfs(i,(1<<N)-1) + dist(P[i],Origin);
        if(tmp<ans) ans = tmp;
    }
    printf("%.2f\n",ans);
    return 0;
}
