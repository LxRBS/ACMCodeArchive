/**
 *   区间查询sin和
 *   同时维护sin和与cos和，并记录延迟标记即可
 */
#include <bits/stdc++.h>
using namespace std;

#include <bits/extc++.h>
using namespace __gnu_pbds;


struct SegTree{ // 线段树带延迟

using llt = long long;

using value_type = pair<double, double>;
vector<value_type> data; // 线段树

using lazy_type = double;
vector<lazy_type> lazy; // 延迟标记

/// 从下往上计算信息，要变动
value_type _up_(const value_type & ls, const value_type & rs) {
    return {ls.first + rs.first, ls.second + rs.second};
}

/// 从上往下计算信息，要变动
void _dn_(int t, int s, int e, const lazy_type & delta) {
    auto sind = sin(delta), cosd = cos(delta);
    auto sina = data[t].first, cosa = data[t].second;
    data[t].first = sina * cosd + sind * cosa;
    data[t].second = cosa * cosd - sina * sind;
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
        int x; cin >> x;
        data[t] =  {sin((double)(x)), cos((double)x)}; // 注意提供value_type的初始化
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
    int n; cin >> n;
    SegTree st; st.init(n); st.build(n);
    int m; cin >> m;
    for(int c,a,b,q=1;q<=m;++q){
        cin >> c >> a >> b;
        if(1 == c){
            double v; cin >> v;
            st.modify(1, 1, n, a, b, v);
        }else if(2 == c){
            cout << fixed << setprecision(1) << st.query(1, 1, n, a, b).first << endl; 
        }else{
            assert(0);
        }
    }
    return 0;
}