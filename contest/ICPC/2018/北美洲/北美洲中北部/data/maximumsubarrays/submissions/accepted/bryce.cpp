#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

typedef long long ll;
typedef vector<ll> vi;
typedef vector<vi> vvi;

static const ll INF = 0xffffffffll * 100000ll;

int main() {
    ll n, k;
    cin >> n >> k;
    vi A(n);
    for (ll i = 0; i < n; ++i) {
        cin >> A[i];
    }

    vvi Best(n, vi(k+1, -INF));
    vvi BestInclude(n, vi(k+1, -INF));

    for (ll i = 0; i < n; ++i) {
        Best[i][0] = 0;
    }
    Best[0][1] = BestInclude[0][1] = A[0];

    for (ll i = 1; i < n; ++i) {
        for (ll j = 1; j <= k; ++j) {
            BestInclude[i][j] = max(BestInclude[i-1][j], Best[i-1][j-1]) + A[i];
            Best[i][j] = max(Best[i-1][j], BestInclude[i][j]);
        }
    }

    cout << Best[n-1][k] << endl;
}
