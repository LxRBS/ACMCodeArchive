#include "testlib.h"
#include <numeric>

using namespace std;

const int MAXN = 5000;
const int MAXV = 5000;

int main(int argc, char** argv) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, MAXN, "n");
    inf.readEoln();
    vector<int> a = inf.readInts(n, 1, MAXV, "a");
    inf.readEoln();
    int sum = accumulate(a.begin(), a.end(), 0);
    inf.readInt(0, sum, "b"); 
    inf.readEoln();
    inf.readEof();

    return 0;
}
