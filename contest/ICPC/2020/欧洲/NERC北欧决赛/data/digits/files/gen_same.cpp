#include "testlib.h"
#include <iostream>

using namespace std;

int main(int argc, char *argv[]) {
    registerGen(argc, argv, 1);

    int n = atoi(argv[1]);
    int x = atoi(argv[2]);
    int p = atoi(argv[3]);
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        a[i] = x;
    }
    int d = 1;
    for (int i = 0; i < n - p; i++) {
        d = (d * a[i]) % 10;
    }
    cout << n << " " << d << "\n";
    for (int i = 0; i < n; i++) {
        cout << a[i] << " \n"[i == n - 1];
    }
}