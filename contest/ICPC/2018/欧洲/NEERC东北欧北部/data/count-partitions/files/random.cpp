#include "testlib.h"
#include <iostream>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    /* Read number from command line. */
    int tests = atoi(argv[1]);
    int max = atoi(argv[2]);
    println(tests);

    for (int i = 0; i < tests; i++) {
        println(rnd.next(1, max));
    }
}