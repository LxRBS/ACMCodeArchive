/**
 * 区间加、区间乘、区间求和
 * 令加为b，乘为k，则延迟矩阵为
 * k b
 * 0 1
 */
#include <bits/stdc++.h>
using namespace std;

#include <bits/extc++.h>
using namespace __gnu_pbds;

long long MOD;


struct SegTree{ // 线段树带延迟

using llt = long long;

using value_type = llt;
vector<value_type> data; // 线段树

using lazy_type = array<array<llt, 2>, 2>;
vector<lazy_type> lazy; // 延迟标记

/// 从下往上计算信息，要变动
value_type _up_(const value_type & ls, const value_type & rs) {
    return (ls + rs) % MOD;
}

/// 从上往下计算信息，要变动
void _dn_(int t, int s, int e, const lazy_type & delta) {
    data[t] = (delta[0][0] * data[t] % MOD + delta[0][1] * (e - s + 1) % MOD) % MOD;
    auto & lz = lazy[t];
    lz[0][0] = lz[0][0] * delta[0][0] % MOD;
    lz[0][1] = (delta[0][0] * lz[0][1] % MOD + delta[0][1]) % MOD;
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
    if(ans < 0) ans += MOD;
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
    static const lazy_type LAZY0 = {array<llt, 2>{1LL, 0LL}, array<llt, 2>{0LL, 1LL}};
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
    int n, q; cin >> n >> q >> MOD;
    SegTree st;
    st.init(n); st.build(n);
    for(int cmd,a,b,qi=1;qi<=q;++qi){
        cin >> cmd >> a >> b;
        if(1 == cmd){
            int d; cin >> d;
            st.modify(1, 1, n, a, b, {array<long long, 2>{d, 0}, array<long long, 2>{0, 1}});      
        }else if(2 == cmd){  
            int d; cin >> d;
            st.modify(1, 1, n, a, b, {array<long long, 2>{1, d}, array<long long, 2>{0, 1}});
        }else if(3 == cmd){
            cout << st.query(1, 1, n, a, b) << endl;
        }else{
            assert(0);
        }

    }
    return 0;
}