#include <bits/stdc++.h>
#include "testlib.h"

using namespace std;

int n, k;

inline void readAndCheckAnswer(InStream& in) {
    string s = in.readLine("[01]{1,10000000}"); 
    if (int(s.length()) != (1<<n))
        in.quitf(_wa, "Length must be equal to 2^n");

    int len=int(s.length());
    for (int i=0;i<len;i++)
    {
        int cnt=0;
        for (int j=0;j<n;j++)
            if (s[i]==s[i^(1<<j)]) ++cnt;
        if (cnt>k) in.quitf(_wa,"There are more than %d neighbours with the same color for node %d!",k,i);
    }
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);
    
    n = inf.readInt();
    k=0;
    while (k*k<n) ++k;

    readAndCheckAnswer(ans);
    readAndCheckAnswer(ouf);

    quitf(_ok, "n=%d", n);
}
