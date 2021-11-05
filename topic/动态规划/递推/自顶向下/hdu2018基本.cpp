//ÀàFibonacciÊıÁĞ
#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;

int N;
int Dp[60] = {0,1,2,3};

int dp(int n){
    if ( Dp[n] ) return Dp[n];

    return Dp[n] = dp(n-1) + dp(n-3);
}
int main(){
    //freopen("1.txt","r",stdin);
    while( ( cin >> N ) && N ) cout<<dp(N)<<endl;
    return 0;
}

