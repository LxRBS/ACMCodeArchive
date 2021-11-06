#include "testlib.h"
#include <iostream>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    /* Read number from command line. */
    int value = atoi(argv[1]);
    int repeats = atoi(argv[2]);
    println(repeats);

    for (int i = 0; i < repeats; i++) {
        println(value);
    }
}