#include <bits/stdc++.h>
#define int long long
#define For(i, a, b) for (int i = a, i##end = b; i <= i##end; i++)
#define Rof(i, a, b) for (int i = a, i##end = b; i >= i##end; i--)
#define rep(i, b) for (int i = 1, i##end = b; i <= i##end; i++)
using namespace std;
const int N = 1e3 + 9;
bool ppp;
// char buf[(1<<21)+5],*p1,*p2;
//#define getchar()
//(p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
void chmx(int& x, int y) {
    (x < y) && (x = y);
}
void chmn(int& x, int y) {
    (x > y) && (x = y);
}
int read() {
    int f = 0, x = 0;
    char ch = getchar();
    while (!isdigit(ch)) {
        f |= (ch == '-');
        ch = getchar();
    }
    while (isdigit(ch)) {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return f ? -x : x;
}
int w, m, n;
int gcd(int a, int b) {
    return (!b) ? a : gcd(b, a % b);
}
bool Flag;
struct line {
    int k, b;
    bool operator<(const line& X) const { return k < X.k; }
} A[N];
struct INT {
    int a, b;
    void re() {
        if (a <= 0 && b <= 0)
            a = -a, b = -b;
        if (b < 0) {
            a = -a, b = -b;
        }
        if (a == 0) {
            b = 1;
            return;
        }
        int g = gcd(abs(a), abs(b));
        a /= g;
        b /= g;
        return;
    }
    void mul(int x) {
        a *= x;
        re();
    }
    void add(int x) {
        a += b * x;
        re();
    }
    INT operator-(const INT& X) const {
        INT y;
        y.b = b * X.b;
        y.a = a * X.b - b * X.a;
        y.re();
        return y;
    }
    bool operator<(const INT& X) const { return a * X.b < b * X.a; }
    bool operator==(const INT& X) const { return a == X.a && b == X.b; }
};
struct node {
    INT x, y;
    bool operator<(const node& X) const { return x == X.x ? y < X.y : x < X.x; }
    bool operator==(const node& X) const { return x == X.x && y == X.y; }
} sta[N * N], B[N * N], C[N * N];
int top, lim, ll;
int ok, qweqwe;
unordered_map<int, int> mp;
unordered_map<int, int> re;
bool pppp;
void check() {
    int l = 1, r = 0;
    while (l <= n + w) {
        r = l;
        while (r < n + w && A[r + 1].k == A[l].k)
            r++;
        if ((r - l + 1) % 2) {
            For(i, l, r) mp[A[i].b] = 1;
            ok = A[l].k;
            qweqwe++;
        }
        l = r + 1;
    }
}
signed main() {
    //    printf("%.5lf\n",(&pppp-&ppp)/1024.0/1024.0);
    auto solve = [&]() {
        mp.clear();
        re.clear();
        ok = 0, qweqwe = 0, pppp = 0, ppp = 0;
        w = m = n = 0, Flag = false;
        top = lim = ll = 0;
        rep(i, 1000) re[i * (i - 1) / 2] = i;
        w = read(), m = read(), n = read();
        rep(i, w + n) {
            A[i].k = read();
            A[i].b = read();
        }
        sort(A + 1, A + 1 + w + n);
        check();
        rep(i, n + w) rep(j, i - 1) if (A[i].k != A[j].k) {
            int k1 = A[i].k, b1 = A[i].b;
            int k2 = A[j].k, b2 = A[j].b;
            // k1x+b1=k2x+b2  (k1-k2)x=b2-b1
            ++top;
            sta[top].x.a = b2 - b1;
            sta[top].x.b = k1 - k2;
            sta[top].x.re();
            sta[top].y = sta[top].x;
            sta[top].y.mul(k1);
            sta[top].y.add(b1);
            sta[top].y.re();
        }
        sort(sta + 1, sta + 1 + top);
        int l = 1, r, cnt = 0;
        while (l <= top) {
            r = l;
            while (r < top && sta[r + 1] == sta[l])
                r++;

            assert(re[r - l + 1]);
            if (re[r - l + 1] & 1) {
                B[++lim] = sta[l];
            } else
                C[++ll] = sta[l];
            cnt++;
            l = r + 1;
        }
        //给的直线全部平行，无法构成交点
        if (n == 2 * m) {
            puts(cnt % 2 ? "Bob" : "Alice");
            return 0;
        }
        if (w % 2 == 0) {
            puts("Bob");
            return 0;
        }
        if (n == 2 * m - 1) {
            puts((lim || ok) || (cnt & 1) ? "Bob" : "Alice");
            return 0;
        }
        if (qweqwe > 1) {
            puts("Bob");
            return 0;
        }
        if (2 * m - n <= 4 && 2 * m - n >= 3) {
            puts(cnt ? "Bob" : "Alice");
            return 0;
        }  //可能没有交点，a只能选择平行
        if (2 * m - n > 2) {
            puts("Bob");
            return 0;
        }
        if (!lim) {
            puts(cnt % 2 ? "Bob" : "Alice");
            return 0;
        }
        assert(qweqwe == 1);
        vector<int> bb;
        rep(i, lim) {
            INT X = B[i].x;
            X.mul(ok);
            X = B[i].y - X;
            if (X.b != 1) {
                puts("Bob");
                return 0;
            }
            bb.push_back(X.a);
        }
        sort(bb.begin(), bb.end());
        For(i, 0, (int)bb.size() - 1) if (bb[i] != bb[0]) {
            puts("Bob");
            return 0;
        }
        if (mp[bb[0]]) {
            puts("Bob");
            return 0;
        }
        rep(i, ll) {
            INT X = C[i].x;
            X.mul(ok);
            X = C[i].y - X;
            if (X.b != 1)
                continue;
            if (X.a == bb[0]) {
                puts("Bob");
                return 0;
            }
        }
        cnt %= 2;
        puts(((cnt) ^ (lim & 1)) ? "Bob" : "Alice");
        return 0;
    };
    int T = read();
    while (T--) {
        solve();
    }
    return 0;
}
