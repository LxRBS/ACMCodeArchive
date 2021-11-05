/*
    n条折线分割平面的最大数量
*/
#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;

int Dp[10001] = {0,2};

int dp(int n){
    if ( Dp[n] ) return Dp[n];

    return Dp[n] = dp(n-1) + ( n << 2 ) - 3;
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

