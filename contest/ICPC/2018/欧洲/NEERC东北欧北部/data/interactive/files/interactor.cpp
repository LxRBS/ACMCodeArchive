#include "testlib.h"
#include <iostream>

using namespace std;

const int MAGIC = 998244352; // nobody will guess it!
const int MAX_QUERIES = 20;

int main(int argc, char* argv[])
{
    registerInteraction(argc, argv);

    inf.readInt(); // 787788
    int n = inf.readInt();
    vector<vector<int> > arrays;
    for (int i = 0; i < n; i++) {
        int len = inf.readInt();
        vector<int> cur(len);
        for (int j = 0; j < len; j++) {
            cur[j] = inf.readInt();
            if (cur[j] < 0) cur[j] *= -1;
        }
        arrays.push_back(cur);
    }

    cout << n << endl;

    int more_queries = MAX_QUERIES;
    while (true) {
        string s = ouf.readToken();
        if (s != "?" && s != "!") {
            quitf(_wa, "Expect '?' or '!', but %s found", s.c_str());
        }
        if (s == "!") {
            int sum_len = 0;
            for (int i = 0; i < n; i++) {
                int len = ouf.readInt();
                sum_len += len;
                if (len != arrays[i].size()) {
                    quitf(_wa, "Length of %d-th array differ: expected %d, found %d", i + 1, (int) arrays[i].size(), len);
                }
                for (int j = 0; j < len; j++) {
                    int val = ouf.readInt();
                    if (val != arrays[i][j]) {
                        quitf(_wa, "a[%d][%d] expected %d found %d", i + 1, j + 1, arrays[i][j], val);
                    }
                }
            }
            tout << MAGIC << endl;
            quitf(_ok, "%d arrays, sum_len = %d", n, sum_len);
        }
        more_queries--;
        if (more_queries < 0) {
            quitf(_wa, "Too many queries asked");
        }
        int len = ouf.readInt();
        if (len < 1 || len > n) {
            quitf(_wa, "asked %d arrays, not in range [1..%d]", len, n);
        }
        vector<int> res;
        for (int i = 0; i < len; i++) {
            int id = ouf.readInt();
            if (id < 1 || id > n) {
                quitf(_wa, "array_id should be in range [1..%d], found %d", n, id);
            }
            id--;
            for (int j = 0; j < arrays[id].size(); j++) {
                res.push_back(arrays[id][j]);
            }
        }
        cout << res.size();
        for (int x : res) {
            cout << " " << x;
        }
        cout << endl << flush;
    }
}