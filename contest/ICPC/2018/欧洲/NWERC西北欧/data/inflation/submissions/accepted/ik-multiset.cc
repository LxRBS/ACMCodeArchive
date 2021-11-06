#include <bits/stdc++.h>
using namespace std;

int main() {
    long n;
    cin >> n;
    multiset<long> canisters;
    long size;
    for (long i = 0; i < n; ++i) {
        cin >> size;
        canisters.insert(size);
    }

    float v = 1.0;
    for (long i = 1; i <= n; ++i) {
        long min_canister = *canisters.begin();
        canisters.erase(canisters.begin());

        if (min_canister > i) {
            cout << "impossible" << endl;
            return 0;
        } else {
            v = v < float(min_canister)/i ? v : float(min_canister)/i;
        }
    }

    cout << v << endl;
    return 0;
}
