#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    setName("Validator for Is It Rated?");
    registerValidation(argc, argv);
    int n = inf.readInt(1, 1000, "n");
    inf.readSpace();
    int m = inf.readInt(1, 10000, "m");
    inf.readEoln();

    string pattern = format("[01]{%d}", n);
    
    for (int i = 0; i < m; i++) {
        setTestCase(i);
        inf.readToken(pattern, "guesses");
        inf.readSpace();
        inf.readInt(0, 1, "answer");
        inf.readEoln();
    }
    unsetTestCase();

    inf.readEof();
}