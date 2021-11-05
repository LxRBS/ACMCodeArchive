//Solution by lukasP (Lukáš Poláček)
//Complexity O(n)
//Tries to guess a point that lies on a line 30 times. Probability of failing is less than 0.2%
#include <iostream>
#include <vector>
#include <unordered_map>
#include <map>
#include <algorithm>
#include <cstdio>
using namespace std;

#define rep(i,a,b) for(__typeof(b) i=a; i<(b); ++i)

typedef pair<int, int> pii;
typedef long long ll;
int main()
{
    int n, p;
    scanf("%d %d", &n, &p);
    int needed = (n * p - 1) / 100;
    if (needed <= 1)
    {
        cout << "possible" << endl;
        return 0;
    }

    vector<pii> a(n);
    rep(i,0,n)
        scanf("%d %d", &a[i].first, &a[i].second);

    int iterations = 6 * 100 / p;
    rep(iter,0,iterations)
    {
        int q = rand() % n;
        unordered_map<ll, int> cnt;

        rep(i,0,n) if (i != q)
        {
            int x = a[i].first - a[q].first, y = a[i].second - a[q].second;
            int d = __gcd(x, y);
            x /= d; y /= d;

            if (++cnt[(ll(x) << 31) + y] >= needed)
            {
                cout << "possible" << endl;
                return 0;
            }
        }
    }

    cout << "impossible" << endl;
}
