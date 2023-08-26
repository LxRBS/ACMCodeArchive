/**
 * 假定有一个多重集合 {ni, ai}，从中任选两个元素的组合数量记作n
 * 现在给定n，问该多重集合最小的SIGMA{ai}是多少
 * 对于给定的n，求K满足C(K, 2) >= n
 * 即单重集合一共有K个元素，如果此时恰好是n，直接返回
 * 否则集合种类只能是K - 1种，此时互异元素的组合数是C(K-1, 2)
 * 于是还需要相同元素的组合为 n - C(K - 1, 2)
 * 只需要再将这么多个元素即可
 * 显然，每种元素只需要2个即可。
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
int const SZ = 200000 + 12;
#endif

llt N;

llt proc(){
    llt d = 1 + 8 * N;
    Real x = (1 + sqrt((Real)d)) * 0.5;
    llt t = x;
    if(t * (t - 1) < N + N) ++t;
    assert(t * (t - 1) >= N + N);
    if(t * (t - 1) == N + N) return t;
    t -= 1;
    auto left = N - t * (t - 1) / 2;
    return t + left;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("z.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int nofkase; cin >> nofkase;
    while(nofkase--){
        cin >> N;
        cout << proc() << endl;
    }
    return 0;
}
