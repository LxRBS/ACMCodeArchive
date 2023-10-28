/**
 * 01数组，支持5种区间操作：
 * 0: 清零
 * 1: 置1
 * 2: 取反
 * 3: 求和
 * 4: 最长连续1的长度
 * 显然要记录和、左起1连续长度、右起1连续长度、最长1连续长度
 * 考虑到要支持取反操作，因此还需要记录左起0连续长度、右起0连续长度、最长0连续长度
 * 因此一共要维护7个值
 * 延迟标记用一个整数表示即可
 */
#include <bits/stdc++.h>
using namespace std;

#include <bits/extc++.h>
using namespace __gnu_pbds;


struct SegTree{ // 线段树带延迟

using llt = long long;

struct _t{
    int sum;   // 和
    array<int, 2> seq;   // 最长连续
    array<int, 2> left;  // 左连续
    array<int, 2> right; // 右连续
    void print(int t) const {
        printf("%d: sum = %d, seq = {%d, %d}, left = {%d, %d}, right = {%d, %d}\n"
            , t, sum, seq[0], seq[1], left[0], left[1], right[0], right[1]);
    }
    void sprint(char * p) const {
        sprintf(p, "%d: sum = %d, seq = {%d, %d}, left = {%d, %d}, right = {%d, %d}\n"
            , 0, sum, seq[0], seq[1], left[0], left[1], right[0], right[1]);        
    }
    bool operator == (const _t & b) const {
        return sum == b.sum and left == b.left and right == b.right and seq == b.seq;
    }
};

using value_type = _t;
vector<value_type> data; // 线段树

/**
 * 0: 无标记
 * 1: 置1
 * 2: 置0
 * 4: 取反
 */
using lazy_type = int;
vector<lazy_type> lazy; // 延迟标记 

/// 从下往上计算信息，要变动
value_type _up_(const value_type & ls, const value_type & rs) {
    if(ls == value_zero()) return rs;
    if(rs == value_zero()) return ls;

    value_type ans = {0, 0, 0, 0, 0};
    ans.sum = ls.sum + rs.sum;
    ans.seq[1] = max(max(ls.seq[1], rs.seq[1]), ls.right[1] + rs.left[1]);
    ans.seq[0] = max(max(ls.seq[0], rs.seq[0]), ls.right[0] + rs.left[0]);

    int st = 0;
    if(0 == ls.seq[0])
    {
        assert(0 == ls.left[0] and 0 == ls.right[0] and ls.left[1] == ls.sum and ls.seq[1] == ls.sum and ls.right[1] == ls.sum);
        st |= 2;
    }
    if(0 == rs.seq[0]){
        assert(rs.left[1] == rs.right[1] and rs.left[1] == rs.seq[1]);
        st |= 1;
    }
    if(3 == st) { // 全满
        assert(ans.seq[1] == ans.sum and 0 == ans.seq[0]);
        ans.left = ans.right = {0, ans.sum};
        return ans;
    }
    if(2 == st){ // 左满
        ans.left = {0, ls.left[1] + rs.left[1]};
        ans.right = rs.right;
        return ans;
    }
    if(1 == st){ // 右满
        ans.left = ls.left;
        ans.right = {0, ls.right[1] + rs.right[1]};
        return ans;
    }

    st = 0;
    if(0 == ls.sum){
        if(not (ls.left[0] == ls.right[0] and ls.left[0] == ls.seq[0])){
            throw runtime_error("XX");
        }
        st |= 2;
    }
    if(0 == rs.sum){
        assert(rs.left[0] == rs.right[0] and rs.left[0] == rs.seq[0]);
        st |= 1;
    }
    if(3 == st){ // 全空
        assert(0 == ans.seq[1] and 0 == ans.sum);
        ans.left = ans.right = {ans.seq[0], 0};
    }else if(2 & st){ // 左空
        ans.left = {ls.left[0] + rs.left[0], 0};
        ans.right = rs.right;
    }else if(1 & st){ // 右空
        ans.left = ls.left;
        ans.right = {ls.right[0] + rs.right[0], 0};
        ans.right[0] = rs.right[0] + ls.right[0];
    }else{ // 非空非满
        ans.left = ls.left;
        ans.right = rs.right;
    }

    return ans;
}

/// 从上往下计算信息，要变动
void _dn_(int t, int s, int e, const lazy_type & delta) {
    auto & v = data[t];
    auto & lz = lazy[t];
    auto n = e - s + 1;
    
    if(delta & 4){ // 取反
        v.sum = n - v.sum;
        swap(v.seq[0], v.seq[1]);
        swap(v.left[0], v.left[1]);
        swap(v.right[0], v.right[1]);  
        
        if(0 == lz) lz = 4;
        else if(1 == lz) lz = 2;
        else if(2 == lz) lz = 1;
        else if(4 == lz) lz = 0;
        else assert(0);  
    }else if(delta & 2){ // 置零
        v.left = v.right = v.seq = {n, v.sum = 0};
        lz = 2;
    }else if(delta & 1){ // 置1
        v.left = v.right = v.seq = {0, v.sum = n};
        lz = 1;         
    }else{
        assert(0);
    }
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
    // data[lson(t)].print(lson(t));
    // data[rson(t)].print(rson(t));

    data[t] = _up_(data[lson(t)], data[rson(t)]);    

    // data[t].print(t);
    // printf("\n");
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
        if(x){
            data[t] = {1, {0, 1}, {0, 1}, {0, 1}};
        }else{
            data[t] = {0, {1, 0}, {1, 0}, {1, 0}};
        }
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
    static const value_type VALUE0 = {0, {0, 0}, {0, 0}, {0, 0}};
    return VALUE0;
}

/// 这两个函数不用变动
static int lson(int x) {return x << 1;}
static int rson(int x) {return lson(x) | 1;}


};

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.in", "r", stdin);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int n, m; cin >> n >> m;
    SegTree st; st.init(n); st.build(n);
    for(int cmd,a,b,q=1;q<=m;++q){
        // printf("OP: %d\n", q);
        cin >> cmd >> a >> b;
        ++a; ++b;
        switch(cmd){
            case 0: st.modify(1, 1, n, a, b, 2); break;
            case 1: st.modify(1, 1, n, a, b, 1); break;
            case 2: st.modify(1, 1, n, a, b, 4); break;
            case 3: cout << st.query(1, 1, n, a, b).sum << endl; break;
            case 4: cout << st.query(1, 1, n, a, b).seq[1] << endl; break;
            default:assert(0);
        }
    }
    return 0;
}