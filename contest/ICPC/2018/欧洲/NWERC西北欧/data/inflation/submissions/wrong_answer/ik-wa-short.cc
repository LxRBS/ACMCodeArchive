#include <bits/stdc++.h>
using namespace std;

int main() {
    short n;
    cin >> n;

    vector<short> canisters(n);

    for (short i = 0; i < n; ++i) {
        cin >> canisters[i];
    }

    sort(canisters.begin(), canisters.end());

    float v = 1.0;
    for (short i = 0; i < n; ++i) {
        if (canisters[i] > i+1) {
            cout << "impossible" << endl;
            return 0;
        } else {
            v = min(v, float(canisters[i])/(i+1));
        }
    }

    cout << v << endl;
    return 0;
}
