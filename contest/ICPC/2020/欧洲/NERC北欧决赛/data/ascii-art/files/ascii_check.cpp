#include "testlib.h"
#include <string>

using namespace std;

int main(int argc, char * argv[]) {
    registerTestlibCmd(argc, argv);
    int h = ans.readInt();
    int w = ans.readInt();
    int ph = ouf.readInt();
    int pw = ouf.readInt();
    if (ph != h || pw != w)
        quitf(_wa, "expected: %d %d, found: %d %d", h, w, ph, pw);
    ans.readEoln();
    ouf.readEoln();
    string strAnswer;
    for (int r = 1; r <= h; r++) {
      string j = ans.readString();
      string p = ouf.readString();
      if (j != p)
        quitf(_wa, "row %d expected: '%s', found: '%s'", r, j.c_str(), p.c_str());
    }
    quitf(_ok, "%d %d", h, w);
}
