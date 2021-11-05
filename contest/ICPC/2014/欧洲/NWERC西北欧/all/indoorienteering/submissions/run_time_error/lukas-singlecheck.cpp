//Solution by lukasP (Lukáš Poláček)
//Meet in the middle with some optimizations
//I store the relevant subsets and permutations, so that I don't have to regenerate them all the
//time.
#include <iostream>
#include <vector>
#include <set>
#include <unordered_map>
#include <algorithm>
#include <bitset>
#include <cstdio>
#include <cassert>
using namespace std;

#define rep(i,a,b) for(__typeof(b) i=a; i<(b); ++i)

typedef vector<int> vi;
typedef long long ll;
int main()
{
    int n; ll l;
    cin >> n >> l;

    ll d[n][n];
    rep(i,0,n)
        rep(j,0,n)
            scanf("%lld", &d[i][j]);

    vector<bitset<13> > subsets;
    int s = 1 << (n - 2);
    rep(i,0,s)
    {
        bitset<13> b(i);
        if ((int)b.count() == (n - 1) / 2)
            subsets.push_back(b);
    }

    int solutions = 0;
    vector<vi> perm[2];
    rep(k,0,2)
    {
        vi p((n - 2 + k) / 2);
        rep(i,0,p.size())
            p[i] = i;

        do {
            perm[k].push_back(p);
        } while (next_permutation(p.begin(), p.end()));
    }

    rep(mid,1,n)
    {
        vi cand;
        rep(i,1,n) if (i != mid)
            cand.push_back(i);

        for (bitset<13> b : subsets)
        {
            vi part[2];
            rep(j,0,cand.size())
                part[b[j]].push_back(cand[j]);

            set<ll> can;
            rep(k,0,2)
                for (vi& p : perm[k])
            {
                int first = 0, last = mid;
                if (k) swap(first, last);

                ll len = 0;
                rep(i,0,part[k].size())
                {
                    int v = part[k][p[i]];
                    len += d[first][v];
                    first = v;
                }
                len += d[first][last];

                if (k)
                {
                    if (can.count(l - len) && ++solutions == 1)
                        cout << "possible" << endl;
                }
                else if (len <= l)
                    can.insert(len);
            }
        }
    }

    if (solutions == 0)
        cout << "impossible" << endl;
    else
    {
        // want to trigger assert if there is only one solution
        assert(solutions > 2);
    }
}
