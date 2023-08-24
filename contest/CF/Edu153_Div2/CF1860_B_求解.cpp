/**
 * 给定目标M，再给定Ak个K和A1个1，此外还有额外的无限个1和无限个K
 * 问使得总和恰好为M，需要使用的额外数字最少是多少
 * 首先，如果Ak * K > M，则其实不需要那么多Ak，将Ak减到合适的数值。
 * 其次将所有A1个1加上去，如果能够满足，答案为0
 * 否则只需考虑两种情况，样例已经给出。
 * 1. 差的比较多的情况，肯定是尽量的选K，然后不足的用1即可
 * 2. 差的比较少的情况，可以少选几个1，然后用一个额外的K补即可
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

llt M, K, A1, AK;

llt proc(){
    auto tmp = M / K;
    if(AK > tmp) AK = tmp;
    if(M - AK * K <= A1) return 0;

    auto cha = M - AK * K - A1;
    auto ans = cha / K + (cha - cha / K * K);

    auto left = K - cha % K;
    if(left <= A1){
        assert((cha + left) % K == 0);
        auto t2 = (cha + left) / K;
        ans = min(ans, t2);
    }
    return ans;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("z.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int nofkase; cin >> nofkase;
    while(nofkase--){
        cin >> M >> K >> A1 >> AK;
        cout << proc() << endl;
    }
    return 0;
}
