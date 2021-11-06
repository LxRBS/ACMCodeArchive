#include "testlib.h"

using namespace std;

int main(int argc, char* argv[])
{
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "n");
    inf.readSpace();
    inf.readInt(1, 1000000000, "c");
    inf.readEoln();
    for (int i = 0; i < n; i++) {
        inf.readInt(1, 1000000000, "a");
        inf.readSpace();
        inf.readInt(1, 1000000000, "b");
        inf.readSpace();
        inf.readInt(0, 1, "s");
        inf.readEoln();
    }
    inf.readEof();
}