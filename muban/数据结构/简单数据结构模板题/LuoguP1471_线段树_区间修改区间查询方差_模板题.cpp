/**
 * 要求区间增加，区间查询平均数与方差。
 * 查询平均数显然是维护和，查询方差则需要同时维护平方和与和。
 * 方差 = SIGMA{(ai - x) ^ 2}， 其中 x = SIGMA{ai} / N
 * 简单推导有 方差 = (SIGMA{ai ^ 2} - SIGMA{ai} / N) / N
 * 因此同时维护和与平方和即可
 * 对于延迟操作，
 * SIGMA{(ai + d) ^ 2} = SIGMA{ai ^ 2} + 2dSIGMA{ai} + 2(e-s+1)*d^2
 * 因此维护平方和就需要维护和。
 * 本题即使不询问平均数，也需要维护和
 */
#include <bits/stdc++.h>
using namespace std;

#include <bits/extc++.h>
using namespace __gnu_pbds;


struct SegTree{ // 线段树带延迟

using llt = long long;

using value_type = pair<double, double>; // <和, 平方和>
vector<value_type> data; // 线段树

using lazy_type = double;
vector<lazy_type> lazy; // 延迟标记

/// 从下往上计算信息，要变动
value_type _up_(const value_type & ls, const value_type & rs) {
    return {ls.first + rs.first, ls.second + rs.second};
}

/// 从上往下计算信息，要变动
void _dn_(int t, int s, int e, const lazy_type & delta) {
    auto n = e - s + 1;
    data[t].second += data[t].first * 2 * delta + n * delta * delta;
    data[t].first += n * delta;
    lazy[t] += delta;    
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
        double x; cin >> x;
        data[t] = {x, x * x}; // 注意提供value_type的初始化
        return; 
    }
    int mid = (s + e) >> 1;
    _build(lson(t), s, mid);
    _build(rson(t), mid + 1, e);
    _pushUp(t);
}

/// 辅助函数，视延迟的类型而变动
static const lazy_type & lazy_zero() {
    static const lazy_type LAZY0 = 0;
    return LAZY0; 
}

/// 辅助函数，视线段树信息类型而变动
static const value_type & value_zero() {
    static const value_type VALUE0 = {0., 0.};
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
    int n, m; cin >> n >> m;
    SegTree st; st.init(n); st.build(n);
    for(int c,a,b,q=1;q<=m;++q){
        cin >> c >> a >> b;
        if(1 == c){
            double k; cin >> k;
            st.modify(1, 1, n, a, b, k);
        }else if(2 == c){
            auto p = st.query(1, 1, n, a, b);
            cout << fixed << setprecision(4) << p.first / (b - a + 1) << endl;
        }else if(3 == c){
            auto p = st.query(1, 1, n, a, b);
            auto n = b - a + 1;
            cout << fixed << setprecision(4) << (p.second - p.first * p.first / n) / n << endl;
        }else{
            assert(0);
        }
    }
    return 0;
}