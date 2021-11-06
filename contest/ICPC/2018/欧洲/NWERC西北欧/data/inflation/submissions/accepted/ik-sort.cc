#include <bits/stdc++.h>
using namespace std;

int main() {
    long n;
    
    cin >> n;
    
    vector<long> canisters(n);
    
    for (long i = 0; i < n; ++i) {
        cin >> canisters[i];
    }
    
    sort(canisters.begin(), canisters.end());
    
    float v = 1.0;
    for (long i = 0; i < n; ++i) {
        if (canisters[i] > i+1) {
            cout << "impossible" << endl;
            return 0;
        } else {
            v = v < float(canisters[i])/(i+1) ? v : float(canisters[i])/(i+1);
        }
    }
    
    cout << v << endl;
    return 0;
}
