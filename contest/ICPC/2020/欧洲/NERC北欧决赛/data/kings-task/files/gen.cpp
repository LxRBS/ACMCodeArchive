#include "testlib.h"
#include <iostream>

using namespace std;

int main(int argc, char *argv[]) {
    registerGen(argc, argv, 1);

    int n = atoi(argv[1]);
    int m = atoi(argv[2]);
    int bg = atoi(argv[3]);

    n *= 2;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        a[i] = i + 1;
    }
    for (int i = 0; i < m; i++) {
        if (i % 2) {
            for (int j = 0; j < n / 2; j++) {
                swap(a[2 * j], a[2 * j + 1]);
            }
        } else {
            for (int j = 0; j < n / 2; j++) {
                swap(a[j], a[j + n / 2]);
            }
        }
    }
    if (bg == 1) {
        int i = rnd.next(n);
        int j = rnd.next(n);
        swap(a[i], a[j]);
    } else if (bg == 2) {
        int i = rnd.next(n - 1);
        int j = i + 1;
        swap(a[i], a[j]);
    } else if (bg == 3) {
        int i = rnd.next(n / 2);
        int j = i + n / 2;
        swap(a[i], a[j]);
    }

    cout << n / 2 << "\n";
    for (int i = 0; i < n; i++) {
        cout << a[i] << " \n"[i == n - 1];
    }
}