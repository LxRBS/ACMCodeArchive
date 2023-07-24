/**
 * 本质上就是解一元二次方程，数比较大要用int128
 * CF上需要用语言 GNU C++17 (64)
 * 不用64会编译错误
 */
#include <bits/stdc++.h>
using namespace std;

#include <bits/extc++.h>
using namespace __gnu_pbds;

using llt = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
using vi = vector<int>;
using vvi = vector<vi>;

int N;
unsigned long long C;
vi A;

llt proc(){
    llt s1 = 0, s2 = 0;
    for(const auto i : A){
        s1 += i;
        s2 += (llt)i * i;
    }
    __int128_t a = N, b = s1 + s1, c = (__int128_t)s2 - (__int128_t)C;
    __int128_t delta = b * b - 4 * a * c;
    delta = (__int128_t)(sqrt((long double)delta) + 1E-4);
    return (delta - b) / (a + a) / 2;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("z.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int nofkase; cin >> nofkase;
    while(nofkase--){
        cin >> N >> C;
        A.assign(N, 0);
        for(auto & i : A) cin >> i;
        cout << proc() << endl;
    }
    return 0;
}

