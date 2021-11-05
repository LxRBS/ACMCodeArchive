/*
    N个砖头摆台阶，台阶必须越来越高，问一共有多少种方法
    如果以Di表示i个砖头的方法，则它跟D(i-1)不一定有联系，so?
*/
#include <cmath>
#include <iostream>
#include <algorithm>
using namespace std;

typedef unsigned long long ull;

int N;

ull Dp[501][501] = {{0ULL},{0ULL,1ULL},{0ULL,0ULL,1ULL}};
ull dp(int n,int last){
    if ( Dp[n][last] ) return Dp[n][last];
    if ( n < last ) return Dp[n][last] = 0;

    double nn = (double)(n-last);
    int least = ( -1.0 + sqrt(1.0+8.0*nn) ) / 2.0;
    ull ret = 0ULL;
    for(int i=least;i<last;++i){
        ret += dp(n-last,i);
    }
    return Dp[n][last] = ret;
}

int main(){
    //freopen("1.txt","r",stdin);
    for(int i=3;i<=500;++i){
        fill(Dp[i],Dp[i]+501,0ULL);
        Dp[i][i] = 1ULL;
    }

    while( cin >> N ){
        ull ret = 0ULL;
        int least = ( -1.0 + sqrt(1.0+8.0*N) ) / 2.0;
        for(int i=least;i<=N;++i) ret += dp(N,i);
        cout<<ret-1ULL<<endl;
    }

    return 0;
}


