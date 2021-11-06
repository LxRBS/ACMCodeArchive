#include <iostream>
#include <vector>
#include <string>
#include <cmath>

#define EP 1e-18

using namespace std;

typedef long long ll;

int main() {
    string num;
    cin >> num;
    ll repeat;
    cin >> repeat;

    long double num_d;
    string repeat_segment = num.substr(num.size()-repeat);
    for (ll i = 0; i < 30; ++i) {
        num += repeat_segment;
    }
    num_d = stold(num);
    cerr.precision(25);
    //cerr << num << endl;
    //cerr << fixed << num_d << endl;

    ll n, d;
    for (n = 1; true; ++n) {
        d = n/num_d;
        if (abs((long double)n/d - num_d) < EP) {
            cout << n << "/" << d << endl;
            break;
        }
    }
}
