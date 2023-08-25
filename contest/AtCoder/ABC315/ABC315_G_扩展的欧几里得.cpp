/**
 * 给定NABCX，问有多少(i,j,k)满足
 * 1. 1 <= i,j,k <= N
 * 2. Ai + Bj + Ck == X
 * X在3E15, ABC在1E9, N在1E6
 * 首先显然循环k，for每一个k:
 *   令 cha = X - Ck
 *   只需要找有多少(i, j)满足 Ai + Bj == cha 即可
 * 
 * 显然是扩展的欧几里得，首先有
 * Ax + By == gcd(A, B)， 将gcd记作g，且求出x和y
 * 这一步只需要做一次
 * 接下来，多每一个cha，如果cha不是g的倍数，则贡献为0
 * 否则，令beishu = cha / g
 * 于是有 A * beishu * x + B * bieshu * y = cha
 * 对于扩展的欧几里得，A的系数是以B/g为公差的等差数列
 * 因此从 beishu * x 出发，看该等差数列在[1, N]之间的值，记作[low, high]
 * 也就是说 A * [low, high] + B * [left, right] = cha
 * 于是可以求出left与right范围，得到一个以A/g为公差的等差数列
 * 最后再看该等差数列有多少在[1, N]之间，即为当前cha所对应的答案。
 * 对每一个差累加即可。O(N + log(Value))
 * long long仍然不够，需要int128
 * 有O(NlogN...)的做法
 */
#include <bits/stdc++.h>
using namespace std;

#include <bits/extc++.h>
using namespace __gnu_pbds;

using Real = long double;
// using llt = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
using vi = vector<int>;
using vvi = vector<vi>;
using llt = __int128_t;

// using llt = __int128_t;

#ifndef ONLINE_JUDGE
int const SZ = 34;
#else
int const SZ = 200000 + 12;
#endif

llt exEuclid(llt a,llt b,llt&x,llt&y){
    llt x0 = 1, y0 = 0;
    llt x1 = 0, y1 = 1;
    x = 0; y = 1;
    llt r = a % b;
    llt q = ( a - r ) / b;
    while( r ){
        x = x0 - q * x1;
        y = y0 - q * y1;
        x0 = x1; y0 = y1;
        x1 = x; y1 = y;
        a = b; b = r; r = a % b;
        q = ( a - r ) / b;
    }
    return b;
}

/// ax + b >= c, a must be positive
llt fGe(llt a, llt b, llt c){
    assert(a);
    auto cha = c - b;
    if(cha % a == 0) return cha / a;
    if(cha <= 0) return cha / a;
    return cha / a + 1; 
}

/// ax + b <= c, a must be positive
llt fLe(llt a, llt b, llt c){
    auto cha = c - b;
    if(cha % a == 0) return cha / a;
    if(cha < 0) return cha / a - 1;
    return cha / a;
}

/// left <= ax + b <= right
pair<llt, llt> f(llt a, llt b, llt left, llt right){
    if(a < 0){
        return f(-a, -b, -right, -left);
    }
    auto first = fGe(a, b, left);
    auto second = fLe(a, b, right);
    if(first > second) return make_pair<llt, llt>(0, -1);
    return {first, second};
}

long long N, A, B, C, X;

llt proc(){
    llt x, y;
    auto g = exEuclid(A, B, x, y);
    auto dx = B / g, dy = A / g;
    llt ans = 0;
    for(llt c=C,limit=N*C;c<=limit;c+=C){        
        auto cha = X - c;
        // cout << "cha = " << cha << endl;
        if(cha < A + B) break;
        if(cha % g) continue;

        auto beishu = cha / g;
        auto pa = f(dx, x * beishu, 1, N);
        if(pa.first == 0 and -1 == pa.second) continue;

        auto low = beishu * x + dx * pa.first;
        auto high = beishu * x + dx * pa.second;
        if(not (1 <= low and low <= high and high <= N)){
            string s = "";
            // s = std::to_string(A) + " * " + std::to_string(x) + " + " + std::to_string(B) + " * " + std::to_string(y) + " = " + std::to_string(cha);
            throw runtime_error(s.c_str());
        }
        assert((cha - A * low) % B == 0);
        assert((cha - A * high) % B == 0);
        auto left = (cha - A * high) / B;
        auto right = (cha - A * low) / B;
        if(left > N or right < 1) continue;

        auto pp = f(dy, left, max(left, (__int128_t)1), min((__int128_t)N, right));
        ans += pp.second - pp.first + 1;
    }
    return ans;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("z.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N >> A >> B >> C >> X;
    cout << (long long)proc() << endl;
    return 0;
}