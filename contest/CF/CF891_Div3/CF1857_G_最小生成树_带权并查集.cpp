/**
 * 给定一颗带权树记作T，问有多少个无向图图满足：
 * 1. 该图有唯一的最小生成树，且恰好就是T
 * 2. 该图的边权不超过给定的LIMIT
 * 3. 没有重边和自环边
 * N个点的无向图，显然一共可能有N*(N-1)/2条边，记作M
 * 除去已有的N-1条边，还有M-N+1条可能的边，再考虑权值，一共有 c + 1 的若干次方种可能
 * 其中c是权值可能取到的值的数量
 * 关键在于c的确定。
 * 对MST上的每一条边，记作(u, v):
 *  假设u、v分属不同的连通块，则加入u/v以后，
 *  即max为该新连通块的最大边权，us为原u连通块的点数，vs为原v连通块的点数
 *  则一共可以添加的边的点对有 us * vs - 1 对，边的权值一共有 LIMIT - max + 1 个，加1是值可以没有边
 *  则对结果的贡献是 (c + 1) ^ (us * vs - 1) 。
 * 依次乘起来即可。
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

map<pii, int> W;
vi Father;
vi Sz;
vi Max;
void init(int n){
    Max.assign(n + 1, 0);
    Sz.assign(n + 1, 1);
    Father.assign(n + 1, 0);
    for(int i=1;i<=n;++i) Father[i] = i;
}

int find(int x){
    return x == Father[x] ? x : Father[x] = find(Father[x]);
}

void unite(int x, int y){
    if(x > y) swap(x, y);
    auto it = W.find({x, y});
    assert(it != W.end());    

    x = find(x);
    y = find(y);
    if(x == y) return;
    Father[y] = x;
    Sz[x] += Sz[y];
    Max[x] = max(Max[x], it->second);
    Max[x] = max(Max[x], Max[y]);
}

llt const MOD = 998244353LL;
llt qpow(llt a, llt n){
    llt ans = 1;
    while(n){
        if(n & 1) ans = ans * a % MOD;
        a = a * a % MOD;
        n >>= 1;
    }
    return ans;
}

llt S;

struct _t{
    int u;
    int v;
    int w;
    _t(int a, int b, int c):u(a),v(b),w(c){}
    bool operator < (const _t & rhs) const {
        if(this->w != rhs.w) return this->w < rhs.w;
        if(this->u != rhs.u) return this->u < rhs.u;
        return this->v < rhs.v;
    }
};

int N;
vector<_t> Edges;


llt proc(){
    init(N);
    sort(Edges.begin(), Edges.end());

    llt ans = 1LL;
    for(int i=0;i<N-1;++i){
        const auto & e = Edges[i];

        int u = find(e.u);
        int v = find(e.v);
        if(u == v) continue;

        int su = Sz[u], sv = Sz[v];
        unite(e.u, e.v);
        llt c = S - Max[find(e.u)];
        
        // (ans += (su - 1LL) * sv * c) %= MOD;
        // (ans += (sv - 1LL) * su * c) %= MOD;

        // auto tmp = qpow(2LL, ((llt)su * sv - 1LL)*c%MOD);
        // auto tmp = (((llt)su * sv - 1LL) * c + 1) % MOD;
        auto tmp = qpow(c + 1, (llt)su * sv - 1LL);
        (ans *= tmp) %= MOD; 

        
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
        cin >> N >> S;
        Edges.assign(N - 1, {0, 0, 0});
        W.clear();
        for(auto & i : Edges){
            cin >> i.u >> i.v >> i.w;
            if(i.u > i.v) swap(i.u, i.v);
            W[{i.u, i.v}] = i.w;
        }
        cout << proc() << endl;
    }
    return 0;
}
