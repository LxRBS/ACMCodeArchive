/*
    在蜂巢地图上，蜜蜂只能向右走，问可能的路线数量
*/
#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;

typedef unsigned long long ull;

ull Dp[60][60] = {0ULL};

ull dp(int a,int b){
    if ( Dp[a][b] ) return Dp[a][b];
    if ( a + 1 == b || a + 2 == b ) return Dp[a][b] = ull(b - a);
    return Dp[a][b] = dp(a,b-1) + dp(a,b-2);
}
int main(){
    //freopen("1.txt","r",stdin);
    int kase;
    cin >> kase;
    while( kase-- ){
        int a,b;
        cin >> a >> b;
        cout << dp(a,b) << endl;
    }
    return 0;
}

