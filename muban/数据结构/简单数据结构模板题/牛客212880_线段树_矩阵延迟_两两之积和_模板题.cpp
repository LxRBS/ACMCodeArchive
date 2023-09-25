/**
 * 区间增加，区间倍乘，延迟标记是用矩阵
 * 需要求区间内两两之积的和，维护和与方和，再计算一下即可
 */
#include <bits/stdc++.h>
using namespace std;

#include <bits/extc++.h>
using namespace __gnu_pbds;

using llt = long long;
llt MOD;

llt qpow(llt a, llt n){
    a %= MOD;
    llt ret = 1;
    while(n){
        if(n & 1) ret = ret * a % MOD;
        a = a * a % MOD;
        n >>= 1;
    }
    return ret;
}

inline llt inv(llt x){return qpow(x, MOD - 2);}

struct SegTree{ // 线段树带延迟

using llt = long long;

using value_type = pair<llt, llt>; // <和，方和>
vector<value_type> data; // 线段树

using lazy_type = array<llt, 2>; // [k, b]
vector<lazy_type> lazy; // 延迟标记

/// 从下往上计算信息，要变动
value_type _up_(const value_type & ls, const value_type & rs) {
    return {(ls.first + rs.first) % MOD, (ls.second + rs.second) % MOD};
}

/// 从上往下计算信息，要变动
void _dn_(int t, int s, int e, const lazy_type & delta) {
    auto sum = data[t].first, s2 = data[t].second;
    auto n = e - s + 1;
    data[t].first = (sum * delta[0] % MOD + n * delta[1] % MOD) % MOD;
    data[t].second = (delta[0] * delta[0] % MOD * s2 % MOD + n * delta[1] % MOD * delta[1] % MOD + 2 * delta[0] % MOD * delta[1] % MOD * sum % MOD) % MOD;

    auto & lz = lazy[t];
    lz[0] = lz[0] * delta[0] % MOD;
    lz[1] = (delta[0] * lz[1] % MOD + delta[1]) % MOD;    
}

/// 初始化，清零，不用动
void init(int n) {
    data.assign(n + 1 << 2, value_zero());
    lazy.assign(n + 1 << 2, lazy_zero());
}

/// 这个函数不用动
void build(int n) {
    _build(1, 1, n);
}

/// 几乎不用动
value_type query(int t, int s, int e, int a, int b) {
    if(a <= s and e <= b) {
        return data[t];
    }
    _pushDown(t, s, e);
    int mid = (s + e) >> 1;
    value_type ans = value_zero();
    if(a <= mid) ans = _up_(ans, query(lson(t), s, mid, a, b));
    if(mid < b) ans = _up_(ans, query(rson(t), mid + 1, e, a, b));
    return ans;
}

/// 几乎不用动
void modify(int t, int s, int e, int a, int b, const lazy_type & delta) {
    if(a <= s and e <= b) {
        _dn_(t, s, e, delta);
        return;
    }
    _pushDown(t, s, e);
    int mid = (s + e) >> 1;
    if(a <= mid) modify(lson(t), s, mid, a, b, delta);
    if(mid < b) modify(rson(t), mid + 1, e, a, b, delta);
    _pushUp(t);
    return;
}

/// 这个函数不用动
void _pushUp(int t) {
    data[t] = _up_(data[lson(t)], data[rson(t)]);
}

/// 这个函数几乎不用动
void _pushDown(int t, int s, int e) {
    if(lazy_zero() == lazy[t]) return;
    auto & lz = lazy[t];
    auto ls = lson(t), rs = rson(t);
    int mid = (s + e) >> 1;

    _dn_(ls, s, mid, lz);
    _dn_(rs, mid + 1, e, lz);

    lz = lazy_zero();
}


/// 几乎不用动
void _build(int t, int s, int e) {
    if(s == e) {
        llt x; cin >> x;
        data[t] = {x % MOD, x * x % MOD}; // 注意提供value_type的初始化
        return; 
    }
    int mid = (s + e) >> 1;
    _build(lson(t), s, mid);
    _build(rson(t), mid + 1, e);
    _pushUp(t);
}

/// 辅助函数，视延迟的类型而变动
static const lazy_type & lazy_zero() {
    static const lazy_type LAZY0 = {1LL, 0LL};
    return LAZY0; 
}

/// 辅助函数，视线段树信息类型而变动
static const value_type & value_zero() {
    static const value_type VALUE0 = {0LL, 0LL};
    return VALUE0;
}

/// 这两个函数不用变动
static int lson(int x) {return x << 1;}
static int rson(int x) {return lson(x) | 1;}


};



int main(){
#ifndef ONLINE_JUDGE
    freopen("z.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int nofkase; cin >> nofkase;
    llt inv2;
    while(nofkase--){
        int n, m; cin >> n >> m >> MOD;
        if(2 == MOD) inv2 = 1;
        else inv2 = inv(2LL);
        SegTree st; st.init(n); st.build(n);
        for(int cmd,a,b,q=1;q<=m;++q){
            cin >> cmd >> a >> b;
            if(1 == cmd){
                llt d; cin >> d;
                st.modify(1, 1, n, a, b, {1LL, d % MOD});
            }else if(2 == cmd){
                llt d; cin >> d;
                st.modify(1, 1, n, a, b, {d % MOD, 0LL});
            }else if(3 == cmd){
                auto t = st.query(1, 1, n, a, b);
                auto ans = (t.first * t.first % MOD - t.second) % MOD;
                ans = ans * inv2 % MOD;
                if(ans < 0) ans += MOD;
                cout << ans << endl;
            }else{
                assert(0);
            }  
        }
    }
    return 0;
}