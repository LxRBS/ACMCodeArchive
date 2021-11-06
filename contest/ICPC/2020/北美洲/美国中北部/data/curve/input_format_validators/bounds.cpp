#include <iostream>

using namespace std;

typedef long long ll;

int main() {
    ll R; double S;
    while (cin >> R >> S) {
        if (R <= 99 || R >= 5281)
            return 1;   // R out of bounds
        if (S <= .009 || S >= 1)
            return 2;   // S out of bounds
    }
    return 42;
}
