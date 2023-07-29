/**
 * 有一个方阵，将其看作是一圈一圈包起来构成的。
 * 给定两个坐标，问到达需要穿过多少个圈
 * 将所有坐标全部转为所在圈的左上角坐标即可
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

#ifndef ONLINE_JUDGE
int const SZ = 34;
#else
int const SZ = 200000 + 12;
#endif

int N;
pii S, T;

pii anchor(pii p){
    if(p.first == p.second){
        if(p.first <= N / 2) return p;
        return {N + 1 - p.first, N + 1 - p.first};
    }

    if(p.first > p.second) swap(p.first, p.second);
    if(p.first + p.second <= N + 1) return {p.first, p.first};
    return {N + 1 - p.second, N + 1 - p.second};
}

int proc(){
    auto p = anchor(S);
    auto q = anchor(T);
    return abs(p.first - q.first);
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("z.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int nofkase; cin >> nofkase;
    while(nofkase--){
        cin >> N >> S.first >> S.second >> T.first >> T.second;
        cout << proc() << endl;
    }
    return 0;
}

