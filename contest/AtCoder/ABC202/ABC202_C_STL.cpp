/**
 * 给定数组A、B、C，问有多少对(i, j)满足 Ai = B[Cj]
 * 对每一个Ai，首先去查找有多少个Bk与之相等，然后在对每一个k查找有多少个Cj与k相等
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

int N;
vi A, B, C;
map<int, vi> Ma, Mb, Mc;

void calc(const vi & v, map<int, vi> & m){
    for(int i=1;i<=N;++i) m[v[i]].push_back(i);
}

llt proc(){
    calc(A, Ma);
    calc(B, Mb);
    calc(C, Mc);

    llt ans = 0;
    for(const auto & p : Ma){
        int val = p.first;
        llt base = p.second.size();

        auto it = Mb.find(val);
        if(it == Mb.end()) continue;

        llt tmp = 0;
        for(auto pos : it->second){
            auto jt = Mc.find(pos);
            if(jt == Mc.end()) continue;
            tmp += jt->second.size();
        }
        ans += base * tmp;
    }
    return ans;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("z.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N;
    A.assign(N + 1, 0);
    B.assign(N + 1, 0);
    C.assign(N + 1, 0);
    for(int i=1;i<=N;++i)cin >> A[i];
    for(int i=1;i<=N;++i)cin >> B[i];
    for(int i=1;i<=N;++i)cin >> C[i];
    cout << proc() << endl;
    return 0;
}