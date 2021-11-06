#include "testlib.h"
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

int main(int argc, char** argv) {
    registerGen(argc, argv, 1);
    int n = atoi(argv[1]);
    int b = atoi(argv[2]);
    cout << n << endl;
    vector<int> a(n);
    int s = 0;
    for (int i = 0; i < n; i++) {
        a[i] = i + 1;
        s += a[i];
    }
    for (int i = 0; i < n; i++) {
        if (i > 0) cout << " ";
        cout << a[i];
    }
    cout << endl;
    b = b * s / 100;
    cout << b << endl;
    return 0;
}
