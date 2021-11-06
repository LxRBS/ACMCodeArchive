#include <iostream>
#include <vector>
#include <cstdlib>

using namespace std;

typedef long long ll;
typedef vector<ll> vi;

int main() {
    ll N = 40;
    ll M = 1100;
    ll k1 = 28;
    ll k2 = 28;

    cout << N << " " << M << " " << k1 << " " << k2 << endl;
    ll S = 1;
    ll T = 1;
    for (ll i = 2; i <= N; ++i) {
        for (ll C = 0; C <= 2; ++C) {
            cout << 1 << " " << i << " " << rand()%1000000000 << " " << C << endl;
            --M;
        }
    }
    while (true) {
        ll k = rand()%N + 1;
        for (ll i = 1; i <= N; ++i) {
            if (i == k) continue;
            for (ll C = 0; C <= 2; ++C) {
                cout << k << " " << i << " " << rand()%1000000000 << " " << C << endl;
                --M;
                if (M == 0)
                    goto END;
            }
        }
    }
END:
    cout << S << " " << T << endl;
}
