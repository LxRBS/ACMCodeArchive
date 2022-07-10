/**
 * 线段树，支持三种操作：
 * 倍乘，增加，查询区间内两两乘积之和
 * 维护和与方和以及[k, b]的矩阵延迟
 * 查出指定区间的方和以及和，运算一下即可。
 * modify处的修改以及pushDown处的修改可以使用统一的函数完成
 * 只需传入相应的参数即可
 */
#include <bits/stdc++.h>
using namespace std;

#ifndef ONLINE_JUDGE
int const SIZE = 7;
#else
int const SIZE = 1E5+7;
#endif

using llt = long long int;
llt MOD;

inline llt add(llt a, llt b){return (a+b)%MOD;}
inline llt add(llt a, llt b, llt c){return add(a, add(b, c));}
inline llt mul(llt a, llt b){return a*b%MOD;}
inline llt mul(llt a, llt b, llt c){return mul(a, mul(b, c));}
inline llt mul(llt a, llt b, llt c, llt d){return mul(a, mul(b, mul(c, d)));}
inline llt sub(llt a, llt b){return add((a-b)%MOD,MOD);}

llt power(llt a, llt n){
    llt ans = 1;
    while(n){
        if(n&1) ans = mul(ans, a);
        a = mul(a, a);
        n >>= 1;
    }
    return ans;
}

inline llt inv(llt x){
    return power(x, MOD-2);
}

llt Inv2;

llt St[SIZE<<2];
llt S2[SIZE<<2];

typedef llt lazy_t[2];
lazy_t Lazy[SIZE<<2];

inline int lson(int t){return t<<1;}
inline int rson(int t){return lson(t)|1;}

inline void _pushUp(int t){
    St[t] = add(St[lson(t)], St[rson(t)]);
    S2[t] = add(S2[lson(t)], S2[rson(t)]);
}

/// 根据lazy更新节点t，t的长度为len
inline void _f(int t, int len, llt k, llt b){
    llt s = St[t], s2 = S2[t];

    St[t] = add(mul(s, k), mul(len, b));
    S2[t] = add(mul(k, k, s2), mul(2, k, b, s), mul(len, b, b));
}

inline void _g(int t, llt k, llt b){
    llt k2 = Lazy[t][0], b2 = Lazy[t][1];

    Lazy[t][0] = mul(k, k2);
    Lazy[t][1] = add(mul(k, b2), b);
}

inline void _pushDown(int t, int s, int e){
    if(1 == Lazy[t][0] && 0 == Lazy[t][1]) return;

    llt &k = Lazy[t][0], &b = Lazy[t][1];
    /// 更新儿子的值
    int mid = (s + e) >> 1;
    _f(lson(t), mid - s + 1, k, b);
    _f(rson(t), e - mid, k, b);

    /// 跟新儿子的延迟标记
    _g(lson(t), k, b);
    _g(rson(t), k, b);

    k = 1;
    b = 0; 
}

using pii = pair<llt, llt>;
inline pii add(const pii&a, const pii&b){
    return {add(a.first, b.first), add(a.second, b.second)};
}

pii query(int t, int s, int e, int a, int b){
    if(a<=s && e<=b){
        return {St[t], S2[t]};
    }
    _pushDown(t, s, e);
    int mid = (s+e) >> 1;    
    pii ans = {0LL, 0LL};
    if(a <= mid) ans = add(ans, query(lson(t), s, mid, a, b));
    if(mid < b) ans = add(ans, query(rson(t), mid+1, e, a, b));
    return ans;
}

void modify(int t, int s, int e, int a, int b, int op, llt v){
    if(a <= s && e <= b){
        if(1 == op){ // 加
            _f(t, e-s+1, 1, v);
            _g(t, 1, v);
        }else if(2 == op){ // 乘
            _f(t, e-s+1, v, 0);
            _g(t, v, 0);
        }else{
            throw runtime_error("wrong cmd");
        }
        return;
    }
    _pushDown(t, s, e);
    int mid = (s + e) >> 1;
    if(a <= mid) modify(lson(t), s, mid, a, b, op, v);
    if(mid < b) modify(rson(t), mid+1, e, a, b, op, v);
    _pushUp(t);
}

void build(int t, int s, int e){
    Lazy[t][0] = 1; Lazy[t][1] = 0;

    if(s == e){
        cin >> St[t];
        S2[t] = mul(St[t], St[t]);
        return;
    }

    int mid = (s + e) >> 1;
    build(lson(t), s, mid);
    build(rson(t), mid+1, e);
    _pushUp(t);
}

int N, M;

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int nofkase; cin >> nofkase;
    while(nofkase--){
        cin >> N >> M >> MOD;
        Inv2 = inv(2);
        build(1, 1, N);
        for(int op,a,b,q=1;q<=M;++q){
            cin >> op >> a >> b;
            if(op <= 2){
                llt v; cin >> v;
                modify(1, 1, N, a, b, op, v);
            }else{
                auto p = query(1, 1, N, a, b);
                llt ans = sub(mul(p.first, p.first), p.second);
                if(MOD != 2){
                    ans = mul(ans, Inv2);
                }else if(!ans){
                    ans = 1;
                }
                cout << ans << endl;
            }
        }
    }
    return 0;
}