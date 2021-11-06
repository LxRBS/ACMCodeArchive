#include "testlib.h"
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

int main(int argc, char** argv) {
    registerGen(argc, argv, 1);
    int n = atoi(argv[1]);
    int x = atoi(argv[2]);
    int m = atoi(argv[3]);
    int y = atoi(argv[4]);
    int b = atoi(argv[5]);
    cout << n + m << endl;
    vector<int> a(n + m);
    int s = 0;
    for (int i = 0; i < n; i++) {
        a[i] = x;
        s += a[i];
    }
    for (int i = n; i < n + m; i++) {
        a[i] = y;
        s += a[i];
    }
    for (int i = 0; i < a.size(); i++) {
        if (i > 0) cout << " ";
        cout << a[i];
    }
    cout << endl;
    b = b * s / 100;
    cout << b << endl;
    return 0;
}
