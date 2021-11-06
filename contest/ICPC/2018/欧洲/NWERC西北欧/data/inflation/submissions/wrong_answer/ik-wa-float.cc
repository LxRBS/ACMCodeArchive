#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;

    cin >> n;

    vector<int> canisters(n);

    for (int i = 0; i < n; ++i) {
        cin >> canisters[i];
    }

    sort(canisters.begin(), canisters.end());

    float v = 1.0;
    for (int i = 0; i < n; ++i) {
        if (canisters[i] > i+1) {
            cout << "impossible" << endl;
            return 0;
        } else {
            v = v < canisters[i]/(i+1) ? v : canisters[i]/(i+1);
        }
    }

    cout << v << endl;
    return 0;
}
