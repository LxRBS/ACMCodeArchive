/**
 * 给定数组A，再给定x和y，
 * 问是存在多少对(Ai, Aj)，满足： Ai + Aj = x， Ai * Aj = y
 * 显然解一个一元二次方程，然后根据解的情况计算一下即可
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
int M;
map<int, int> A;

llt proc(llt x, llt y){
    auto xx = x * x - y - y - y - y;
    if(xx < 0) return 0LL;

    if(xx == 0){
        if(x % 2 == 1) return 0LL;
        int t = x / 2;
        auto it = A.find(t);
        if(it == A.end() or it->second < 2) return 0LL;
        return (it->second - 1LL) * it->second / 2LL;
    }

    Real tmp = sqrt((Real)xx);
    llt rt = (llt)tmp;
    if(rt * rt != xx) return 0LL;

    auto cha = x + rt;
    if(cha & 1) return 0LL;

    auto u = (x + rt) / 2;
    auto v = (x - rt) / 2;
    if((int)u != u or (int)v != v) return 0LL;

    auto ut = A.find(u);
    auto vt = A.find(v);
    if(ut == A.end() or vt == A.end()) return 0LL;
    return (llt)ut->second * (llt)vt->second;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("z.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int nofkase; cin >> nofkase;
    while(nofkase--){
        cin >> N;
        A.clear();
        for(int a,i=0;i<N;++i) {cin >> a; ++A[a];}

        cin >> M;
        for(int q=1;q<=M;++q){
            llt x, y;
            cin >> x >> y;
            cout << (proc(x, y)) << " ";
        }
        cout << endl;
    }
    return 0;
}
