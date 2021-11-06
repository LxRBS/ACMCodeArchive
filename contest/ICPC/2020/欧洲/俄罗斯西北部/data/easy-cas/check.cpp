#include "testlib.h"

struct Cas {
    int a, b, s;

    Cas(int a, int b, int s) : a(a), b(b), s(s)
    { }
};


int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);
    int n = inf.readInt();
    int C = inf.readInt();
    std::vector<Cas> cases;
    for (int i = 0; i < n; i++) {
        int a = inf.readInt();
        int b = inf.readInt();
        int s = inf.readInt();
        cases.push_back(Cas(a, b, s));
    }
    std::string corr = upperCase(ans.readWord());
    std::string answer = upperCase(ouf.readWord());
    if (answer != "YES" && answer != "NO") {
        quit(_wa, "Yes or No expected.");
    }
    if (answer == "NO") {
        if (corr == "NO") {
            quit(_ok, "No is correct answer");
        } else {
            quit(_wa, "Order exists, but not found");
        }
    }

    std::set<int> used;
    for (int i = 0; i < n; i++) {
        int index = ouf.readInt(1, n);
        if (used.count(index)) {
            quit(_wa, format("CAS number %d used twice.", index));
        }
        used.insert(index);
        Cas cas = cases[index - 1];
        if (cas.a == C) {
            if (cas.s == 0) {
                quit(_wa, format("Cas %d succeeded, but it shouldn't. Current value is %d, CAS a is %d", index, C, cas.a));
            }
            C = cas.b;
        } else {
            if (cas.s == 1) {
                quit(_wa, format("Cas %d failed, but it shouldn't. Current value is %d, CAS a is %d", index, C, cas.a));
            }
        }
    }


    if (corr == "NO") {
        quit(_fail, "Participant found correct order, but jury isn't");
    } else {
        quit(_ok, "Order is correct");
    }
}