#include "testlib.h"
#include <iostream>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    rnd.setSeed(23929010917850934LL);
    if (argc < 4) {
        quitf(_fail, "Not enough arguments");
    }

    int opening = atoi(argv[1]);
    int closing = atoi(argv[2]);
    string mode = argv[3];

    vector <string> text;
    for (int i = 0; i < opening; i++)
        text.push_back("<<");
    for (int i = 0; i < closing; i++)
        text.push_back(">>");

    if (mode == "shuffle") {
        shuffle (text.begin(), text.end());
    }
    else if (mode != "no_shuffle") {
        quitf(_fail, "Incorrect mode");
    }

    for (auto &p : text)
        cout << p;
    cout << endl;

    return 0;
}

