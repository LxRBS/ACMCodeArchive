#include "testlib.h"
#include <iostream>

using namespace std;

int main(int argc, char *argv[]) {
    registerGen(argc, argv, 1);

    int n = atoi(argv[1]);
    int d = atoi(argv[2]);
    int mx = atoi(argv[3]);
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        a[i] = rnd.next(1, mx);
    }
    cout << n << " " << d << "\n";
    for (int i = 0; i < n; i++) {
        cout << a[i] << " \n"[i == n - 1];
    }
}