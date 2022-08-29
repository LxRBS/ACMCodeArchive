#include "testlib.h"
using namespace std;
using LL = long long;
int main(int argc, char** argv) {
    registerTestlibCmd(argc, argv);
    int T = inf.readInt();
    for (int ti = 1; ti <= T; ti += 1) {
        int k = inf.readInt(1, 100'000, "k"), n = inf.readInt(1, 100'000, "k"), m = inf.readInt(0, min(100'000LL, (LL) n * (n - 1) / 2), "m");
        for (int i = 0; i < m; i += 1){
            inf.readToken();
            inf.readToken();
        }

        for (int i = 1; i < k; i += 1){
            inf.readToken();
            inf.readToken();
            inf.readToken();
            inf.readToken();
        }
        auto readAndCheckAnswer = [&] (InStream& in) {
            set<set<int>> s;
            set<int> t;
            int r = in.readInt(1, k, "r");
            for (int i = 0; i < r; i += 1) {
                int x = in.readInt(1, k, "x");
                set<int> ss;
                for (int j = 0; j < x; j += 1) {
                    int y = in.readInt(1, k, "y");
                    if (t.count(y)) quitf(_pe, "repeated graphs");
                    ss.insert(y);
                    t.insert(y);
                }
                s.insert(ss);
            }
            return s;
        };
        auto anss = readAndCheckAnswer(ans);
        auto oufs = readAndCheckAnswer(ouf);
        if (anss != oufs)
            quitf(_wa, "the participant dose not equal to answer");
    }
    quitf(_ok, "%d test cases", T);
}
