#include <bits/stdc++.h>
#ifdef HOME
#include "/Users/dreamoon/Code/MTF/testlib.h"
#else
#include "testlib.h"
#endif
using namespace std;
const int MAX_V = 2 * 1000 * 1000;
int a, b;
inline int readAndCheckAnswer(InStream& in, int cs) {
    vector<long long>output = in.readLongs(4, -1, (long long)MAX_V*MAX_V);
    bool no_solution = 1;
    int neg_count = 0;
    for(int i = 0; i < 4; i++) {
        if(output[i] == -1)neg_count++;
    }
    if(neg_count == 4) return 0;
    for(int i = 0; i < 4; i++) {
        if(output[i] <= 0) {
            in.quitf(_wa, "the the output of valid solution should contain only positive numbers.");
        }
    }
    if(output[1] >= b) in.quitf(_wa, "d should less than b");
    if(output[3] >= b) in.quitf(_wa, "f should less than b");
    int ga,gb;
    int gg=__gcd(a,b);
    ga=a/gg;
    gb=b/gg;
    long long p = (long long)output[0] * output[3] - (long long)output[1] * output[2];
    long long q = output[1] * output[3];
    long long pq_gg = __gcd(p, q);
    p /= pq_gg;
    q /= pq_gg;
    if(p != ga || q != gb) {
        in.quitf(_wa, "c/d - e/f != a/b (%lld/%lld-%lld/%lld != %d/%d) on test %d\n", cs,output[0],output[1],output[2],output[3],a,b);
    }
    return 1;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int T = inf.readInt();
    for(int cs = 1; cs <= T; cs++) {
        a = inf.readInt();
        b = inf.readInt();
        int ja = readAndCheckAnswer(ans, cs);
        int pa = readAndCheckAnswer(ouf, cs);
        if(ja > pa) {
            quitf(_wa, "Jury find a solution but participant doesn't (test %d)", cs);
        }
        else if(ja < pa) {
            quitf(_fail, "Participant find a solution but jury doesn't (test %d)", cs);
        }
    }

    quitf(_ok, "correct answer");
}

