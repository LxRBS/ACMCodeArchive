#include "testlib.h"
#include <iostream>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    /* Read number from command line. */
    int left = atoi(argv[1]);
    int right = atoi(argv[2]);
    println(right - left + 1);

    for (int i = left; i <= right; i++) {
        println(i);
    }
}