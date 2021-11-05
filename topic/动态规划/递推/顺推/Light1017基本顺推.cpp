/*
    平面上若干个点，用w的刷子水平刷
    问刷k次，最多刷到多少个点
*/
#include <cstdio>
#include <algorithm>
using namespace std;
struct point_t{
    int x,y;
}P[110];
bool operator < (point_t const&lhs,point_t const&rhs){
    return lhs.y < rhs.y || ( lhs.y == rhs.y && lhs.x < rhs.x );
}

int D[110][110];//Dij表示刷i次刷到第j个点能获得的最多个数
int N,W,K;
void read(){
    scanf("%d%d%d",&N,&W,&K);
    for(int i=0;i<N;++i)scanf("%d%d",&P[i].x,&P[i].y);
    sort(P,P+N);
}
void dp(){
    for(int j=0;j<N;++j) D[0][j] = 0;
    for(int i=1;i<=K;++i){
        for(int j=0;j<N;++j){
            int t = j;
            int& c = ( D[i][j] = 0 );
            while( t >= 0 && P[j].y - P[t].y <= W ) ++c, --t;

            if ( t >= 0 ) c += *max_element(D[i-1],D[i-1]+t+1);
        }
    }
}
int main()
{
    //freopen("1.txt","r",stdin);
    int nofkase;
    scanf("%d",&nofkase);
    for(int kase=1;kase<=nofkase;++kase){
        read();
        dp();
        printf("Case %d: %d\n",kase,*max_element(D[K],D[K]+N));
    }
    return 0;
}
