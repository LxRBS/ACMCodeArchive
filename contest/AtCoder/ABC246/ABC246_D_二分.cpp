/**
 * 给定N，找出a、b，满足a^3+a^2b+ab^2+b^3大于等于N且最小。
 * 无需求出a和b，只需求出这个最小值即可
 * N在1e18
 * 显然a和b不能超过1e6.
 * 令所求为f(a,b)，在a固定的情况下，f与b是单调的，因此可以二分
 * 一开始使用unsigned导致超时，因为计算减法的时候有时会溢出
*/
#include <bits/stdc++.h>
using namespace std;

typedef long long ull;

inline ull f(ull a, ull b){
    return (a*a+b*b)*(a+b);
}

ull N;



ull proc(ull a){
    ull limit = N - a*a*a;
    limit = (ull)pow(limit, 1.0/3.0) + 1ULL;
    ull left = 0, right = limit, mid;
    do{
        mid = (left + right) >> 1;
        if(f(a, mid) >= N) right = mid - 1;
        else left = mid + 1;
    }while(left<=right);
    return left;
}

ull proc(){
    if(0 == N) return 0;
    ull ans = 1E18;
    ull limit = (ull)pow(N, 1.0/3.0) + 1ULL;
    for(ull a=0;a<=limit;++a){
        if(N < a*a*a) break;
        ull b = proc(a);
        ans = min(ans, f(a, b));
    }
    return ans;
}

int main() {    
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif    
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cin>>N;
    cout<<proc()<<endl;
    return 0;
}

