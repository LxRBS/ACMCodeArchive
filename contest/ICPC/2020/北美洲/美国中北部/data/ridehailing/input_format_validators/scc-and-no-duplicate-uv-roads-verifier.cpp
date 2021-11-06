// The checktestdata verifier verifies input format but does not check both:
//  1. That the graph is strongly connected.
//  2. That there is at most one road in one direction between any two locations u and v.
// This c++ program handles these two requirements.

#include <iostream>
#include <vector>

#define INF 100000000

using namespace std;

typedef long long ll;
typedef vector<ll> vi;
typedef vector<vi> vvi;

int main() {
    ll n, m, k;
    cin >> n >> m >> k;

    vvi dist(n, vi(n, INF));
    for (ll i = 0; i < m; ++i) {
        ll u, v, w;
        cin >> u >> v >> w;
        --u;
        --v;
        if (dist[u][v] != INF) {    // there is more than one u-v road in the input
            return 2;
        }
        dist[u][v] = w;
    }

    for (ll k = 0; k < n; ++k) {
        for (ll i = 0; i < n; ++i) {
            for (ll j = 0; j < n; ++j) {
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }

    for (ll i = 0; i < n; ++i) {
        for (ll j = 0; j < n; ++j) {
            if (dist[i][j] == INF) {        // the graph is not strongly-connected
                return 1;
            }
        }
    }

    return 42;  // both 1 and 2 are satisfied
}
