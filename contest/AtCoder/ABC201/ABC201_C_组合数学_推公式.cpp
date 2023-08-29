/**
 * 密码一共有4位，有0-9的数字组成
 * 其中有o种数字必须用到，w种数字可能用到，x种数字一定用不到
 * 问可能的密码一共有多少个？
 * 令 f(o) 为只考虑o的数量
 * 当 o >= 5:  f(o) = 0
 *  o == 4: f(o) = 4!
 *  o == 3: f(o) = C(3, 1) * 4! / 2!
 *  o == 2: f(o) = C(2, 1) * 4 + 4! / (2! * 2!)
 *  o == 1: f(o) = 1
 * 再考虑有w的情况，记作g(w):
 *  0o4w: g(4) = SIGMA{C(w, i) * f(i)}
 *  1o3w: g(3) = C(w, 3) * f(4) + C(w, 2) * f(3) + C(w, 1) * f(2)
 *  2o2w: g(2) = C(w, 2) * f(4) + C(w, 1) * f(3)
 *  3o1w: g(1) = C(w, 1) * f(4)
 * 累加即可。
 * 标程用的暴力枚举法。4位密码一共只有1E4种可能性
 * 对每一种可能性看是否符合条件
 */
#include <bits/stdc++.h>
using namespace std;

#include <bits/extc++.h>
using namespace __gnu_pbds;

using Real = long double;
using llt = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
using vi = vector<int>;
using vvi = vector<vi>;

#ifndef ONLINE_JUDGE
int const SZ = 34;
#else
int const SZ = 2E5+10;
#endif

llt f(int n){
    llt ans = 1;
    for(int i=1;i<=n;++i) ans *= i;
    return ans;
}

llt C(int n, int m){
    if(not (0 <= m and m <= n)) return 0;
    if(0 == m or n == m) return 1;
    return f(n) / (f(m) * f(n - m));
}

string S;

llt calcO(int o){
    if(0 == o) return 0;
    if(o > 4) return 0;
    if(4 == o) return f(4);
    if(3 == o) return f(4) / f(2) * 3;
    if(2 == o) return f(4) / f(3) * 2 + f(4) / (f(2) * f(2));
    return 1;
}

llt calc3X(int x){
    return C(x, 1) * calcO(4);
}

llt calc2X(int x){
    return C(x, 1) * calcO(3) + C(x, 2) * calcO(4);
}

llt calc1X(int x){
    return C(x, 1) * calcO(2) + C(x, 2) * calcO(3) + C(x, 3) * calcO(4);
}

llt calc0X(int x){
    llt ans = 0;
    for(int i=1;i<=4;++i){
        ans += C(x, i) * calcO(i);
    }
    return ans;
}

llt calcOX(int o, int x){
    if(o >= 4) return 0;
    if(3 == o) return calc3X(x);
    if(2 == o) return calc2X(x);
    if(1 == o) return calc1X(x);
    return calc0X(x);
}

llt proc(){
    vi o, w, x;
    for(int i=0;i<10;++i){
        if('o' == S[i]) o.push_back(i);
        else if('?' == S[i]) w.push_back(i);
        else if('x' == S[i]) x.push_back(i);
        else assert(0);
    }
    llt ans = calcO(o.size());
    ans += calcOX(o.size(), w.size());
    return ans;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("z.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> S;
    cout << proc() << endl;
    return 0;
}