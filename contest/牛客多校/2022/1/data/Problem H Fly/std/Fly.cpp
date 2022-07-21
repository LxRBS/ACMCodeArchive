#include <bits/stdc++.h>

typedef long long ll;
const int MAX = 20;
const int moder = 998244353;
const int root = 3;
const int invroot = (moder + 1) / root;

void add(int &u, int v){
    u += v;
    u -= u >= moder ? moder : 0;
}

void sub(int &u, int v){
    u -= v;
    u += u < 0 ? moder : 0;
}

int w[2][1 << MAX];

int powermod(int a, int exp){
    int ret = 1;
    for ( ; exp > 0; exp >>= 1){
        if (exp & 1){
            ret = 1ll * a * ret % moder;
        }
        a = 1ll * a * a % moder;
    }
    return ret;
}

void init(){
    w[0][0] = w[1][0] = 1;
    w[0][1] = powermod(root, (moder - 1) >> MAX);
    for (int i = 2; i < (1 << MAX); ++i){
        w[0][i] = 1ll * w[0][i - 1] * w[0][1] % moder;
    }
    for (int i = 1; i < (1 << MAX); ++i){
        w[1][(1 << MAX) - i] = w[0][i];
    }
}

void NTT(std::vector <int> &a, int len, int type){
    for(int i = 1, j = 0; i < len - 1; ++i){
        for(int s = len; j ^= (s >>= 1), ~j & s; )
            ;
        if(i < j){
            std::swap(a[i], a[j]);
        }
    }
    for (int i = 2, d = 1; i <= len; i <<= 1, ++d){
        for (int j = 0; j < len; j += i){
            auto u = a.begin() + j;
            for (int k = 0; k < i / 2; ++k){
                int t = 1ll * w[type][k << (MAX - d)] * u[k + i / 2] % moder;
                u[k + i / 2] = u[k] - t + (u[k] - t < 0 ? moder : 0);
                u[k] += t; u[k] -= u[k] >= moder ? moder : 0;
            }
        }
    }
    if (type == 0) return;
    int inv = powermod(len, moder - 2);
    for (int i = 0; i < len; ++i){
        a[i] = 1ll * a[i] * inv % moder;
    }
}

struct poly{
    std::vector<int> a; int len; poly() : len(-1) {}
    poly(int len) : len(len) { a.resize(len + 1); }
    poly(const poly &p, int len) : len(len) {
        a.resize(len + 1);
        for (int i = 0; i <= len; ++i)
            a[i] = i > p.len ? 0 : p.a[i];
    }
    void addpush(int pos, int value){
        if (pos > len){
            a.resize(pos + 1);
            len = pos;
        }
        add(a[pos], value);
    }
    int &operator [] (int n) { assert(n >= 0 && n <= len); return a[n]; }
    poly operator * (const poly &p) const {
        if (!~len || !~p.len) return poly(-1);
        int n = len + p.len, lenret = 1;
        for ( ; lenret <= n; lenret <<= 1);
        poly ret(*this, lenret);
        std::vector<int> aux(lenret);
        std::copy(p.a.begin(), p.a.begin() + p.len + 1, aux.begin());
        NTT(ret.a, lenret, 0); NTT(aux, lenret, 0);
        for (int i = 0; i < lenret; ++i)
            ret.a[i] = 1ll * ret.a[i] * aux[i] % moder;
        NTT(ret.a, lenret, 1); ret.len = n;
        return ret;
    }

    bool operator <(const poly &p)const{
        return len > p.len;
    }
};

const int N = 100010;
const int BIT = 60;

int a[N];
std::set <int> vec[N];

int main(){
    init();
    int n;
    ll m;
    int k;
    scanf("%d%lld%d", &n, &m, &k);
    std::priority_queue <poly> pq;
    for (int i = 0; i < n; ++ i){
        scanf("%d", &a[i]);
        poly p(a[i]);
        p[0] = p[a[i]] = 1;
        pq.emplace(p);
    }
    for (int i = 0; i < k; ++ i){
        int b, c;
        scanf("%d%d", &b, &c);
        -- b;
        vec[c].emplace(b);
    }
    while (int(pq.size()) > 1){
        poly p1 = pq.top();
        pq.pop();
        poly p2 = pq.top();
        pq.pop();
        pq.emplace(p1 * p2);
    }
    poly p = pq.top();
    poly mult1(0), mult2;
    mult1[0] = 1;
    ++ m;
    for (int i = 0; i < BIT; ++ i){
        poly q = p;
        for (auto u : vec[i]){
            int sz = q.len;
            for (int j = 0; j + a[u] <= sz; ++ j){
                sub(q[j + a[u]], q[j]);
            }
        }
        q.a.resize(q.len + 1);
        mult1 = mult1 * q;
        mult2 = mult2 * q;
        poly mult3, mult4;
        for (int j = 0; j <= mult1.len; ++ j){
            mult3.addpush(j / 2, mult1[j]);
        }
        for (int j = 0; j <= mult2.len; ++ j){
            if (j % 2 == (m >> i & 1)){
                mult4.addpush(j / 2, mult2[j]);
            }
        }
        if ((m >> i & 1) == 1){
            for (int j = 0; j <= mult1.len; j += 2){
                mult4.addpush(j / 2, mult1[j]);
            }
        }
        mult1 = mult3;
        mult2 = mult4;
    }
    if (mult2.len < 0){
        puts("0");
    }
    else{
        printf("%d\n", mult2[0]);
    }
    return 0;
}