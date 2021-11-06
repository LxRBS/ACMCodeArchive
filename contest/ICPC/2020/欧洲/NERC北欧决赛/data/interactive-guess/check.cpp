#include "testlib.h"
#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{
    setName("Checker for Is It Rated?");
    registerTestlibCmd(argc, argv);
    
    int n = inf.readInt();
    int m = inf.readInt();
    int errors = 0;
    vector<int> others(n);

    for (int i = 0; i < m; i++)
    {
        setTestCase(i);
        string s = inf.readToken();
        int a = inf.readInt();
        int o = ouf.readInt(0, 1);
        for (int j = 0; j < n; ++j) if (s[j] != '0' + a) {
          ++others[j];
        }
        if (a != o) {
          ++errors;
        }
    }
    unsetTestCase();
    int b = others[0];
    for (int x : others) b = min(x, b);
    int need = 13 * b / 10 + 100;
    if (errors <= need) {
       quitf(_ok, "%d errors, b = %d", errors, b);
    } else {
       quitf(_wa, "too many errors: %d, while b = %d", errors, b);
    }
}
