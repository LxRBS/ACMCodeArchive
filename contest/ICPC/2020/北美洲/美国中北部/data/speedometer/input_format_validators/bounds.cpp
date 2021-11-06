// handles input bounds not captured by format.ctd REGEX

#include <iostream>

using namespace std;

typedef long long ll;

int main() {
    double tf, tr;
    cin >> tf >> tr;
    if (tf >= tr)   // first bound captured by format.ctd regex
        return 1;
    double speed;
    while (cin >> speed) {
        if (speed < 0 || speed > 120) {
            return 2;
        }
    }
    return 42;
}
