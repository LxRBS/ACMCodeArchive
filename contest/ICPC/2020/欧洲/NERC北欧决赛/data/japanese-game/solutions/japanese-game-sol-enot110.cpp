/**
 *    author:  [itmo] enot110
 *    created: 21.03.2021 14:05:56       
**/
#include <bits/stdc++.h>
 
#define F first
#define S second
#define pb push_back
#define forn(i, n) for(int i = 0 ; (i) < (n) ; ++i)
#define eprintf(...) fprintf(stderr, __VA_ARGS__),fflush(stderr)
#define sz(a) ((int)(a).size())
#define all(a) (a).begin(),a.end()
#define pw(x) (1LL<<(x))
 
using namespace std;
 
typedef long long ll;
typedef double dbl;
typedef vector<int> vi;
typedef pair<int, int> pi;
 
const int inf = 1.01e9;
const dbl eps = 1e-9;
 
/* --- main part --- */
 
const int N = 1e5 + 10;
 
char s[N];
int n;
 
int ok(int k, int x)
{
    //eprintf("OK %d %d\n", k, x);
    if (x < 0) return 0;
    if (x == 0) return 1;
    if (k == 0) return 0;
    if (x == 1) return 0;
    if (x % 2 == 0) return 1;
    return k >= 2;
}
 
vi res;
 
void make(int k, int x)
{
    //eprintf("MAKE %d %d   OK = %d\n", k, x, ok(k, x));
    if (x == 0) return;
    while (x > 3)
    {
        res.pb(1);
        x -= 2;
    }
    if (x == 2) res.pb(1);
    else if (x == 3) res.pb(2);
    else assert(0);
}
 
void go(int k)
{
    int mn = inf;
    int mx = -inf;
    forn(i, n) if (s[i] == '#')
    {
        mn = min(mn, i);
        mx = max(mx, i);
    }
    if (mn == inf)
    {
        if (n == 1)
        {
            printf("-1\n");
            exit(0);
        }
        else
        {
            printf("1\n1\n");
            exit(0);
        }
    }
    if (!ok(k, mn - k)) return;
    if (!ok(k, n - mx - 1 - k)) return;
    int cur = 0;
    for (int i = mn; i <= mx; i++)
    {
        if (s[i] == '_') cur++;
        else
        {
            if (cur > 0)
            {
                if (!ok(k, cur - 1 - k)) return;
            }
            cur = 0;
        }
    }
    assert(cur == 0);
    make(k, mn - k);
    int cur0 = 0, cur1 = 0;
    for (int i = mn; i <= mx; i++)
    {
        if (s[i] == '_')
        {
            cur0++;
            if (cur1 > 0)
            {
                res.pb(cur1 + k);
                cur1 = 0;
            }     
        }
        else
        {
            cur1++;
            if (cur0 > 0)
            {
                make(k, cur0 - 1 - k);
                cur0 = 0;
            }
        }
    }
    //eprintf("OK k=%d\n", k);
    assert(cur1 > 0);
    res.pb(cur1 + k);
    make(k, n - mx - 1 - k);
    printf("%d\n", sz(res));
    forn(i, sz(res)) printf("%d%c", res[i], " \n"[i + 1 == sz(res)]);
    exit(0);
}
         
 
int main()
{
    #ifdef HOME
        assert(freopen("1.in", "r", stdin));
        assert(freopen("1.out", "w", stdout));
    #endif
    scanf("%s", s);
    n = strlen(s);
    vi v;
 
    go(0);
    go(1);
    go(2);
    go(3);    
    printf("-1\n");
    #ifdef HOME
        eprintf("time = %d ms\n", (int)(clock() * 1000. / CLOCKS_PER_SEC));
    #endif
    return 0;
}
