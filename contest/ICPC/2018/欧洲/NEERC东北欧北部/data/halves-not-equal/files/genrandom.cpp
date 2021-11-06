#include "testlib.h"
#include <iostream>
#include <vector>
using namespace std;

int main(int argc, char** argv) {
    registerGen(argc, argv, 1);
    int n = atoi(argv[1]);
    int v = atoi(argv[2]);
    cout << n << endl;
    vector<int> a(n);
    int s = 0;
    for (int i = 0; i < n; i++) {
        a[i] = rnd.next(1, v);
        s += a[i];
    }
    for (int i = 0; i < n; i++) {
        if (i > 0) cout << " ";
        cout << a[i];
    }
    cout << endl;
    int b = rnd.next(0, s);
    cout << b << endl;
    return 0;
}
