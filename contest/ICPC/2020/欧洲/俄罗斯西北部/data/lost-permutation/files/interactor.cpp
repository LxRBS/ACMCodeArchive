#include "testlib.h"

int const MAX_QUERIES =  2;

using namespace std;
 
vector<int> readPermutation(InStream& inf, int n) {
    vector<int> perm(n);
    vector<bool> used(n);
    for (int i = 0; i < n; i++) {
        perm[i] = inf.readInt(1, n, format("p[%d]", i));
        perm[i]--;
        if (used[perm[i]]) {
            quitf(_wa, "Expected a permutation, but got duplicate values: %d", perm[i] + 1);
        }
        used[perm[i]] = true;
    }
    return perm;
}

int main(int argc, char * argv[]) {
    registerInteraction(argc, argv);
    int tests = inf.readInt();
    printf("%d\n", tests);

    for (int test_idx = 0; test_idx < tests; test_idx++) {
        int n = inf.readInt();
        printf("%d\n", n);
        fflush(stdout);
        vector<int> pi = readPermutation(inf, n);
        vector<int> inv_pi(n);
        for (int i = 0; i < n; i++) {
            inv_pi[pi[i]] = i;
        }
        
        int queries = 0;
        while (true) {
            string token = ouf.readWord("\?|!");
            if (token == "?") {
                queries += 1;
                if (queries > MAX_QUERIES) {
                    quitf(_wa, "Asked more than %d queries in test %d", MAX_QUERIES, test_idx);
                }
            }
            vector<int> f = readPermutation(ouf, n);
            if (token == "?") {
                for (int i = 0; i < n; i++) {
                    printf("%d", pi[f[inv_pi[i]]] + 1);
                    if (i + 1 < n) {
                        printf(" ");
                    } else {
                        printf("\n");
                    }
                }
                fflush(stdout);
            } else {
                for (int i = 0; i < n; i++) {
                    if (pi[i] != f[i]) {
                        quitf(_wa, "Guess is wrong in test %d: guessed pi[%d] = %d, but should be %d", test_idx, i, f[i], pi[i]);
                    }
                }
                break; // guess is OK, break
            }         
        }
    }
    quitf(_ok, "%d guesses done correctly", tests);
}
