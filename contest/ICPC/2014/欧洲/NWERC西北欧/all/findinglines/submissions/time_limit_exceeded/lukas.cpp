//Solution by lukasP (Lukáš Poláček)
//Complexity O(n log n)
//Tries to guess a point that lies on a line 20 times. Probability of failing is less than 1e-15
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

    int iterations = 60 * 100 / p + 1;
    rep(iter,0,iterations)
    {
        int q = rand() % n;
        map<pii, int> cnt;

        rep(i,0,n) if (i != q)
        {
            pii w(a[i].first - a[q].first, a[i].second - a[q].second);
            int d = __gcd(w.first, w.second);
            w.first /= d;
            w.second /= d;

            if (++cnt[w] >= needed)
            {
                cout << "possible" << endl;
                return 0;
            }
        }

    }

    cout << "impossible" << endl;
}
