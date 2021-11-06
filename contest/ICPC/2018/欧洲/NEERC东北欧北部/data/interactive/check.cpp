#include "testlib.h"

using namespace std;

const int MAGIC = 998244352; // nobody will guess it!

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int val = ouf.readInt();
    if (val == MAGIC) {
        quitf(_ok, "ok");
    } else {
        quitf(_wa, "strange: magic differs. Expected %d, found %d", MAGIC, val);
    }
}