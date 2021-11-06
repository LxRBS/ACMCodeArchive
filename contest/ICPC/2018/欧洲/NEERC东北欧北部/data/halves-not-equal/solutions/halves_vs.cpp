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
 
const int N = 5010;
 
int n;
int s;
 
int a[N];
dbl r[N];
dbl rr[N];
pi b[N];
int c[N], cc = 0;
 
dbl add[N][N];
 
pi q[N];
int qq = 0;
 
void gen() {
    /*add[0][0] = add[1][0] = add[2][0] = 1. / 3;
    add[0][1] = 1. / 6;
    add[1][1] = add[2][1] = 5. / 12;
    add[1][2] = 1. / 4;
    add[2][2] = 3. / 4;
    add[0][3] = add[1][3] = add[2][3] = 1. / 3;
 
    b[n] = {inf, 0};
    forn(i, n) b[i] = {a[i], i};
    sort(b, b + n);
    cc = 0;
    c[cc++] = 0;
    forn(i, n) c[cc++] = b[i].F;
    c[cc++] = inf;
 
    forn(i, n) {
        r[b[i].S] = 0;
        forn(j, n + 2) {
            int z = min(s - c[j], c[j + 1] - c[j]);
            if (z < 0) break;
            dbl ADD = add[i][j];
            eprintf("i = %d, j = %d, add = %.4lf, z = %d\n", i, j, ADD, z);
            r[b[i].S] += z * ADD;
        }
    }*/
    forn(i, n) b[i] = {a[i], i};
    sort(b, b + n);
 
    qq = 0;
    forn(i, n) forn(j, i) q[qq++] = {i, j};
    random_shuffle(q, q + qq);
 
    forn(i, n) r[i] = s * 1. / n;
    forn(_, 10) {
        forn(ii, qq) {
            int i = q[ii].F;
            int j = q[ii].S;
 
            dbl z = r[i] + r[j];
            dbl x1, x2;
            if (z <= b[j].F) {
                x1 = z * 0.5;
                x2 = z * 0.5;
            } else if (z <= b[i].F) {
                x1 = b[j].F * 0.5;
                x2 = z - b[j].F * 0.5;
            } else {
                x1 = b[j].F * 0.5 + (z - b[i].F) * 0.5;
                x2 = b[i].F * 0.5 + (z - b[j].F) * 0.5;
            }
            r[i] = x2;
            r[j] = x1;
        }
    }
    forn(i, n) rr[b[i].S] = r[i];
    forn(i, n) r[i] = rr[i];
 
}
 
void check(int a1, int a2, dbl c1, dbl c2, int i, int j) {
    if (a1 > a2) swap(a1, a2), swap(c1, c2), swap(i, j);
    dbl z = c1 + c2;
    dbl x1, x2;
    if (z <= a1) {
        x1 = z * 0.5;
        x2 = z * 0.5;
    } else if (z <= a2) {
        x1 = a1 * 0.5;
        x2 = z - a1 * 0.5;
    } else {
        x1 = a1 * 0.5 + (z - a2) * 0.5;
        x2 = (z - a1) * 0.5 + a2 * 0.5;
    }
    if (abs(x1 - c1) + abs(x2 - c2) > 1e-9) {
        eprintf("error %d %d :: %d %d -> %.4lf %.4lf instead %.4lf %.4lf\n", i, j, a1, a2, c1, c2, x1, x2);
        exit(0);
    }
}
 
void check() {
    forn(i, n) forn(j, i) check(a[i], a[j], r[i], r[j], i, j);
}
 
 
void out() {
    forn(i, n) printf("%.10f\n", r[i]);
}
 
int main()
{
    #ifdef HOME
        assert(freopen("in", "r", stdin));
        assert(freopen("out", "w", stdout));
    #endif
    if (1) {
        scanf("%d", &n);
        forn(i, n) scanf("%d", &a[i]);
        scanf("%d", &s);
        gen();
        out();
    } else {
        for (int tt = 0; tt < 10000; ++tt) {
            eprintf("tt = %d\n", tt);
            srand(tt);
 
            n = 100;//rand() % 10 + 1;
            forn(i, n) a[i] = rand() % 20 + 1;
            int x = 0;
            forn(i, n) x += a[i];
            s = rand() % (x + 1);
            //n = 3;
            //s = 11;
            //a[0] = 10, a[1] = 20, a[2] = 30;
 
            eprintf("n = %d, s = %d\n", n, s);
            forn(i, n) eprintf("%d%c", a[i], " \n"[i + 1 == n]);
 
            gen();
            check();
        }
    }
    #ifdef HOME
        eprintf("time = %d ms\n", (int)(clock() * 1000. / CLOCKS_PER_SEC));
    #endif
    return 0;
}
