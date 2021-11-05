//FibonacciÊıÁĞ
#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;

int Dp[42] = {0,0,1,2};

int dp(int n){
    if ( Dp[n] || 1 == n ) return Dp[n];

    return Dp[n] = dp(n-1) + dp(n-2);
}
int main(){
    //freopen("1.txt","r",stdin);
    int kase;
    cin >> kase;
    while( kase-- ){
        int n;
        cin >> n;
        cout<<dp(n)<<endl;
    }
    return 0;
}

