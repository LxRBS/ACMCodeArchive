#include <functional>
#include <algorithm>
#include <iostream>
#include <vector>
#include <map>
using namespace std;
typedef long long ll;
typedef pair<ll, int> P;

const int INF = 10000000;

template <typename T>
struct SegmentTree
{
    using F = function<T(T, T)>;
    
    const F f;
    const T e;
    
    int n;
    vector<T> seg;
    
    SegmentTree(int nn, const F f, const T e) : f(f), e(e){
        n = 1;
        while(n <= nn) n <<= 1;
        seg.assign(n * 2, e);
    }
    
    void set(int i, T x){
        seg[i + n] = x;
    }
    
    void build(){
        for(int k = n - 1; k > 0; k--){
            seg[k] = f(seg[k * 2], seg[k * 2 + 1]);
        }
    }
    
    void update(int i, T x){
        int k = i + n;
        seg[k] = x;
        while(k >>= 1){
            seg[k] = f(seg[k * 2], seg[k * 2 + 1]);
        }
    }
    
    T query(int l, int r){
        l += n, r += n;
        T L = e, R = e;
        for(; l != r; l >>= 1, r >>= 1){
            if(l % 2) L = f(L, seg[l++]);
            if(r % 2) R = f(seg[--r], R);
        }
        return f(L, R);
    }
    
    T operator[](const int i)const {
        return seg[i + n];
    }
};

ll l[200005], u[200005];
int dp[200005];
P p[200005];

void divide_conquer(int a, int b, int d){
    if(b - a <= d){
        for(int i = max(a, 1); i < b; i++) dp[i] = max(dp[i], dp[i - 1]);
        return;
    }
    divide_conquer(a, (a + b) / 2, d);
    for(int c = 0; c < d; c++){
        if(a + c + d >= b) continue;
        map<ll, int> mp;
        int m = 0, k = 0;
        for(int i = a + c; i < b; i += d) mp[l[i]] = m++;
        for(auto itr = mp.begin(); itr != mp.end(); itr++) mp[itr->first] = k++;
        for(int e = 0; e < m; e++){
            int i = a + c + d * e;
            p[e] = P(u[i], i);
        }
        sort(p, p + m);
        SegmentTree<int> seg(k, [](int a, int b){return max(a, b);}, -INF);
        for(int e = 0; e < m; e++){
            int i = p[e].second;
            if(i < (a + b) / 2) seg.update(mp[l[i]], max(seg[mp[l[i]]], dp[i] - i / d));
            else dp[i] = max(dp[i], seg.query(mp[l[i]], k) + i / d);
        }
    }
    for(int i = (a + b) / 2; i < b; i++) dp[i] = max(dp[i], dp[i - 1]);
    divide_conquer((a + b) / 2, b, d);
}

void solve(){
    int n, r, b;
    string s;
    cin >> n >> r >> b >> s;
    int d = r + b;
    for(int i = 1; i <= n; i++){
        if(s[i - 1] == 'R') l[i] = l[i - 1] + b;
        else l[i] = l[i - 1] - r;
        if(s[i - 1] == 'B') u[i] = u[i - 1] - r;
        else u[i] = u[i - 1] + b;
    }
    divide_conquer(0, n + 1, d);
    cout << dp[n] << endl;
}

int main()
{
    solve();
}
