#include <iostream>
#include <vector>
#include <cstdlib>

using namespace std;

typedef long long ll;
typedef vector<ll> vi;

int main() {
    ll n = 500;
    ll k = 28;

    cout << n << " " << k << endl;
    for (ll i = 0; i < n-1; ++i) {
        if (rand() % 5 != 0) {
            cout << rand() % 1000000000 - 1000000000 << " ";
        }
        else {
            cout << rand() % 1000000000 << " ";
        }
        //cout << 1000000000LL << " ";
        //cout << rand() % 1000000000LL - 10000LL << " ";
    }
    //cout << rand() % 1000000000LL - 10000LL << " ";
    cout << rand() % 100000LL - 1000000LL << endl;
}
