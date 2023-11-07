/**
 * 支持两种操作：
 * 1. 区间增加
 * 2. 给定K，从[1...]开始减，直到把K减完
 * 
 * 第二个操作显然要二分先找到位置pos, pos是满足sum[1...pos]>=K的第一个位置
 * 然后将 [1...pos-1] 清零， 再将剩下的从pos位置减去即可
 * 
 * 因此需要区间设置、区间增加、区间求和操作
 */
#include <bits/stdc++.h>
using namespace std;

struct SegTree{ // 线段树带延迟

using llt = long long;

using value_type = llt;
vector<value_type> data; // 线段树

using lazy_type = pair<llt, pair<bool, llt>>; // <增加, <设置, 标记>>
vector<lazy_type> lazy; // 延迟标记

/// 从下往上计算信息，要变动
value_type _up_(const value_type & ls, const value_type & rs) {
    return ls + rs;
}

/// 从上往下计算信息，要变动
void _dn_(int t, int s, int e, const lazy_type & delta) {
    auto n = e - s + 1;
    /// 有设置之前的数据全作废，没有设置就是增加
    if(delta.second.first) data[t] = n * (delta.first + delta.second.second);
    else data[t] += n * delta.first;
    /// 如果有设置标记，之前的lazy全部作废，否则就只增加
    if(delta.second.first) lazy[t] = delta;
    else lazy[t].first += delta.first;
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
    static const lazy_type LAZY0 = {0LL, {false, 0LL}};
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

int N, Q;
SegTree St;

int proc(int x){
    if(x > St.query(1, 1, N, 1, N)) return -1;
    int left = 1, right = N, mid;
    do{
        mid = (left + right) >> 1;
        if(St.query(1, 1, N, 1, mid) < x) left = mid + 1;
        else right = mid - 1;
    }while(left <= right);
    
    auto ans = left;
    if(ans > 1) {
        x -= St.query(1, 1, N, 1, ans - 1);
        St.modify(1, 1, N, 1, ans - 1, {0LL, {true, 0LL}}); 
    }

    St.modify(1, 1, N, ans, ans, {-x, {false, 0LL}});
    return ans;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("z.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int nofkase; cin >> nofkase;
    while(nofkase--){
        cin >> N >> Q;
        St.init(N);
        for(int c,a,b,x,q=1;q<=Q;++q){
            cin >> c;
            if(1 == c){
                cin >> a >> b >> x;
                St.modify(1, 1, N, a, b, {0LL + x, {false, 0LL}});
            }else if(2 == c){
                cin >> x;
                auto ans = proc(x);
                if(-1 == ans) cout << "Trote_w is sb" << endl;
                else cout << ans << endl;
            }else{
                assert(0);
            }
        }
    }
    return 0;
}