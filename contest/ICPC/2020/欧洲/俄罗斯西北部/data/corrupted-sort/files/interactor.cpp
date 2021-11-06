#include "testlib.h"


const int MAX_OPS =  10000;

void check_sorted(const std::vector<int> &cards, int n, int tot_ops) {
    for (int i = 0; i + 1 < cards.size(); i++) {
        if (cards[i] > cards[i + 1]) {
            return;
        }
    }
    printf("WIN\n");
    fflush(stdout);
    quitf(_ok, "Sorted (n = %d, tot_ops = %d)", n, tot_ops);
}

int main(int argc, char * argv[]) {
    registerInteraction(argc, argv);
    int n = inf.readInt();
    std::vector<int> cards(n);
    for (int i = 0; i < n; i++) {
        cards[i] = inf.readInt();
    }
    printf("%d\n", n);
    fflush(stdout);
    for (int iters = 0; iters < MAX_OPS; iters++) {
        int pos_i = ouf.readInt(1, n - 1, "pos_i");
        int pos_j = ouf.readInt(pos_i + 1, n, "pos_j");
        pos_i--;
        pos_j--;
        if (cards[pos_i] < cards[pos_j]) {
            check_sorted(cards, n, iters + 1);
            printf("STAYED\n");
        } else {
            std::swap(cards[pos_i], cards[pos_j]);
            check_sorted(cards, n, iters + 1);
            printf("SWAPPED\n");
        }
        fflush(stdout);
        if ((iters + 1) % (2 * n) == 0) {
            int p1 = 0, p2 = 0;
            while (p1 == p2) {
                p1 = rnd.next(n);
                p2 = rnd.next(n);
            }
            std::swap(cards[p1], cards[p2]);
        }

    }
    quitf(_wa, "Too many operations (%d), still not sorted", MAX_OPS);
}
