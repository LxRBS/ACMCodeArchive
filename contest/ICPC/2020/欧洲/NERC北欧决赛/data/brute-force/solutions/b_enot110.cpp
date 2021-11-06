/**
 *    author:  [itmo] enot110
 *    created: 21.03.2021 11:12:43       
**/
#include <bits/stdc++.h>
#include <bits/extc++.h>

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

template <typename T, typename C>

class mcmf {

  public:

  static constexpr T eps = (T) 1e-9;



  struct edge {

    int from;

    int to;

    T c;

    T f;

    C cost;

    char dig;

  };



  vector< vector<int> > g;

  vector<edge> edges;

  vector<C> d;

  vector<int> q;

  vector<bool> in_queue;

  vector<int> pe;

  int n;

  int st, fin;

  T flow;

  C cost;



  mcmf(int _n, int _st, int _fin) : n(_n), st(_st), fin(_fin) {

    assert(0 <= st && st < n && 0 <= fin && fin < n && st != fin);

    g.resize(n);

    d.resize(n);

    in_queue.resize(n);

    pe.resize(n);

    flow = 0;

    cost = 0;

  }



  void clear_flow() {

    for (const edge &e : edges) {

      e.f = 0;

    }

    flow = 0;

  }

   


  void add(int from, int to, T forward_cap, T backward_cap, C cost, char dig=0) {

    assert(0 <= from && from < n && 0 <= to && to < n);

    g[from].push_back((int) edges.size());

    edges.push_back({from, to, forward_cap, 0, cost, dig});

    g[to].push_back((int) edges.size());

    edges.push_back({to, from, backward_cap, 0, -cost, 0});

  }

    vector<char> ANS;

    bool go(int x)
    {
        //eprintf("go %d  %d %d\n", x, st, fin);
        if (x == fin)
        {
            return 1;
        }
        for (int e : g[x])
        {
            //eprintf("edge %d\n", e);
            if (e % 2 == 0)
            {
//                eprintf("edge   to=%d  f=%d  c=%d  cost=%d\n", edges[
                if (edges[e].f > 0)
                {
                    if (edges[e].dig)
                    {
                        //eprintf("ADD %c\n", edges[e].dig);
                        ANS.pb(edges[e].dig);
                    }
                    edges[e].f--;
                    edges[e ^ 1].f++;
                    bool val = go(edges[e].to);
                    assert(val == true);
                    return true;
                }
            }
        }
        return false;
    }
    
    void reconstruct()
    {
        while (go(st));
    }
  
    


  bool expath() {

    fill(d.begin(), d.end(), numeric_limits<C>::max());

    q.clear();

    q.push_back(st);

    d[st] = 0;

    in_queue[st] = true;

    int beg = 0;

    bool found = false;

    while (beg < (int) q.size()) {

      int i = q[beg++];

      if (i == fin) {

        found = true;

      }

      in_queue[i] = false;

      for (int id : g[i]) {

        const edge &e = edges[id];

        if (e.c - e.f > eps && d[i] + e.cost < d[e.to]) {

          d[e.to] = d[i] + e.cost;

          pe[e.to] = id;

          if (!in_queue[e.to]) {

            q.push_back(e.to);

            in_queue[e.to] = true;

          }

        }

      }

    }

    if (d[fin] > 0) return 0;
    if (found) {

      T push = numeric_limits<T>::max();

      int v = fin;

      while (v != st) {

        const edge &e = edges[pe[v]];

        push = min(push, e.c - e.f);

        v = e.from;

      }

      v = fin;

      while (v != st) {

        edge &e = edges[pe[v]];

        e.f += push;

        edge &back = edges[pe[v] ^ 1];

        back.f -= push;

        v = e.from;

      }

      flow += push;

      cost += push * d[fin];

    }

    return found;

  }

   

  pair<T, C> max_flow_min_cost() {

    while (expath()) {

    }

    //eprintf("%d %lld\n", flow, cost);
    return make_pair(flow, cost);

  }

};



mcmf<int, ll> *FLOW;

namespace flow
{
    void add(int x, int y, int f, int c, char dig=0)
    {
        FLOW->add(x, y, f, 0, c, dig);
    }

    int ST, EN;
    void setN(int n)
    {
        ST = n;
        EN = n + 1;
        n += 2;
        //eprintf("n = %d\n", n);
        FLOW = new mcmf<int, ll>(n, ST, EN);
    }

    void minCost()
    {
        FLOW->max_flow_min_cost();
    }        
}            




const int maxN = 1100;
int a[maxN];
int b[maxN];


int main()
{
    #ifdef HOME
        assert(freopen("1.in", "r", stdin));
        assert(freopen("1.out", "w", stdout));
    #endif
    int n, k;
    scanf("%d%d", &n, &k);
    forn(i, k)
    {
        char s[11];
        scanf("%s", s);
        int x = 0;
        forn(j, n) x = x * 2 + (s[j] - '0');
        a[x] = 1;
    }       
    int N = pw(n);
    flow::setN(2 * N);
    for (int i = 0; i < N; i++)
    {
        flow::add(2 * i, 2 * i + 1, inf, 0);
        if (a[i])
        {
            flow::add(2 * i, 2 * i + 1, 1, -100);
        }
    }
    for (int x = 0; x < N; x++)
    {
        forn(i, n) if ((x & pw(i)) == 0)
        {
            int y = x | pw(i);
            flow::add(2 * x + 1, 2 * y, inf, 1, '0' + (n - 1 - i));
        }
        flow::add(2 * x + 1, flow::EN, inf, 1, 'R');
    }
    //eprintf("!!\n");
    flow::add(flow::ST, 0, inf, 0);
    flow::minCost();
    //eprintf("!!\n");
    
    FLOW->reconstruct();
    //eprintf("!!\n");
    vector<char> ans = FLOW->ANS;
    //eprintf("!!  %d\n", sz(ans));
    assert(sz(ans));
    ans.pop_back();
    printf("%d\n", sz(ans));
    forn(i, sz(ans)) printf("%c%c", ans[i], " \n"[i + 1 == sz(ans)]);

    int cur = 0;
    forn(i, sz(ans))
    {
        if (ans[i] == 'R') cur = 0;
        else
        {
            int x = n - 1 - (ans[i] - '0');
            assert((cur & pw(x)) == 0);
            cur |= pw(x);
        }
        b[cur] = 1;
    }

    forn(i, N) if (a[i] && !b[i])
    {
        assert(0);
    } 

    
        
    #ifdef HOME
        eprintf("time = %d ms\n", (int)(clock() * 1000. / CLOCKS_PER_SEC));
    #endif
    return 0;
}
