/**
 * 区间修改操作为加一个等差数列
 * 可以维护差分数组，这里直接维护延迟标记为 <首项, 公差>
 */
#include <bits/stdc++.h>
using namespace std;

#include <bits/extc++.h>
using namespace __gnu_pbds;

struct SegTree{ // 线段树带延迟

using llt = long long;

using value_type = llt;
vector<value_type> data; // 线段树

using lazy_type = pair<llt, llt>; // 首项, 公差
vector<lazy_type> lazy; // 延迟标记

/// 从下往上计算信息，要变动
value_type _up_(const value_type & ls, const value_type & rs) {
    return ls + rs;
}

/// 从上往下计算信息，要变动
void _dn_(int t, int s, int e, const lazy_type & delta) {
    auto n = e - s + 1;
    data[t] += delta.first * n + delta.second * n * (n - 1) / 2;
    lazy[t].first += delta.first;
    lazy[t].second += delta.second;
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
        /// 这里注意，不是简单的更新delta，而是需要计算s和a的关系
        _dn_(t, s, e, {delta.first + delta.second * (s - a), delta.second});
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
    /// 右儿子需要改一下，不能简单的传lz
    _dn_(rs, mid + 1, e, {lz.first + lz.second * (mid + 1 - s), lz.second});

    lz = lazy_zero();
}


/// 几乎不用动
void _build(int t, int s, int e) {
    if(s == e) {
        int x; cin >> x;
        data[t] = value_type(x); // 注意提供value_type的初始化
        return; 
    }
    int mid = (s + e) >> 1;
    _build(lson(t), s, mid);
    _build(rson(t), mid + 1, e);
    _pushUp(t);
}

/// 辅助函数，视延迟的类型而变动
static const lazy_type & lazy_zero() {
    static const lazy_type LAZY0 = {0LL, 0LL};
    return LAZY0; 
}

/// 辅助函数，视线段树信息类型而变动
static const value_type & value_zero() {
    static const value_type VALUE0 = 0;
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
    int n, q; cin >> n >> q;
    SegTree st; st.init(n); st.build(n);
    for(int cmd,qi=1;qi<=q;++qi){
        cin >> cmd;
        if(1 == cmd){
            int a, b, k, d;
            cin >> a >> b >> k >> d;
            st.modify(1, 1, n, a, b, {k, d});  
        }else if(2 == cmd){  
            int p; cin >> p;
            cout << st.query(1, 1, n, p, p) << endl;
        }else{
            assert(0);
        }

    }
    return 0;
}