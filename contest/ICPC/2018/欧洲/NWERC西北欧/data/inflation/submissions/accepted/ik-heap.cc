#include <bits/stdc++.h>
using namespace std;

int main() {
    long n;
    cin >> n;
    vector<long> canisters(n);
    long size;
    for (long i = 0; i < n; ++i) {
        cin >> canisters[i];
    }
    make_heap(canisters.begin(), canisters.end());

    float v = 1.0;
    for (long i = n; i > 0; --i) {
        pop_heap(canisters.begin(), canisters.end());
        long max_canister = canisters.back();
        canisters.pop_back();

        if (max_canister > i) {
            cout << "impossible" << endl;
            return 0;
        } else {
            v = v < float(max_canister)/i ? v : float(max_canister)/i;
        }
    }

    cout << v << endl;
    return 0;
}
