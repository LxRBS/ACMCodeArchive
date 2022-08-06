#include <bits/stdc++.h>
using namespace std;
struct frac {
    long long a;
    long long b;
    frac() {
        a = 0;
        b = 1;
    }
    frac(long long _a, long long _b) {
        // assert(_b <= 0x7fffffff);
        assert(_b != 0);
        a = _a;
        b = _b;
    }
    bool operator<(const frac& T) const {
        assert(is_product_not_overflow(a, T.b));
        assert(is_product_not_overflow(b, T.a));
        return a * T.b < b * T.a;
    }
    frac operator+(const frac& T) const {
        assert(is_product_not_overflow(a, T.b));
        assert(is_product_not_overflow(b, T.a));
        assert(is_product_not_overflow(b, T.b));
        assert(is_plus_not_overflow(a * T.b, b * T.a));
        long long tmp_a = a * T.b + b * T.a;
        long long tmp_b = b * T.b;
        long long tmp_g = gcd(tmp_a, tmp_b);
        return frac(tmp_a / tmp_g, tmp_b / tmp_g);
    }
private:
    static long long gcd(long long a, long long b) {
        if (a % b == 0) {
            return b;
        }
        return gcd(b, a % b);
    }
    static bool is_product_not_overflow(long long a, long long b) {
        if (a == 0) {
            return true;
        }
        long long product = a * b;
        return product / a == b;
    }
    static bool is_plus_not_overflow(long long a, long long b) {
        long long product = a + b;
        return product - a == b;
    }
};
inline int read()
{
    int w = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9')
    {
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
    {
        w = (w << 3) + (w << 1) + ch - 48;
        ch = getchar();
    }
    return w * f;
}
int n, m;
frac dp[3010][3010][2];
signed main()
{
    n = read();
    m = read();
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= i; j++)
        {
            int a = read();
            int b = read();
            dp[i][j][0] = frac(a, b);
        }
    }
    int cur = 1;
    int nxt = 2;
    bool flag = false;
    while (true)
    {
        nxt = min(nxt, m);
        if (nxt >= m)
        {
            nxt = m;
            flag = true;
        }
        int d = nxt - cur;
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= i; j++)
            {
                dp[i][j][1] = dp[i][j][0];
                if (i - d >= 1)
                    dp[i][j][1] = max(dp[i][j][1], dp[i - d][j][0]);
                if (j + d <= i)
                    dp[i][j][1] = max(dp[i][j][1], dp[i][j + d][0]);
            }
        }
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= i; j++)
            {
                dp[i][j][0] = dp[i][j][1];
            }
        }
        cur = nxt;
        nxt = 1.5 * cur;
        if (flag)
            break;
    }
    frac ans(0, 1);
    for (int i = m; i <= n; i++)
    {
        for (int j = 1; j <= i - m + 1; j++)
        {
            ans = ans + dp[i][j][0];
        }
    }
    cout << ans.a  << "/" << ans.b << endl;
    return 0;
}