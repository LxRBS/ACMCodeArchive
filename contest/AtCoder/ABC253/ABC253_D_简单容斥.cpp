/**
 * 求[1, N]中不是A的倍数也不是B的倍数的数之和
 * 求一下A或B的倍数之和，简单的容斥
 */
#include <bits/stdc++.h>
using namespace std;

#ifndef ONLINE_JUDGE
int const SIZE = 13;
#else
int const SIZE = 2e5+5;
#endif  

using llt = long long;

llt gcd(llt a, llt b){
    while(b){
        llt r = a % b;
        a = b;
        b = r;
    }
    return a;
}

llt lcm(llt a, llt b){
    return a / gcd(a, b) * b;
}

llt f(llt n, llt x){
    llt t = n / x;
    return x * t * (t + 1) / 2;
}

llt f(llt n, llt a, llt b){
    llt ans = n * (n + 1LL) / 2LL;
    ans -= f(n, a);
    ans -= f(n, b);
    ans += f(n, lcm(a, b));
    return ans;
}
 
int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif  
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    
    llt n, a, b;
    cin>>n>>a>>b;
    cout<<f(n,a,b)<<endl;
    return 0;
}
