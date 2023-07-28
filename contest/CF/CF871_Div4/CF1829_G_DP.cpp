/**
 * 给定数塔，第i格记录i的平方。
 * 假设拆掉第n格，则n之上的格子全都垮掉，给定n，问一共垮了多少
 * 假设第n个在level层，则
 * Dn = n * n + D[n - level] + D[n - level + 1] - D[n - level - level + 2]
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

int N;
vector<llt> D;

llt get(llt n){
    llt t = 1 + 8 * n;
    Real r = sqrt((Real)t);
    llt tmp = r;
    if(tmp * tmp == t){
        return (tmp - 1) / 2;
    }
    return static_cast<llt>((1.L + r) * 0.5L);
}

llt dfs(llt n){
    if(D[n] != -1) return D[n];

    llt level = get(n);
    if(level * (level + 1) == n + n) return D[n] = n * n + dfs(n - level);
    if(level * (level - 1) == n + n - 2) return D[n] = n * n + dfs(n - level + 1);
    return D[n] = n * n + dfs(n - level) + dfs(n - level + 1) - dfs(n - level - level + 2);
}

llt proc(){
    return dfs(N);
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("z.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    D.assign(1000000+100, -1);
    D[1] = 1;
    D[2] = 5;
    D[3] = 10;
    int nofkase; cin >> nofkase;
    while(nofkase--){
        cin >> N;
        cout << proc() << endl;
    }
    return 0;
}

