/*
    给定1年的总天数，问至少要多少人，才能使得至少两个人同生日的概率不低于0.5
    设总天数为N，M个人，则生日不同的概率为
    N * (N-1) * ... * (N-M+1) / N^M
    即
    (N-1)/N * (N-2)/N * ... (N-M+1)/N < 0.5

    这个程序当N取1、2时，似乎有点问题
*/

#include <stdio.h>
#include <vector>
#include <numeric>
using namespace std;

int f(int n){
    double x = 1.0, dn = (double)n;
    for(int m=0;;++m){
        x *= (double)( n - m ) / dn;
        if ( x <= 0.5 ) return m;
    }
}

int main(){
    int n,nofkase;
    scanf("%d",&nofkase);
    for(int kase=1;kase<=nofkase;++kase){
        scanf("%d",&n);
        printf("Case %d: %d\n",kase,f(n));
    }
    return 0;
}

