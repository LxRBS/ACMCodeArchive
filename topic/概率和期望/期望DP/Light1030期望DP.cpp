/*
    1×N的地图，每个位置有一定数量的黄金。
	初始在1位置，每次掷1个6面骰子，前进若干步并拿到目标位置的黄金。
	如果当前的步数使得超出了地图，则重掷骰子
	到达N位置后，停止。问最后拿到黄金数量的期望 
	令Di为从i位置到达N位置的期望，则
	Di = SIGMA( P(i到j的概率) * Dj ) 
	Dj实际上最多只有6种可能，即i+1到i+6 
*/
#include <cstdio>
#include <algorithm>
using namespace std;

int N;
int A[101];
double D[101];//Di表示从位置i到达位置N的期望

int main(){
    //freopen("1.txt","r",stdin);
    int nofkase;
    scanf("%d",&nofkase);
    for(int kase=1;kase<=nofkase;++kase){
        scanf("%d",&N);
        for(int i=1;i<=N;++i)scanf("%d",A+i);

        fill(D,D+N+1,0.0);
        D[N] = A[N];
        for(int i=N-1;i>=1;--i){
            D[i] = A[i];
            int cnt = 6;
            if ( N - i < cnt ) cnt = N - i;
            for(int j=1;j<=cnt;++j) D[i] += D[i+j] / cnt;
        }
        printf("Case %d: %f\n",kase,D[1]);
    }
    return 0;
}
