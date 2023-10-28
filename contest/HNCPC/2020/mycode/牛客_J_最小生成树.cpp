/**
    给定一个无向图，其第i条边的边权为ai+bi*x，其中x为未知数
    求当x取遍[L, R]时，可以得到该图的n个MST
    求这n个MST中的最小值
    考虑任意x下的一种支撑树，其边集合记作E，权值记作W(x)=aE+bE*x
    现在考虑当x+1时，仍然取E，则权值记作W(x+1)=aE+bE*x+bE，
    现在有两种可能，
    一种是W(x)>=W(x+1)，此情况下，易得W(x+1)>=W(x+2)>=...
    说明x肯定取不到最小值，只能是在R取到。
    另一种是W(x)<W(x+1)，此情况下，必然有W(x)>W(x-1)>...
    则在L取到。
    所以只需计算端点即可。
*/
#include <bits/stdc++.h>
using namespace std;

typedef long long llt;

int const SIZE = 200010;

int Father[SIZE];

void init(int n){for(int i=1;i<=n;++i)Father[i]=i;}
int find(int x){return x==Father[x]?x:Father[x]=find(Father[x]);}
void unite(int x,int y){Father[find(y)]=find(x);}

int N, M, L, R;
struct _t{
    int from, to;
    llt w;
}A[SIZE],B[SIZE];

bool operator < (const _t&a, const _t&b){
    return a.w < b.w;
}

llt proc(){
    init(N);
    sort(A,A+M);
    llt a = 0LL;
    int cnt = 1;
    for(int i=0;i<M;++i){
        if(find(A[i].from)==find(A[i].to)) continue;

        unite(A[i].from, A[i].to);
        a += A[i].w;
        if(++cnt==N) break;
    }

    init(N);
    sort(B,B+M);
    llt b = 0LL;
    cnt = 1;
    for(int i=0;i<M;++i){
        if(find(B[i].from)==find(B[i].to)) continue;

        unite(B[i].from, B[i].to);
        b += B[i].w;
        if(++cnt==N) break;
    }

    return min(a, b);
}

int main(){
    //freopen("1.txt","r",stdin);
    while(4==scanf("%d%d%d%d",&N,&M,&L,&R)){
        for(int u,v,a,b,i=0;i<M;++i){
            scanf("%d%d%d%d",&u,&v,&a,&b);
            A[i].from = B[i].from = u;
            A[i].to = B[i].to = v;
            A[i].w = a + (llt)b * L;
            B[i].w = a + (llt)b * R;
        }
        printf("%lld\n", proc());
    }
    return 0;
}
