/*
    N面骰子，每一面等概率，每面有ai个金币
    N面当中有M面是特殊的，掷出M面其中之一就可以再掷一遍，
    再掷出M面之一又可以再掷一遍……
    问一次游戏得到的金币期望
    设期望为E
    E = SIGMA( P(掷出非M面) * 相应面的金币 ) + SIGMA( P(M面) * ( 相应面的金币 + E ) )
    所以 E = 总数/N + E * M/N
    所以 E = 总数 / ( N - M )
*/
#include <stdio.h>
#include <numeric>
#include <algorithm>
using namespace std;

int N,M,S;
int main(){
    int a;
    while( EOF != scanf("%d",&N) ){
        S = 0;
        for(int i=0;i<N;++i){
            scanf("%d",&a);
            S += a;
        }

        scanf("%d",&M);
        for(int i=0;i<M;++i) scanf("%d",&a);

        if ( 0 == S ) printf("0.00\n");
        else if( N == M ) printf("inf\n");
        else printf("%.2f\n",(double)S/(N-M));
    }
    return 0;
}
