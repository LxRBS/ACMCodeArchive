#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;

struct Wife {
    int a;
    double c;
    int i;
};

int main() {
    int n;
    cin >> n;
    vector<Wife> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i].a;
        a[i].i = i;
    }
    double b;
    cin >> b;

    double suma = accumulate(a.begin(), a.end(), 0, [](double s, Wife& a){ return s + a.a; });
    bool neg = false;
    if (b * 2 > suma) {
        b = suma - b;
        neg = true;
    }

    sort(a.begin(), a.end(), [](Wife& a, Wife& b) { return a.a < b.a; });

    for (int i = 0; i < n; i++) {
        double d;
        if (b < (a[i].a / 2.0 - a[i].c) * (n - i)) {
            double d = b / (n - i);
            for (int j = i; j < n; j++) {
                a[j].c += d;
            }
            break;
        } else {
            double d = a[i].a / 2.0 - a[i].c;
            for (int j = i; j < n; j++) {
                a[j].c += d;
            }
            b -= d * (n - i);
        }
    }

    sort(a.begin(), a.end(), [](Wife& a, Wife& b) { return a.i < b.i; });

    if (neg) {
        for (int i = 0; i < n; i++) {
            a[i].c = a[i].a - a[i].c;
        }
    }

    cout.precision(15);
    for (int i = 0; i < n; i++) {
        cout << a[i].c << endl;
    }

    return 0;
}
